/**
 * File:exlist.c for project Exlist.
 * Author: Josin
 * Email: xeapplee@gmail.com
 * Website: https://www.supjos.cn
 */

#include "exlist.h"

EXLIST *
INIT_EXLIST()
{
    EXLIST *ptr = malloc( sizeof(EXLIST) );
    assert(ptr != NULL);
    memset(ptr, 0, sizeof(EXLIST));
    EL_NUM_P(ptr) = 0;
    EL_HEAD_P(ptr) = EL_TAIL_P(ptr) = EL_LISTS_P(ptr) = NULL;
    return ptr;
}

EXLIST_V *
INIT_EXLIST_V()
{
    EXLIST_V *ptr = malloc( sizeof(EXLIST_V) );
    assert(ptr != NULL);
    memset(ptr, 0, sizeof(EXLIST_V));
    ELV_VALUE_P(ptr) = ELV_NEXT_P(ptr) = ELV_PREV_P(ptr) = NULL;
    return ptr;
}

/* Push the data into the end of the list
 * notice that kernel will not malloc any memory to store the data
 * RETURN VALUE:
 * 1: when successful otherwise 0 returned */
int push_tail(EXLIST *exlist, void *data, __list_destructor__ _free_func_)
{
    if ( !exlist ) return 0;
    
    EXLIST_V *tail = EL_TAIL_P(exlist), *value_ptr = NULL, *temp_ptr;
    
    value_ptr = INIT_EXLIST_V();
    ELV_VALUE_P(value_ptr) = data;
    ELV_FUNC_P(value_ptr) = _free_func_;
    
    if ( !tail )
    {
        /* empty list now, insert into the list and set the head & tail node to this newly node */
        EL_LISTS_P(exlist) = EL_HEAD_P(exlist) = EL_TAIL_P(exlist) = value_ptr;
        EL_NUM_P(exlist)++;
    }
    else
    {
        ELV_NEXT_P(tail) = value_ptr;
        ELV_PREV_P(value_ptr) = tail;
        EL_TAIL_P(exlist) = value_ptr;
    }
    
    return 1;
}

int append_head(EXLIST *exlist, void *data, __list_destructor__ _free_func_)
{
    if ( !exlist ) return 0;
    
    EXLIST_V *head = EL_HEAD_P(exlist), *value_ptr = NULL, *temp_ptr;
    
    value_ptr = INIT_EXLIST_V();
    ELV_VALUE_P(value_ptr) = data;
    ELV_FUNC_P(value_ptr) = _free_func_;
    
    if ( !head )
    {
        /* empty list now, insert into the list and set the head & tail node to this newly node */
        EL_LISTS_P(exlist) = EL_HEAD_P(exlist) = EL_TAIL_P(exlist) = value_ptr;
        EL_NUM_P(exlist)++;
    }
    else
    {
        ELV_PREV_P(head) = value_ptr;
        ELV_NEXT_P(value_ptr) = head;
        EL_HEAD_P(exlist) = value_ptr;
    }
    
    return 1;
}

void destroy_exlist(EXLIST *exlist)
{
    if ( !exlist ) return ;
    
    EXLIST_V *head = EL_HEAD_P(exlist), *temp_ptr = head, *middle_ptr;
    if ( !head ) { free(exlist); return; }
    
    while ( temp_ptr )
    {
        middle_ptr = ELV_NEXT_P(temp_ptr);
        
        if ( ELV_FUNC_P(temp_ptr) )
        {
            ELV_FUNC_P(temp_ptr)(temp_ptr);
        }
        free(temp_ptr);
        temp_ptr = middle_ptr;
    }
    
    free(exlist);
}