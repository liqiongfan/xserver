/**
 * File:string_split.c for project Xserver.
 * Author: Josin
 * Email: xeapplee@gmail.com
 * Website: https://www.supjos.cn
 */

#include <string.h>
#include <stdio.h>
#include "../kernel/tools/list.h"

void
/* Split the string by the delimiter for example:
 * src: hello||world
 * delimiter: ||
 * so first calling result is: result => hello
 * second invoking result is : world
 * This function not allocate memory, developer need keep that the result parameter
 * has memory to store the data */
split_string(const char *_source, const char *delimiter, char *result, int _over)
{
    if ( !delimiter ) return ;
    
    static ssize_t _pos = 0;
    if ( _over ) _pos = 0;
    ssize_t _str_len = strlen(_source), _i, _j = 0, _deli_len = strlen(delimiter);
    memset(result, 0, strlen(result));
    for ( _i = _pos; _i < _str_len; ++_i )
    {
        char cur_src_char = _source[_i];
        char cur_deli_char = delimiter[_j];
        if ( cur_deli_char == cur_src_char ) {
            if ( _deli_len == 1) {
                strncpy(result, _source + _pos, _i - _pos);
                _pos = _i + _deli_len;
                break;
            }
            else
            {
                for ( _j = _j + 1; _j < _deli_len; ++_j )
                {
                    if ( delimiter[ _j ] != _source[ _i + _j ] ) return ;
                    if ( _j == _deli_len - 1 )
                    {
                        strncpy( result, _source + _pos, _i - _pos );
                        _pos = _i + _deli_len;
                        return ;
                    }
                }
            }
        } else {
            if (_i == _str_len - 1 && _pos) {
                strncpy(result, _source + _pos, _i - _pos + 1);
                return ;
            }
        }
    }
}

static void
/* Delete the defined data from list
 * Note that need to free the node and the value node after used. */
__delete_stream_data__(list_node *value)
{
    list_data *_list_data = (list_data *)value->data_ptr;
    free(_list_data->value);
    free(_list_data);
    value->data_ptr =  _list_data->value = EMPTY_PTR;
}

char *
/* Get the substring of the string
 * Note that: the returned string need to be freed after used. */
string_substr(const char *src, ssize_t length)
{
    char *__v_v = (char *)malloc( sizeof(char) * (length + 1) );
    memset(__v_v, 0, length + 1 );
    strncpy(__v_v, src, length);
    return __v_v;
}

list *
/* Parse the HTTP query string and store it into the list
 * NOTE: destroy the list after used.
 * for example: query_string = "a=b&c=d&d=e" */
parse_query_string(const char *query_string)
{
    ssize_t _pos = 0, _start_pos = 0, _query_string_len = strlen(query_string);
    list *_result = EMPTY_PTR, *_v;
    list_data *_value = EMPTY_PTR;
    int _isset_key = 0;
    char _key[KEY_BUFFER_SIZE] = {0};
    
    for ( _pos = 0; _pos < _query_string_len; ++_pos )
    {
        char cur_char = query_string[_pos];
        if ( cur_char == '=' ) {
            memset(_key, 0, KEY_BUFFER_SIZE);
            strncpy(_key, query_string + _start_pos, _pos - _start_pos);
            _start_pos = _pos + 1;
        }
        else if ( cur_char == '&' )
        {
            _value = INIT_EMPTY_DATA();
            strncpy(_value->name, _key, KEY_BUFFER_SIZE);
            _value->value = string_substr(query_string + _start_pos, _pos - _start_pos);
            _start_pos = _pos + 1;
            
            _v = INIT_LIST();
            _v->node.data_ptr = _value;
            _v->delete_func = __delete_stream_data__;
            
            _result = APPEND_LIST(_result, _v);
        }
    }
    
    return _result;
}



int main(int argc, char *argv[])
{
    char *source = "aa=bb&cc=dd&ee=ff&gg=hh";
    list *_v = parse_query_string(source);
    
    list *_temp;
    LIST_FOREACH_VAL(_v, _temp) {
        list_data *_data = (list_data *)_temp->node.data_ptr;
        printf("%s:%s\t", _data->name, _data->value);
    } LIST_FOREACH_END();
    
    DESTROY_LIST(_v);
    
    return 0;
}