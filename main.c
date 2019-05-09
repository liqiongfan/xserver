#include <stdio.h>
#include "kernel/config.h"
#include "kernel/net/tcp_server.h"
#include "kernel/tools/list.h"
#include "kernel/crypts/base64.h"
#include "kernel/crypts/md5.h"
#include "kernel/tools/string.h"
#include "kernel/tools/stack.h"

int main()
{
    // int sock_fd, thread_number = 3, i;
    //
    // xserver_init_threads(thread_number);
    //
    // sock_fd = xserver_init(EMPTY_PTR, 0);
    //
    // xserver_run(sock_fd);
    //
    // for (i = 0; i < thread_number; ++i) {
    //     pthread_join(_threads[i], EMPTY_PTR);
    // }
    
    EX_STACK *stack = INIT_STACK();
    int a = 10;
    push_stack(stack, &a, sizeof(int));
    a = 20;
    push_stack(stack, &a, sizeof(int));
    
    EX_STACK_V *v;
    v = INIT_STACK_V();
    a = 30;
    v->data = &a;
    push_back(stack, v);
    
    EX_STACK_V *stack_v = pop_stack(stack);
    printf("%d\t", *(int *)stack_v->data);
    // stack_free(stack_v);
    stack_v = pop_stack(stack);
    printf("%d\t", *(int *)stack_v->data);
    // stack_free(stack_v);
    
    // DESTROY_STACK(stack);
    
    return 0;
}