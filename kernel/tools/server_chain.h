/**
 * File: ${FILE} for project Xserver
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#ifndef XSERVER_SERVER_CHAIN_H
#define XSERVER_SERVER_CHAIN_H

typedef struct list {
	struct list *_previous;
	struct list *_next;
	int _fd;
	void *data;
	int status;/* 0: need to work, or 1: done. */
} _list;

#define LIST_FOR_EACH_FD(__data, __value) do { \
	_list *t = __data;           \
    for ( ; t != EMPTY_PTR; t = t->_next ) {\
        *__value = t->_fd;

#define LIST_FOR_EACH_ITER(__data, __value) do { \
	_list *t = __data;          \
    for ( ;t != EMPTY_PTR; t = t->_next ) {\
        __value = t;

#define LIST_FOR_EACH_END }   \
	} while(0)


#define IS_DONE(__list_value)  (__list_value->status == 1)
#define LIST_VAL(__list_value) (__list_value->_fd)

_list *
init_list();

_list *
list_first(_list *data);

void
list_del(_list *data, _list *iter);

_list *
push_back_list(_list *list, _list *data);

void
destroy_list(_list *data);



#endif /* XSERVER_SERVER_CHAIN_H */
