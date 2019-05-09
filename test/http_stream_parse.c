/**
 * File:http_stream_parse.c for project Xserver.
 * Author: Josin
 * Email: xeapplee@gmail.com
 * Website: https://www.supjos.cn
 */

#include "../kernel/net/tcp_server.h"
#include "../kernel/tools/list.h"
#include "../kernel/tools/string.h"


int main (int argc, char *argv[])
{
    int sock_fd, _client_fd;
    sock_fd = xserver_init(EMPTY_PTR, 0);
    
    int _next_pos;
    while ( true ) {
        _client_fd = accept(sock_fd, EMPTY_PTR, EMPTY_PTR);
        if ( _client_fd ) {
            char *buff = get_stream_from_socket(_client_fd);
            list *_request_stream = parse_http_stream( buff, &_next_pos ), *_temp;
            LIST_FOREACH_VAL(_request_stream, _temp) {
                list_data *_data = _temp->node.data_ptr;
                printf("%s:%s\n", _data->name, _data->value);
            } LIST_FOREACH_END();
            free(buff);
            DESTROY_LIST(_request_stream);
        }
    }
}