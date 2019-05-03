#include <stdio.h>
#include "kernel/config.h"
#include "kernel/net/tcp_server.h"
#include "kernel/tools/list.h"
#include "kernel/crypts/base64.h"
#include "kernel/crypts/md5.h"
#include "kernel/tools/string.h"

int main()
{
    int sock_fd, thread_number = 3, i;

	xserver_init_threads(thread_number);

    sock_fd = xserver_init(EMPTY_PTR, 0);

	xserver_run(sock_fd);

	for (i = 0; i < thread_number; ++i) {
		pthread_join(_threads[i], EMPTY_PTR);
	}

	// char *request_stream =
	//     "GET /index.php?a=b&c=d HTTP/1.1\r\n"
    //     "Content-Type: application/json;charset=UTF-8\r\n"
    //     "Content-Length: 10\r\n"
    //     "Status Code: 202\r\n"
    //     "Code: 898\r\n"
    //     "\r\n"
    //     "{\"A\":\"AA\"}";
	//
	// int _t;
	// list *_v = parse_http_stream(request_stream, &_t);
	//
	//
	// list *__t;
	// LIST_FOREACH_VAL(_v, __t) {
	//     list_data *__k = (list_data *)__t->node.data_ptr;
	//     printf("[%s:%s]\n", __k->name, __k->value);
	// } LIST_FOREACH_END();
	//
	// DESTROY_LIST(_v);

	return 0;
}