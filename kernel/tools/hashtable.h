/**
 * File:tree.h for project Xserver.
 * Author: Josin
 * Email: xeapplee@gmail.com
 * Website: https://www.supjos.cn
 */

#ifndef XSERVER_TREE_H
#define XSERVER_TREE_H

#include "../config.h"
#include "hash.h"

__BEGIN_DECL

enum _BUCKET_STATUS
{
    BUCKET_DELETE = 1,
    BUCKET_NORMAL = 2,
    BUCKET_IN_USE = 3
};

/* Tree node contains the tree real data store info. */
typedef struct __bucket
{
    int    ival;
    char   cval;
    double dval;
    /* Only the following types need to free its memory after used.
     * if stores the string, also store it's length for other use */
    struct {
        char   *sval;
        ulong   len;
    } str;
    void  *vval;
    
    /* Below are the key info. */
    char *key;
    ulong key_length;
    ulong key_hash;
    /* The bucket value type to pick the value */
    uchar value_type;
    /* The bucket status */
    uchar bucket_status;
} Bucket;

#define IS_INT     0
#define IS_CHAR    1
#define IS_DOUBLE  2
#define IS_STRING  3
#define IS_PTR     4

#define T_STATUS(_t) (_t).bucket_status
#define T_STATUS_PTR(_t) T_STATUS(*_t)
#define T_TYPE(_t) (_t).value_type
#define T_TYPE_PTR(_t) T_TYPE(*_t)
#define T_IVAL(_t) (_t).ival
#define T_IVAL_PTR(_t) T_IVAL(*_t)
#define T_CVAL(_t) (_t).cval
#define T_CVAL_PTR(_t) T_CVAL(*_t)
#define T_DVAL(_t) (_t).dval
#define T_DVAL_PTR(_t) (_t).dval
#define T_SVAL(_t) (_t).str.sval
#define T_SVAL_LEN(_t) (_t).str.len
#define T_SVAL_PTR(_t) T_SVAL(*_t)
#define T_SVAL_LEN_PTR(_t) T_SVAL_LEN(*_t)
#define T_VOID(_t) (_t).vval
#define T_VOID_PTR(_t) T_VOID(*_t)

#define TVAL_KEY(_t, _k, _l) {\
    Bucket *_p = _t;\
    (_p)->key = _k;\
    (_p)->key_length = _l;\
    (_p)->key_hash = xserver_inline_hash_func(_k, _l);\
}
#define TVAL_INT(_t, _i) {\
    Bucket *_p = _t;\
    (_p)->ival = _i;\
    T_TYPE_PTR(_p) = IS_INT;\
}
#define TVAL_CHAR(_t, _c) {\
    Bucket *_p = _t;\
    (_p)->cval = _c;\
    T_TYPE_PTR(_p) = IS_CHAR;\
}
#define TVAL_DOUBLE(_t, _d) {\
    Bucket *_p = _t;\
    (_p)->dval = _d;\
    T_TYPE_PTR(_p) = IS_DOUBLE;\
}
#define TVAL_STRING(_t, _s) {\
    Bucket *_p = _t;\
    (_p)->str.sval = _s;\
    (_p)->str.len = strlen(_s);\
    T_TYPE_PTR(_p) = IS_STRING;\
}
#define TVAL_PTR(_t, _p) {\
    Bucket *_p = _t;\
    (_p).vval = _p;\
    T_TYPE_PTR(_p) = IS_PTR;\
}
#define TVAL_DELETE(_t) {\
    (_t).bucket_status = BUCKET_DELETE;\
}
#define TVAL_NORMAL(_t) {\
    (_t).bucket_status = BUCKET_NORMAL;\
}

typedef void (*_destructor_hash_table_)(void *data);
static void _destructor_hash_table_func_(void *_bucket)
{
    struct __bucket *_pp = (struct __bucket *)_bucket;
    switch (T_TYPE_PTR(_pp))
    {
        case IS_STRING:
            if ( (_pp)->str.sval ) {
                free((_pp)->str.sval);
                (_pp)->str.sval = EMPTY_PTR;
            }
            break;
        case IS_PTR:
            if ( (_pp)->vval ) {
                free((_pp)->vval);
                (_pp)->vval = EMPTY_PTR;
            }
            break;
    }
    
    /* Other types only to delete the key and the bucket memory */
    if ( (_pp)->key )
    {
        free((_pp)->key);
        (_pp)->key = EMPTY_PTR;
    }
    
    /* Bucket memory */
    free(_pp);
    _pp = EMPTY_PTR;
}

/* hashtable typedef
 * This type allocate from the stack not the malloc function */
typedef struct __hash_table
{
    ulong table_size;       /* equals to free_table_size + element_size */
    ulong free_table_size;
    ulong element_size;
    struct __bucket *head;
    struct __bucket *tail;
    struct __bucket *arBuckets;
    _destructor_hash_table_ destructor_ptr;
} hash_table;

typedef hash_table HashTable;

void
INIT_HASHTABLE(HashTable *);

int
add_index_int(HashTable *hashTable, ulong index, int _ival);

int
add_index_double(HashTable *hashTable, ulong index, double _dval);

int
add_index_char(HashTable *hashTable, ulong index, char _cval);

int
add_index_string_l(HashTable *hashTable, ulong index, char *str, ulong str_len);

int
add_index_ptr(HashTable *hashTable, ulong index, void *_ptr);

int
add_index_string(HashTable *hashTable, ulong index, char *str);

int
xserver_hash_add(HashTable *hashTable, char *key, ulong key_len, uchar value_type, void *value, ulong value_len);

void
xserver_hashtable_destroy(HashTable *, int );

Bucket *
xserver_hash_index_find(HashTable*, ulong index);

Bucket *
xserver_hash_str_l_find(HashTable *, char *key, ulong key_len);

Bucket *
xserver_hash_str_find(HashTable *, char *key);

/* The macros to iterate the hashtable
 * skip the deleted hash table list node */
#define HASH_FOREACH(hash_table, bucket) do {\
    int __hash_index__ = 0;\
    for ( ; __hash_index__ < (hash_table).table_size; ++__hash_index__ )    \
    {\
        Bucket *_bucket = (hash_table).arBuckets + __hash_index__;\
        if ( _bucket->bucket_status == BUCKET_IN_USE ) {\
            bucket = _bucket;
            
#define HASH_FOREACH_END() }}}while(0)

__END_DECL

#endif /* XSERVER_TREE_H */

