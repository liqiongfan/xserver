#include <stdio.h>
#include "kernel/config.h"
#include "kernel/net/tcp_server.h"
#include "kernel/tools/list.h"
#include "kernel/crypts/base64.h"
#include "kernel/crypts/md5.h"

int main()
{

	// xserver_init_threads(3);
	//
	// int sockd_fd = xserver_init(EMPTY_PTR, 0);
	//
	// xserver_run(sockd_fd);
	//
	// for (int i = 0; i < 3; ++i) {
	// 	pthread_join(_threads[i], EMPTY_PTR);
	// }

	// list *data = EMPTY_PTR;
	// for (int i = 0; i < 10; ++i) {
	// 	list *_t = INIT_LIST();
	// 	_t->node.data = i;
	// 	if ( i == 7 || i == 9 || i == 0 ) LIST_DELETE_PTR(_t);
	// 	data = APPEND_LIST(data, _t);
	// }
	//
	// list *_v = EMPTY_PTR;
	// LIST_FOREACH_VAL(data, _v) {
	// 	printf("%d:%d\n", _v->node.data, _v->node_status);
	// } LIST_FOREACH_END();
	//
	// DESTROY_LIST(data);

	char buff[256] = {0};
	char *str = "hello world";
	sha256(str, strlen(str) - 1, buff);
	printf("%s\n", buff);

	return 0;
}