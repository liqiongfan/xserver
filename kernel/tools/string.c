/**
 * File:{string.c} for project {Xserver}.
 * Author: Josin
 * Email: xeapplee@gmail.com
 * Website: https://www.supjos.cn
 */

#include "string.h"
#include "list.h"
#include <ctype.h>

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

char *
/* Get the substring of the string
 * mode: 0 -> trim left space
 * mode: 1 -> trim right space
 * mode: 2 -> trim both right & left space */
string_substr_option(const char *src, ssize_t length, int _mode)
{
    int _left = 0, _right = 0, _i, _src_len = ( int )length - 1/* Max pos. */, _result_len = 0;
    if ( _mode == 0 || _mode == 2 )
    {
        for ( _i = 0; _i <= _src_len; ++_i )
        {
            char cur_char = src[_i];
            if ( cur_char == ' ')  _left++;
            else break;
        }
    }
    
    if ( _mode == 1 || _mode == 2 )
    {
        for ( _i = _src_len; _i >= 0; _i-- )
        {
            char cur_char = src[_i];
            if ( cur_char == ' ') _right++;
            else break;
        }
    }
    
    _result_len = _src_len - _left - _right + 2/* Two means the first boundary and the terminate null char */;
    char *result = (char *)malloc( sizeof(char) * _result_len );
    memset(result, 0, _result_len );
    strncpy(result, src + _left, _result_len - 1);
    return result;
}

void
/* This function turn the source string's char case to lowercase */
string_to_lower(char *src)
{
    int _i;
    for ( _i = 0; _i < strlen(src); ++_i )
    {
        src[_i] = ( char )tolower( src[_i]);
    }
}

void
/* Turn the source string to uppercase */
string_to_upper(char *src)
{
    int _i;
    for ( _i = 0; _i < strlen(src); ++_i )
    {
        src[_i] = ( char )toupper( src[_i]);
    }
}

char *
/* Trim space from the src string
 * Fix bug: #101 left boundary check.
 * mode: 0 -> trim left space
 * mode: 1 -> trim right space
 * mode: 2 -> trim both right & left space */
trim_space(char *src, int _mode)
{
    int _left = 0, _right = 0, _i, _src_len = ( int )strlen( src);
    if ( _mode == 0 || _mode == 2 )
    {
        for ( _i = 0; _i < _src_len; ++_i )
        {
            char cur_char = src[_i];
            if ( cur_char == ' ') _left++;
            else break;
        }
    }
    
    if ( _mode == 1 || _mode == 2 )
    {
        for ( _i = _src_len - 1; _i >= 0; _i-- )
        {
            char cur_char = src[_i];
            if ( cur_char == ' ') _right++;
            else break;
        }
    }
    
    char *result = (char *)malloc( sizeof(char) * (_src_len - _left - _right + 1) );
    memset(result, 0, (_src_len - _left - _right + 1));
    strncpy(result, src + _left, _src_len - _left - _right);
    return result;
}

char *
/* Get the http stream from the tcp http connection
 * Fix bug #100: over-write buffer data previous read from
 * realloc return value check wrong. */
