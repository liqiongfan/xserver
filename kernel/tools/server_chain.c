/**
 * File: ${FILE} for project Xserver
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#include "server_chain.h"
#include "../config.h"

_list *
/*
 * Init the list data which store the newly client fd.
 * Return:
 * The _list data */
init_list()
{
	_list *data = (_list *)malloc(sizeof(_list));
	memset(data, 0, sizeof(_list));
	assert(data != EMPTY_PTR);
	return data;
}

_list *
/* Get the head value for the _list data
 * Return value:
 * The head value for the _list data */
list_first(_list *data)
{
	_list *temp = data;
	while (1)
	{
		if (temp->_previous)
		{
			temp = temp->_previous;
		} else break;
	}
	return temp;
}

void
/* Delete the iter from the data
 * with the iter value */
list_del(_list *data, _list *iter)
{
	_list *first_data = list_first(data), *temp = first_data, *_t;
	while ( temp )
	{
		if (temp->_fd == iter->_fd)
		{
			if ( !temp->_previous ) {
				_t = temp;
				free(temp);
				_t->_next->_previous = EMPTY_PTR;
			} else {
				_t = temp;
				free(temp);
				_t->_previous->_next = _t->_next;
				_t->_next->_previous = _t->_previous;
			}
		}
		temp = temp->_next;
	}
}

_list *
/* To append the data back to the _list chain
 * if data is NULL or nullptr nothing will done other than.
 * RETURN VALUE:
 * the last node in the chain _list */
push_back_list(_list *list, _list *data)
{
	if ( data )
	{
		_list *last_node = list;

		while ( 1 ) {
			if ( last_node->_next ) {
				last_node = last_node->_next;
			} else break;
		}

		/* After find the last node, do the append operation */
		last_node->_next = data;
		data->_previous = last_node;
	}
	return data;
}

void
/* To destroy the list data with the given parameter data
 * to loop the data and free it
 * */
destroy_list(_list *data)
{
	_list *head_node = list_first(data);
	_list *next = head_node->_next, *_temp;
	while (next)
	{
		_temp = next;
		free(next);
		next = _temp->_next;
	}
	free(head_node);
}