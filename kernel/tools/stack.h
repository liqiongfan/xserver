/**
 * File: stack.h for project Exjson
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#ifndef EXJSON_STACK_H
#define EXJSON_STACK_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef void (*_destructor_stack_func_)(void *data);

typedef struct _STACK_V
{
	void            *data;
	unsigned char    tag;
	unsigned char    memory_free; /* 1: not free */
	struct _STACK_V *prev;
	struct _STACK_V *next;
} E_STACK_V;
#define SV_INT      2
#define SV_DOUBLE   3
#define SV_STRING   4
#define SV_ARRAY    5
#define SV_OBJECT   6
#define SV_PTR      7
#define SV_DATA(stack_v) (stack_v).data
#define SV_DATA_P(stack_v) SV_DATA(*(stack_v))
#define SV_TAG(stack_v) (stack_v).tag
#define SV_TAG_P(stack_v) SV_TAG(*(stack_v))
#define SV_PREV(stack_v) (stack_v).prev
#define SV_PREV_P(stack_v) SV_PREV(*(stack_v))
#define SV_NEXT(stack_v) (stack_v).next
#define SV_NEXT_P(stack_v) SV_NEXT(*(stack_v))
#define SV_MEMORY_FREE(stack_v) (stack_v).memory_free
#define SV_MEMORY_FREE_P(stack_v) SV_MEMORY_FREE(*(stack_v))

typedef struct _STACK
{
	 struct _STACK_V       *head;
	_destructor_stack_func_ destructor_stack_func_;
} E_STACK;
#define ST_HEAD(stack) (stack).head
#define ST_HEAD_P(stack) ST_HEAD(*(stack))
#define ST_FUNC(stack) (stack).destructor_stack_func_
#define ST_FUNC_P(stack) ST_FUNC(*stack)

E_STACK *
INIT_STACK();

E_STACK_V *
INIT_STACK_V();

E_STACK_V *
pop(E_STACK *);

int push(E_STACK *, void *data, size_t size);
int push_int(E_STACK *, int val);
int push_int_tag(E_STACK *, int val, unsigned char tag);
int push_double(E_STACK *, double val);
int push_string(E_STACK *, char *str, int _re_alloc_);
void destroy_stack(E_STACK *);


#endif /* EXJSON_STACK_H */



