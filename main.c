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
    
    return 0;
}