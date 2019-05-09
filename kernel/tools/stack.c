/**
 * File: stack.h for project Exjson
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

/* EX_STACK as the stack data for preserving data with structure `Stack`
 * for example:
 * E_STACK *stack = INIT_STACK();
 * push_int(stack, 10);
 * push_int(stack, 22);
 * destroy_stack(stack); */

#include "stack.h"

E_STACK *
INIT_STACK()
{
	E_STACK *ptr = malloc(sizeof(E_STACK));
	assert(ptr != NULL);
	memset(ptr, 0, sizeof(E_STACK));
	return ptr;
}

E_STACK_V *
INIT_STACK_V()
{
	E_STACK_V *ptr = malloc(sizeof(E_STACK_V));
	SV_PREV_P(ptr) = NULL;
	SV_NEXT_P(ptr) = NULL;

	assert(ptr != NULL);
	memset(ptr, 0, sizeof(E_STACK_V));
	return ptr;
}

int
push(E_STACK *stack, void *data, size_t size)
{
	E_STACK_V *head = ST_HEAD_P(stack),
	          *temp_val = INIT_STACK_V();
	SV_PREV_P(temp_val) = NULL;
	SV_NEXT_P(temp_val) = NULL;
	if ( size )
	{
		SV_DATA_P(temp_val) = malloc(size);
		assert(SV_DATA_P(temp_val) != NULL);
		memcpy(SV_DATA_P(temp_val), data, size);
	}
	else
	{
		SV_DATA_P(temp_val) = data;
	}
	SV_TAG_P(temp_val) = SV_PTR;

	if ( !head )
	{
		ST_HEAD_P(stack) = temp_val;
	}
	else
	{
		SV_NEXT_P(temp_val) = head;
		SV_PREV_P(head)     = temp_val;
		ST_HEAD_P(stack)    = temp_val;
	}
	return 1;
}

int
push_int(E_STACK *stack, int val)
{
	E_STACK_V *head = ST_HEAD_P(stack),
	          *temp_val = INIT_STACK_V();
	SV_PREV_P(temp_val) = NULL;
	SV_NEXT_P(temp_val) = NULL;
	SV_DATA_P(temp_val) = malloc(sizeof(int));
	assert(SV_DATA_P(temp_val) != NULL);
	memcpy(SV_DATA_P(temp_val), &val, sizeof(int));
	SV_TAG_P(temp_val) = SV_INT;

	if ( !head )
	{
		ST_HEAD_P(stack) = temp_val;
	}
	else
	{
		SV_NEXT_P(temp_val) = head;
		SV_PREV_P(head)     = temp_val;
		ST_HEAD_P(stack)    = temp_val;
	}
	return 1;
}

int 
push_int_tag(E_STACK *stack, int val, unsigned char tag)
{
	E_STACK_V *head = ST_HEAD_P(stack),
	          *temp_val = INIT_STACK_V();
	SV_PREV_P(temp_val) = NULL;
	SV_NEXT_P(temp_val) = NULL;
	SV_DATA_P(temp_val) = malloc(sizeof(int));
	assert(SV_DATA_P(temp_val) != NULL);
	memcpy(SV_DATA_P(temp_val), &val, sizeof(int));
	SV_TAG_P(temp_val) = tag;

	if ( !head )
	{
		ST_HEAD_P(stack) = temp_val;
	}
	else
	{
		SV_NEXT_P(temp_val) = head;
		SV_PREV_P(head)     = temp_val;
		ST_HEAD_P(stack)    = temp_val;
	}
	return 1;
}

int
push_double(E_STACK *stack, double val)
{
	E_STACK_V *head = ST_HEAD_P(stack),
	          *temp_val = INIT_STACK_V();
	SV_PREV_P(temp_val) = NULL;
	SV_NEXT_P(temp_val) = NULL;
	SV_DATA_P(temp_val) = malloc(sizeof(double));
	assert(SV_DATA_P(temp_val) != NULL);
	memcpy(SV_DATA_P(temp_val), &val, sizeof(double));
	SV_TAG_P(temp_val) = SV_DOUBLE;

	if ( !head )
	{
		ST_HEAD_P(stack) = temp_val;
	}
	else
	{
		SV_NEXT_P(temp_val) = head;
		SV_PREV_P(head)     = temp_val;
		ST_HEAD_P(stack)    = temp_val;
	}
	return 1;
}

int
push_string(E_STACK *stack, char *str, int _re_alloc_)
{
	unsigned long str_len;
	E_STACK_V *head = ST_HEAD_P(stack),
	          *temp_val = INIT_STACK_V();
	SV_PREV_P(temp_val) = NULL;
	SV_NEXT_P(temp_val) = NULL;
	if ( _re_alloc_ )
	{
		str_len = strlen(str) + 1;
		SV_DATA_P(temp_val) = malloc(str_len);
		memset(SV_DATA_P(temp_val), 0, str_len);
		memcpy(SV_DATA_P(temp_val), str, str_len - 1);
	}
	else
	{
		SV_DATA_P(temp_val) = str;
		SV_MEMORY_FREE_P(temp_val) = 1;
	}
	SV_TAG_P(temp_val) = SV_STRING;

	if ( !head )
	{
		ST_HEAD_P(stack) = temp_val;
	}
	else
	{
		SV_NEXT_P(temp_val) = head;
		SV_PREV_P(head)     = temp_val;
		ST_HEAD_P(stack)    = temp_val;
	}
	return 1;
}

E_STACK_V *
pop(E_STACK *stack)
{
	E_STACK_V *val = ST_HEAD_P(stack);
	if ( !val ) return NULL;
	ST_HEAD_P(stack) = SV_NEXT_P(ST_HEAD_P(stack));
	return val;
}

void
destroy_stack(E_STACK *stack)
{
	E_STACK_V *head = ST_HEAD_P(stack),
	          *prev = head, *next;
    
	if ( prev )
    {
        while ( SV_PREV_P( prev ) )
            prev = SV_PREV_P( prev );
    
        /* Getting the head of the stack
         * free the memory allocated. */
        next = prev;
        while ( SV_NEXT_P( next ) )
        {
            prev = SV_NEXT_P( next );
            if ( SV_MEMORY_FREE_P( next ) == 0 )
                free( SV_DATA_P( next ) );
            free( next );
            next = prev;
        }
        free( SV_DATA_P( next ) );
        free( next );
    }
	free(stack);
}









