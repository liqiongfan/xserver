/**
 * File:hashtable.c for project Xserver.
 * Author: Josin
 * Email: xeapplee@gmail.com
 * Website: https://www.supjos.cn
 */

#include "../kernel/tools/hashtable.h"

int main(int argc, char *argv[])
{
    HashTable hashTable;
    INIT_HASHTABLE(&hashTable);
    
    add_index_int(&hashTable,      0, 12);
    add_index_int(&hashTable,      1, 11);
    add_index_int(&hashTable,      2, 10);
    add_index_int(&hashTable,      3, 13);
    add_index_int(&hashTable,      4, 14);
    add_index_string_l(&hashTable, 5, "Hello World", 11);
    add_index_string(&hashTable,   6, "Xserver so good.");
    add_index_int(&hashTable,      7, 16);
    add_index_int(&hashTable,      8, 15);
    xserver_hash_add(&hashTable,  "0", 1, IS_STRING, "make song", 9);
    xserver_hash_add(&hashTable,  "1", 1, IS_STRING, "make song", 9);
    xserver_hash_add(&hashTable,  "2", 1, IS_STRING, "make song", 9);
    xserver_hash_add(&hashTable,  "3", 1, IS_STRING, "make song", 9);
    
    Bucket *bucket;
    HASH_FOREACH(hashTable, bucket) {
        if ( bucket->key ) {
            printf("%s\t", bucket->key);
        }
        printf("%ld\t", _bucket->key_hash);
        switch (T_TYPE_PTR(_bucket))
        {
            case IS_CHAR:
            case IS_INT:
                printf("%d\n", T_IVAL_PTR(_bucket));
                break;
            case IS_STRING:
                printf("%s\n", T_SVAL_PTR(_bucket));
                break;
        }
    } HASH_FOREACH_END();
    
    xserver_hashtable_destroy(&hashTable, 0);
    
    return 0;
}
