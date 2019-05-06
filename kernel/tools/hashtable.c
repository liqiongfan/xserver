/**
 * File:tree.c for project Xserver.
 * Author: Josin
 * Email: xeapplee@gmail.com
 * Website: https://www.supjos.cn
 */

#include "hashtable.h"

__BEGIN_DECL

void
/* Init the hash table for later use. */
INIT_HASHTABLE(struct __hash_table *hashTable)
{
    Bucket *_bucket = (Bucket *)malloc(sizeof(struct __bucket) * BUCKET_SIZE);
    assert(_bucket != EMPTY_PTR);
    memset(_bucket, 0, sizeof(_bucket) * BUCKET_SIZE);
    _bucket->bucket_status = 0;
    _bucket->value_type = 0;
    _bucket->key_hash = 0;
    _bucket->key = EMPTY_PTR;
    _bucket->key_length = 0;
    _bucket->vval = EMPTY_PTR;
    _bucket->str.sval = EMPTY_PTR;
    _bucket->str.len = 0;
    _bucket->dval = 0.0;
    _bucket->ival = 0;
    _bucket->cval = 0;
    
    hashTable->arBuckets = _bucket;
    hashTable->destructor_ptr = _destructor_hash_table_func_;
    hashTable->element_size = 0;                /* Currently used size */
    hashTable->free_table_size = BUCKET_SIZE;   /* The free size which can be used */
    hashTable->table_size = BUCKET_SIZE;        /* Total size */
    hashTable->head = _bucket;
    hashTable->tail = _bucket + (BUCKET_SIZE - 1);
}

static int
/* The kernel function to add the key & value into hash table
 * remember that: value_len will omitted other than when value_type is IS_STRING */
hash_table_symtable_update(struct __hash_table *hashTable, ulong index,
    uchar value_type, void *value, ulong value_len)
{
    if ( hashTable->table_size - 1 < index ) {
        ulong need_size;
        if ( ( index - hashTable->table_size + 1 ) < BUCKET_SIZE )
        {
            need_size = hashTable->table_size + BUCKET_SIZE;
        }
        else
        {
            need_size = index + BUCKET_SIZE;
        }
        void *_temp_ptr = realloc(hashTable->arBuckets, sizeof(Bucket) * need_size );
        assert(_temp_ptr != EMPTY_PTR);
        hashTable->arBuckets = _temp_ptr;
        hashTable->free_table_size = need_size - hashTable->table_size;
        hashTable->table_size = need_size;
    }
    
    /* Set the value */
    Bucket *__bucket = ( hashTable->arBuckets + index );
    __bucket->key = EMPTY_PTR;
    __bucket->key_hash = index;
    __bucket->value_type = value_type;
    __bucket->bucket_status = BUCKET_IN_USE;
    switch(value_type) {
        case IS_CHAR:
        case IS_INT:
            __bucket->ival = *((int *)value);
            break;
        case IS_DOUBLE:
            __bucket->dval = *((double *)value);
            break;
        case IS_STRING:
            __bucket->str.sval = (char *)value;
            __bucket->str.len = value_len;
            break;
        case IS_PTR:
            __bucket->vval = value;
            break;
        default:
            return false;
    }
    hashTable->free_table_size--;
    hashTable->element_size++;
    return true;
}

int
/* The kernel function to add the key & value into hash table
 * remember that: value_len will omitted other than when value_type is IS_STRING
 * Workflow: if element_size is equal to table_size increase it by BUCKET_SIZE */
