#include <stdio.h>
#include "kernel/config.h"
#include "kernel/tools/server_chain.h"
#include "kernel/net/tcp_server.h"

int main()
{

	xserver_init_threads(5);

	int sockd_fd = xserver_init(EMPTY_PTR, 0);

	xserver_run(sockd_fd);

	for (int i = 0; i < 5; ++i) {
		pthread_join(_threads[i], EMPTY_PTR);
	}

	return 0;
}