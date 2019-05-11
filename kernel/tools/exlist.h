/**
 * File:exlist.h for project Exlist.
 * Author: Josin
 * Email: xeapplee@gmail.com
 * Website: https://www.supjos.cn
 */

#ifndef LIBRARY_EXLIST_H
#define LIBRARY_EXLIST_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef __BEGIN_DECLS
    #define __BEGIN_DECLS extern "C" {
#endif
#ifndef __END_DECLS
    #define __END_DECLS };
#endif

__BEGIN_DECLS

typedef void (*__list_destructor__)(void *);

typedef struct __EXLIST_V
{
    struct __EXLIST_V   *prev;
    struct __EXLIST_V   *next;
    void *value_ptr;
    __list_destructor__ func;
} EXLIST_V;
#define ELV_PREV(list) (list).prev
#define ELV_PREV_P(list) ELV_PREV(*(list))
#define ELV_NEXT(list) (list).next
#define ELV_NEXT_P(list) ELV_NEXT(*(list))
#define ELV_VALUE(list) (list).value_ptr
#define ELV_VALUE_P(list) ELV_VALUE(*(list))
#define ELV_FUNC(list) (list).func
#define ELV_FUNC_P(list) ELV_FUNC(*(list))

typedef struct __EXLIST
{
    struct __EXLIST_V *lists;
    struct __EXLIST_V *head;
    struct __EXLIST_V *tail;
    unsigned long ele_nums;
} EXLIST;
#define EL_LISTS(list) (list).lists
#define EL_LISTS_P(list) EL_LISTS(*(list))
#define EL_HEAD(list) (list).head
#define EL_HEAD_P(list) EL_HEAD(*(list))
#define EL_TAIL(list) (list).tail
#define EL_TAIL_P(list) EL_TAIL(*(list))
#define EL_NUM(list) (list).ele_nums
#define EL_NUM_P(list) EL_NUM(*(list))


EXLIST *INIT_EXLIST();
EXLIST_V *INIT_EXLIST_V();
int push_tail(EXLIST *, void *, __list_destructor__);
int append_head(EXLIST *, void *, __list_destructor__);
void destroy_exlist(EXLIST *);

#define EXLIST_FOREACH(list, value) do {\
    if ( list ) {  \
        EXLIST_V *ptr = EL_HEAD_P(list); \
        for (; ptr != NULL; ptr = ELV_NEXT_P(ptr) )\
        {\
            value = ptr;
        
#define EXLIST_FOREACH_END() }}}while(0)

__END_DECLS

#endif /* LIBRARY_EXLIST_H */