hash_table_key_symtable_update(struct __hash_table *hashTable, char *key, ulong key_len,
    uchar value_type, void *value, ulong value_len)
{
    /* Calc the hash code */
    ulong hash_h = xserver_inline_hash_func(key, key_len);
    
    /* check the left space, which not used */
    if ( hashTable->element_size + 10 >= hashTable->table_size )
    {
        ulong need_size = hashTable->table_size + BUCKET_SIZE;
        void *_temp_ptr = realloc(hashTable->arBuckets, sizeof(Bucket) * (need_size));
        assert(_temp_ptr != EMPTY_PTR);
        hashTable->arBuckets = _temp_ptr;
        hashTable->free_table_size = need_size - hashTable->table_size;
        hashTable->table_size = need_size;
    }
    
    /* Get the data pos. */
    ulong index = hash_h % (hashTable->table_size);
    
    /* Set the value */
    Bucket *__bucket = ( hashTable->arBuckets + index );
    __bucket->key = key;
    __bucket->key_length = key_len;
    __bucket->key_hash = index;
    __bucket->value_type = value_type;
    __bucket->bucket_status = BUCKET_IN_USE;
    switch(value_type) {
        case IS_CHAR:
        case IS_INT:
            __bucket->ival = *((int *)value);
            break;
        case IS_DOUBLE:
            __bucket->dval = *((double *)value);
            break;
        case IS_STRING:
            __bucket->str.sval = (char *)value;
            __bucket->str.len = value_len;
            break;
        case IS_PTR:
            __bucket->vval = value;
            break;
        default:
            return false;
    }
    
    /* After each add op. increase the element_size */
    hashTable->free_table_size--;
    hashTable->element_size++;
    return true;
}

int
add_index_int(hash_table *hashTable, ulong index, int _ival)
{
    return hash_table_symtable_update(hashTable, index, IS_INT, &_ival, 0);
}

int
add_index_double(hash_table *hashTable, ulong index, double _dval)
{
    return hash_table_symtable_update(hashTable, index, IS_DOUBLE, &_dval, 0);
}

int
add_index_char(hash_table *hashTable, ulong index, char _cval)
{
    return hash_table_symtable_update(hashTable, index, IS_CHAR, &_cval, 0);
}

int
add_index_string_l(hash_table *hashTable, ulong index, char *str, ulong str_len)
{
    return hash_table_symtable_update(hashTable, index, IS_STRING, str, str_len);
}

int
add_index_string(hash_table *hashTable, ulong index, char *str)
{
    return add_index_string_l(hashTable, index, str, strlen(str));
}

int
add_index_ptr(hash_table *hashTable, ulong index, void *_ptr)
{
    return hash_table_symtable_update(hashTable, index, IS_PTR, _ptr, 0);
}

int
xserver_hash_add(hash_table *hashTable, char *key, ulong key_len, uchar value_type, void *value, ulong value_len)
{
    return hash_table_key_symtable_update(hashTable, key, key_len, value_type, value, value_len);
}

void
/* To destroy the hash table if the parameter _free_table_ set to true or value not 0
 * kernel will free the memory by the kernel libc's free function */
xserver_hashtable_destroy(struct __hash_table *hashTable, int _free_table_)
{
    int _i;
    for ( _i = 0; _i < hashTable->table_size; ++_i )
    {
        Bucket *_bucket = hashTable->arBuckets + _i;
        if ( T_STATUS_PTR(_bucket) == BUCKET_IN_USE )
        {
            if ( _free_table_ ) {
                hashTable->destructor_ptr(_bucket);
            }
        }
    }
    free(hashTable->arBuckets);
}

Bucket *
xserver_hash_index_find(struct __hash_table* hashTable, ulong index)
{
    if ( index > hashTable->table_size ) return EMPTY_PTR;
    
    return hashTable->arBuckets + index;
}

Bucket *
xserver_hash_str_l_find(struct __hash_table * hashTable, char *key, ulong key_len)
{
    ulong __k_h__ = xserver_inline_hash_func(key, key_len);
    ulong _h = __k_h__ % hashTable->table_size;
    if ( _h > hashTable->table_size ) return EMPTY_PTR;
    return hashTable->arBuckets + _h;
}

Bucket *
xserver_hash_str_find(struct __hash_table * hashTable, char *key)
{
    return xserver_hash_str_l_find(hashTable, key, strlen(key));
}

__END_DECL






