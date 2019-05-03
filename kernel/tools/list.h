/**
 * File: list.h for project Xserver
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#ifndef XSERVER_LIST_H
#define XSERVER_LIST_H

#include "../config.h"

__BEGIN_DECL

/* The type __list_node value */
typedef struct __list_data {
    char name[256];     /* Node key   */
    char *value;        /* Node value */
} list_data;

/* _list_node is the node for the list */
typedef struct _list_node {
	int                data;     /* type: 1 */
	void              *data_ptr; /* type: 2 */
	int                type;     /* default 1 */
} list_node;

typedef void (*__func)(list_node *);

#define LIST_NODE_CONST_TYPE 1
#define LIST_NODE_PTR_TYPE   2
#define LIST_NODE_DELETE     1
#define LIST_NODE_NORMAL     0

/* List */
typedef struct _list {
	struct _list      *previous;
	struct _list      *next;
	struct _list_node  node;
	int                node_status;
	__func             delete_func;
} list;

/* Get the node value from the data field or data_ptr field
 * defined by the node type field */
#define LIST_NODE_GET_VAL(__node) \
	(__node).node.type == LIST_NODE_CONST_TYPE ? (__node).node.data : (__node).node.data_ptr
#define LIST_NODE_GET_VAL_PTR(__node) LIST_NODE_GET_VAL((*__node))

#define LIST_VAL(__node, __value) if ((__node).node.type == LIST_NODE_CONST_TYPE) (__node).node.data = (__value); \
	else (__node).node.data_ptr = (__value)
#define LIST_VAL_PTR(__node, __value) LIST_VAL(*(__node), __value)


#define LIST_NODE_VAL(__node, val) (__node).data = val
#define LIST_NODE_VAL_PTR(__node, val) (__node).data_ptr = val
#define LIST_PREVIOUS(__list) (__list).previous
#define LIST_PREVIOUS_PTR(__list) (__list)->previous
#define LIST_NEXT(__list) (__list).next
#define LIST_NEXT_PTR(__list) (__list)->next
#define LIST_GET_VAL(__list) (__list).node
#define LIST_GET_VAL_PTR(__list) (__list)->node
#define LIST_DELETE(__list) (__list).node_status = LIST_NODE_DELETE
#define LIST_DELETE_PTR(__list) (*__list).node_status = LIST_NODE_DELETE


list_data *
INIT_LIST_DATA(char *, char *, int);

list_data *
INIT_EMPTY_DATA();

list *
INIT_LIST();

list *
APPEND_LIST(list *__list_v, list *__data_d);

list *
DELETE_LIST(list *data);

void
DESTROY_LIST(list *_list);

void
SET_NODE_VAL_LIST(list *_list, int _i);

void
SET_NODE_PTR_LIST(list *_list, void *_p);

list *
POP_LIST(list *list);

static list *
/* Get the end element of the list */
END_LIST(list *_list)
{
	list *temp = _list;

	while ( temp->next ) {
		/* Loop the next node in list. */
		temp = temp->next;
	}

	return temp;
}

static list *
/* Get the first element of the list */
HEAD_LIST(list *_list)
{
	list *temp = _list;

	while ( temp->previous ) {
	    /* Loop the previous node in the list. */
		temp = temp->previous;
	}

	return temp;
}

/* The macro for list using
 * for example:
 * The typeof list is (list *)
 * val's type is (list *) too:
 * LIST_FOREACH_VAL(list, val) {
 *     printf("%d\t", val->node.data);
 * } LIST_FOREACH_END(); */
#define LIST_FOREACH_VAL(_list, _val) do {\
    if ( _list != EMPTY_PTR ) {\
	list *t = HEAD_LIST(_list); \
	for (; t != EMPTY_PTR ; t = t->next) {\
		if ( t->node_status == LIST_NODE_DELETE )\
            continue; \
		_val = t;
#define LIST_FOREACH_END() }}} while(0)

/* Allocate the list data and set the default value for it. */
#define INIT_LIST_DATA_OVER(key, value) INIT_LIST_DATA(key, value, true)












__END_DECL

#endif /* XSERVER_LIST_H */
