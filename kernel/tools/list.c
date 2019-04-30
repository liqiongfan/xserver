/**
 * File: list.c for project Xserver
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#include "list.h"


list *
/* Allocate a node for list and set default value for it.
 * RETURN:
 * The allocated memory */
INIT_LIST()
{
	list *data = (list *)malloc(sizeof(list));
	memset(data, 0, sizeof(list));
	data->node_status = LIST_NODE_NORMAL;
	data->next = EMPTY_PTR;
	data->previous = EMPTY_PTR;
	data->node.data = 0;
	data->node.data_ptr = EMPTY_PTR;
	data->node.type = LIST_NODE_CONST_TYPE;
	assert( data != EMPTY_PTR );
	return data;
}

void
SET_NODE_VAL_LIST(list *_list, int _i)
{
	if ( _list->node.type == LIST_NODE_CONST_TYPE ) {
		_list->node.data = _i;
	}
}

void
SET_NODE_PTR_LIST(list *_list, void *_p)
{
	if ( _list->node.type == LIST_NODE_PTR_TYPE ) {
		_list->node.data_ptr = _p;
	}
}

list *
/* Add the data to the end of the list
 * RETURN:
 * The newly insert data node. */
APPEND_LIST(list *__list_v, list *__data_d)
{
	if (!__list_v) {
		return __data_d;
	}
	list *temp = END_LIST(__list_v);
	temp->next = __data_d;
	__data_d->previous = temp;
	return __data_d;
}


list *
/* Delete the data node from the list
 * RETURN:
 * The last node of the list */
DELETE_LIST(list *data)
{
	LIST_DELETE_PTR(data);
	return END_LIST(data);
}

void
/* Destroy the list */
DESTROY_LIST(list *__list_v)
{
	list *__temp_t = HEAD_LIST(__list_v), *t;
	while (__temp_t->next)
	{
		t = __temp_t->next;
		__temp_t->next = t->next;
		free(t);
		t = EMPTY_PTR;
	}
	free(__temp_t);
	__temp_t = EMPTY_PTR;
	__list_v->previous = EMPTY_PTR;
	__list_v = EMPTY_PTR;
}

list *
/* Pop the first element in the list and return
 * RETURN:
 * The first element of the list OR EMPTY when there is not element */
POP_LIST(list *_list)
{
	list *temp = HEAD_LIST(_list);
	if (!temp) return EMPTY_PTR;
	LIST_DELETE_PTR(temp);
	return temp->next;
}