get_stream_from_socket(int __sock_fd)
{
    /* Total size of the buffer, initialise to 4096 * 16 */
    ssize_t __size = BUFFER_SIZE * 16 + 1;
    int _realloc_number = 0;
    
    /* Allocate 16 package of the buffer string result from the stack */
    char *__result_buffer = (char *)malloc(sizeof(char) * __size);
    memset(__result_buffer, 0, __size);
    
    ssize_t __buffer_size;
    char __buffer[BUFFER_SIZE] = { 0 };
    while ( true )
    {
        memset(__buffer, 0, BUFFER_SIZE);
        __buffer_size = read(__sock_fd, __buffer, BUFFER_SIZE);
        if ( __buffer_size == 0 ) break;
        
        if ( (strlen(__result_buffer) + __buffer_size) >= BUFFER_SIZE * 15  )
        {
            void *__temp_buffer = realloc(__result_buffer, sizeof(char) * ( __size + BUFFER_SIZE ) );
            if ( __temp_buffer ) {
                __result_buffer = __temp_buffer;
            } else {
                free(__result_buffer);
                __result_buffer = EMPTY_PTR;
                LOG_INFO(LOG_ERROR_LEVEL, "Allocate memory failure: size is : %ld\n", __size + BUFFER_SIZE );
            }
            __size += BUFFER_SIZE;
        }
    
        strncpy( __result_buffer + ( BUFFER_SIZE * _realloc_number ), __buffer, BUFFER_SIZE );
        if ( __buffer_size < BUFFER_SIZE ) break;
        _realloc_number++;
    }
    return __result_buffer;
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

list *
/* Parse the HTTP query string and store it into the list
 * NOTE: destroy the list after used.
 * for example: query_string = "a=b&c=d&d=e"
 * warning: query_string's first char mustn't be `?` */
parse_query_string(const char *query_string)
{
    ssize_t _pos = 0,
            _start_pos = 0,
            _query_string_len = strlen(query_string);
    list *_result = EMPTY_PTR, *_v;
    list_data *_value = EMPTY_PTR;
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

void *
/* Parse the http stream from the given http_stream parameter
 * such as:
 * GET /index.action HTTP/1.1\r\n
 * Content-Length: 10\r\n
 * Content-Type: application/json;charset=utf-8\r\n
 * \r\n
 * {"a":"aa"} */
parse_http_stream(const char *http_stream, int *str_len)
{
    *str_len = 0;
    int _i, _colon_pos = 0;
    long _content_length = 0;
    list *__list_data = EMPTY_PTR, *value_data;
    size_t _http_stream_length = strlen(http_stream), _i_pos = 0, _white_count = 0;
    
    /* Parse the HTTP stream's first line when meeting the first \r\n stop */
    for ( _i = 0; _i < _http_stream_length; ++_i )
    {
        char current_char = http_stream[_i];
        
        if ( current_char == ' ' ) {
            switch (_white_count)
            {
                case 0:
                    /* Request method */
                    value_data = INIT_LIST();
                    value_data->delete_func = __delete_stream_data__;
                    value_data->node.data_ptr = INIT_LIST_DATA_OVER(
                        "request_method",  string_substr(http_stream + _i_pos, _i - _i_pos)
                    );
                    __list_data = APPEND_LIST(__list_data, value_data);
                    break;
                case 1:
                    /* Request URI */
                    value_data = INIT_LIST();
                    value_data->delete_func = __delete_stream_data__;
                    value_data->node.data_ptr = INIT_LIST_DATA_OVER(
                        "request_uri",  string_substr(http_stream + _i_pos, _i - _i_pos)
                    );
                    __list_data = APPEND_LIST(__list_data, value_data);
                    break;
            }
            _i_pos = ( size_t )_i + 1;
            _white_count++;
        }
        
        if ( current_char == '\r' && http_stream[_i + 1] == '\n' )
        {
            if ( _white_count == 2 )
            {
                /* Request HTTP/VERSION */
                value_data = INIT_LIST();
                value_data->delete_func   = __delete_stream_data__;
                value_data->node.data_ptr = INIT_LIST_DATA(
                    "http_version", string_substr( http_stream + _i_pos, _i - _i_pos ), false
                );
                __list_data = APPEND_LIST( __list_data, value_data );
            }
            _i_pos = ( size_t )_i + 2;
            break;
        }
    }
    
    /* Parse the second line to last second line */
    for ( _i = ( int )_i_pos; _i < _http_stream_length; ++_i )
    {
        char current_char = http_stream[ _i ];
        if ( current_char == ':' ) _colon_pos = _i + 1;
        if (
            current_char == '\r' && http_stream[ _i + 1] == '\n' && _colon_pos )
        {
            if (http_stream[ _i + 2 ] != '\r' && http_stream[ _i + 3] != '\n')
            {
                /* Request HTTP/VERSION */
                list_data *__v = INIT_EMPTY_DATA();
                strncpy( __v->name, http_stream + _i_pos, _colon_pos - _i_pos - 1);
                /* string_to_lower(__v->name); */
                __v->value = string_substr_option( http_stream + _colon_pos, _i - _colon_pos, 2);
                if ( strncasecmp(__v->name, "content-length", 14) == 0 )
                {
                    _content_length = strtol(__v->value, EMPTY_PTR, 10);
                }
                value_data = INIT_LIST();
                value_data->delete_func   = __delete_stream_data__;
                value_data->node.data_ptr = __v;
                __list_data = APPEND_LIST( __list_data, value_data );
                _i_pos = ( size_t )_i + 2;
            }
            else if (http_stream[ _i + 2 ] == '\r' && http_stream[ _i + 3] == '\n')
            {
                /* Insert the last header */
                list_data *__v = INIT_EMPTY_DATA();
                strncpy( __v->name, http_stream + _i_pos, _colon_pos - _i_pos - 1);
                __v->value = string_substr_option( http_stream + _colon_pos, _i - _colon_pos, 2);
                value_data = INIT_LIST();
                value_data->delete_func   = __delete_stream_data__;
                value_data->node.data_ptr = __v;
                __list_data = APPEND_LIST( __list_data, value_data );
                
                /* trip to the body start pos. */
                #if 0 /* for optimization not to get the length size by iterate the list */
                list *__temp_v;
                LIST_FOREACH_VAL(__list_data, __temp_v) {
                    list_data *__data = __temp_v->node.data_ptr;
                    if ( strncasecmp(__data->name, "content-length", 14) == 0 )
                    {
                        _content_length = strtol(__data->value, EMPTY_PTR, 10);
                    }
                } LIST_FOREACH_END();
                #endif
                
                /* Request HTTP/VERSION */
                value_data = INIT_LIST();
                value_data->delete_func   = __delete_stream_data__;
                value_data->node.data_ptr = INIT_LIST_DATA_OVER(
                    "http_body", string_substr( http_stream + _i + 4, _content_length )
                );
                __list_data = APPEND_LIST( __list_data, value_data );
                
                /* Set the last start pos. */
                *str_len = _i + 4 + _content_length;
                break;
            }
        }
    }
    
    /* Return the data to the outer space,
     * NOTE that to free it after used. */
    return __list_data;
}


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

















