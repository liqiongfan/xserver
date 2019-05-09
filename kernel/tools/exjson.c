/**
 * File:exjson.c for project exjson.
 * Author: Josin
 * Email: xeapplee@gmail.com
 * Website: https://www.supjos.cn
 */

#include "exjson.h"

EXJSON_V *
INIT_EXJSON_V()
{
    EXJSON_V *ptr = malloc(sizeof(EXJSON_V));
    assert( ptr != NULL );
    memset(ptr, 0, sizeof(EXJSON_V));
    
    EV_NAME_P(ptr) = NULL;
    EV_VALUE_P(ptr) = NULL;
    EV_TYPE_P(ptr) = 0;
    return ptr;
}

EXJSON *
INIT_EXJSON()
{
    EXJSON *ptr = malloc(sizeof(EXJSON));
    assert( ptr != NULL );
    memset(ptr, 0, sizeof(EXJSON));
    
    E_DATA_P(ptr) = NULL;
    E_NUM_P(ptr) = 0;
    E_TYPE_P(ptr) = 0;
    return ptr;
}

int add_object_int(EXJSON *exjson, char *key, int val)
{
    EXJSON_V *val_ptr  = E_DATA_P(exjson),
             *temp_ptr = INIT_EXJSON_V(),
             *ptr;
    unsigned long size = E_NUM_P(exjson) + 1,
                  key_len = strlen(key);
    
    /* Allocate key memory and store it. */
    EV_NAME_P(temp_ptr) = malloc(sizeof(char) * (key_len + 1));
    assert(EV_NAME_P(temp_ptr) != NULL);
    memset(EV_NAME_P(temp_ptr), 0, key_len + 1);
    memcpy(EV_NAME_P(temp_ptr), key, key_len);
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = malloc( sizeof(int) );
    assert(EV_VALUE_P(temp_ptr) != NULL);
    memcpy(EV_VALUE_P(temp_ptr), &val, sizeof(int));
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_INT;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    assert(ptr != NULL);
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_OBJECT;
}

int add_object_double(EXJSON *exjson, char *key, double val)
{
    EXJSON_V *val_ptr  = E_DATA_P(exjson),
             *temp_ptr = INIT_EXJSON_V(),
             *ptr;
    unsigned long size = E_NUM_P(exjson) + 1,
              key_len = strlen(key);
    
    /* Allocate key memory and store it. */
    EV_NAME_P(temp_ptr) = malloc(sizeof(char) * (key_len + 1));
    assert(EV_NAME_P(temp_ptr) != NULL);
    memset(EV_NAME_P(temp_ptr), 0, (key_len + 1));
    memcpy(EV_NAME_P(temp_ptr), key, (key_len));
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = malloc( sizeof( double) );
    assert(EV_VALUE_P(temp_ptr) != NULL);
    memcpy(EV_VALUE_P(temp_ptr), &val, sizeof( double ));
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_DOUBLE;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    assert(ptr != NULL);
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_OBJECT;
}

int add_object_string(EXJSON *exjson, char *key, char *val)
{
    EXJSON_V *val_ptr  = E_DATA_P(exjson),
             *temp_ptr = INIT_EXJSON_V(),
             *ptr;
    unsigned long size = E_NUM_P(exjson) + 1,
        key_len = strlen(key), val_len = strlen(val);
    
    /* Allocate key memory and store it. */
    EV_NAME_P(temp_ptr) = malloc(sizeof(char) * (key_len + 1));
    assert(EV_NAME_P(temp_ptr) != NULL);
    memset(EV_NAME_P(temp_ptr), 0, key_len + 1);
    memcpy(EV_NAME_P(temp_ptr), key, key_len);
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = malloc( sizeof( char) * ( val_len + 1 ));
    memset(EV_VALUE_P(temp_ptr), 0, val_len + 1);
    assert(EV_VALUE_P(temp_ptr) != NULL);
    memcpy(EV_VALUE_P(temp_ptr), val, (val_len));
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_STRING;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    assert(ptr != NULL);
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_OBJECT;
}

int add_object_object(EXJSON *exjson, char *key, void *val)
{
    EXJSON_V *val_ptr  = E_DATA_P(exjson),
             *temp_ptr = INIT_EXJSON_V(),
             *ptr;
    unsigned long size = E_NUM_P(exjson) + 1,
        key_len = strlen(key);
    
    /* Allocate key memory and store it. */
    EV_NAME_P(temp_ptr) = malloc(sizeof(char) * (key_len + 1));
    assert(EV_NAME_P(temp_ptr) != NULL);
    memset(EV_NAME_P(temp_ptr), 0, key_len + 1);
    memcpy(EV_NAME_P(temp_ptr), key, key_len);
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = val;
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_OBJECT;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    assert(ptr != NULL);
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_OBJECT;
}

int add_object_array(EXJSON *exjson, char *key, void *val)
{
    EXJSON_V *val_ptr  = E_DATA_P(exjson),
             *temp_ptr = INIT_EXJSON_V(),
             *ptr;
    unsigned long size = E_NUM_P(exjson) + 1,
        key_len = strlen(key);
    
    /* Allocate key memory and store it. */
    EV_NAME_P(temp_ptr) = malloc(sizeof(char) * (key_len + 1));
    assert(EV_NAME_P(temp_ptr) != NULL);
    memset(EV_NAME_P(temp_ptr), 0, key_len + 1);
    memcpy(EV_NAME_P(temp_ptr), key, key_len);
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = val;
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_ARRAY;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V) * size);
    assert(ptr != NULL);
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_OBJECT;
}

int add_object_ptr(EXJSON *exjson, char *key, void *val, unsigned char val_type)
{
    switch ( val_type )
    {
        case EXJSON_INT:
            return add_object_int(exjson, key, *(int *)val);
        case EXJSON_DOUBLE:
            return add_object_double(exjson, key, *( double *)val);
        case EXJSON_STRING:
            return add_object_string(exjson, key, (char *)val);
        case EXJSON_OBJECT:
            return add_object_object(exjson, key, val);
        case EXJSON_ARRAY:
            return add_object_array(exjson, key, val);
    }
    return 0;
}

int add_array_int(EXJSON *exjson, int val)
{
    EXJSON_V *val_ptr  = E_DATA_P(exjson),
             *temp_ptr = INIT_EXJSON_V(),
             *ptr;
    unsigned long size = E_NUM_P(exjson) + 1;

    /* Allocate key memory and store it. */
    EV_NAME_P(temp_ptr) = NULL;
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = malloc( sizeof(int) );
    assert(EV_VALUE_P(temp_ptr) != NULL);
    memcpy(EV_VALUE_P(temp_ptr), &val, sizeof(int));
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_INT;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    assert(ptr != NULL);
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_ARRAY;
}

int add_array_double(EXJSON *exjson, double val)
{
    EXJSON_V *val_ptr  = E_DATA_P(exjson),
             *temp_ptr = INIT_EXJSON_V(),
             *ptr;
    unsigned long size = E_NUM_P(exjson) + 1;
    
    /* Allocate key memory and store it. */
    EV_NAME_P(temp_ptr) = NULL;
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = malloc( sizeof( double ) );
    assert(EV_VALUE_P(temp_ptr) != NULL);
    memcpy(EV_VALUE_P(temp_ptr), &val, sizeof( double ));
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_DOUBLE;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    assert(ptr != NULL);
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_ARRAY;
}

int add_array_string(EXJSON *exjson, char *val)
{
    EXJSON_V *val_ptr  = E_DATA_P(exjson),
             *temp_ptr = INIT_EXJSON_V(),
             *ptr;
    unsigned long size = E_NUM_P(exjson) + 1,
                  val_len = strlen(val);
    
    /* Allocate key memory and store it. */
    EV_NAME_P(temp_ptr) = NULL;
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = malloc( sizeof( char) * ( val_len + 1 ));
    memset(EV_VALUE_P(temp_ptr), 0, val_len + 1);
    assert(EV_VALUE_P(temp_ptr) != NULL);
    memcpy(EV_VALUE_P(temp_ptr), val, (val_len));
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_STRING;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    assert(ptr != NULL);
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_ARRAY;
}

int add_array_object(EXJSON *exjson, void *val)
{
    EXJSON_V *val_ptr  = E_DATA_P(exjson),
             *temp_ptr = INIT_EXJSON_V(),
             *ptr;
    unsigned long size = E_NUM_P(exjson) + 1;
    
    /* Allocate key memory and store it. */
    EV_NAME_P(temp_ptr) = NULL;
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = val;
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_OBJECT;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    assert(ptr != NULL);
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_ARRAY;
}

int add_array_array(EXJSON *exjson, void *val)
{
    EXJSON_V *val_ptr  = E_DATA_P(exjson),
             *temp_ptr = INIT_EXJSON_V(),
             *ptr;
    unsigned long size = E_NUM_P(exjson) + 1;
    
    /* Allocate key memory and store it. */
    EV_NAME_P(temp_ptr) = NULL;
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = val;
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_ARRAY;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    assert(ptr != NULL);
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_ARRAY;
}

int add_array_ptr(EXJSON *exjson, void *val, unsigned char val_type)
{
    switch (val_type)
    {
        case EXJSON_INT:
            return add_array_int(exjson, *(int *)val);
        case EXJSON_DOUBLE:
            return add_array_double(exjson, *(double *)val);
        case EXJSON_STRING:
            return add_array_string(exjson, (char *)val);
        case EXJSON_ARRAY:
            return add_array_array(exjson, val);
        case EXJSON_OBJECT:
            return add_array_object(exjson, val);
    }
    return 0;
}

EXJSON *
/* Get the value from exjson with key */
exjson_get_array_or_object_from_key(EXJSON *exjson, char *key_name)
{
	EXJSON_V *temp = E_DATA_P(exjson);
	unsigned long i = 0, num = E_NUM_P(exjson);
	if ( E_TYPE_P(exjson) == EX_ARRAY )
	{
		printf("Array only can't be get by index.\n");
		return NULL;
	}

	for ( ; i < num; i++ )
	{
		if ( strncmp(key_name, EV_NAME_P(temp), strlen(key_name)) == 0 )
		{
			return EV_VALUE_P(temp);
		}
		temp = temp + 1;
	}

	return NULL;
}

EXJSON *
exjson_get_array_or_object_from_index(EXJSON *exjson, int index)
{
	EXJSON_V *temp = E_DATA_P(exjson);
	unsigned long i = 0, num = E_NUM_P(exjson);
	if ( E_TYPE_P(exjson) == EX_OBJECT )
	{
		printf("Object only can be get with index.\n");
		return NULL;
	}

	if ( E_NUM_P(exjson) < index ) {
		printf("Index out of range!");
		return NULL;
	}

	temp = temp + index;

	return EV_VALUE_P(temp);
}

void *
exjson_get_val_from_key(EXJSON *exjson, char *key)
{
	EXJSON_V *temp = E_DATA_P(exjson);
	unsigned long i = 0, num = E_NUM_P(exjson);

	for ( ; i < num; i++ )
	{
		if (strncmp(EV_NAME_P(temp), key, strlen(key)) == 0)
		{
			return EV_VALUE_P(temp);
		}
		temp = temp + 1;
	}

	return NULL;
}

void *
exjson_get_val_from_index(EXJSON *exjson, int index)
{
	EXJSON_V *temp = E_DATA_P(exjson);
	unsigned long num = E_NUM_P(exjson);

	if ( num <= index ) {
		printf("Index out of range!");
		return NULL;
	}

	temp = temp + index;
	return EV_VALUE_P(temp);
}


void print_exjson(EXJSON *exjson, int _num)
{
    EXJSON_V *temp = E_DATA_P(exjson);
    int j = 0;
    unsigned long i = 0, num = E_NUM_P(exjson);

    switch( E_TYPE_P(exjson) )
    {
        case EX_OBJECT:
            printf("{\n"); break;
        case EX_ARRAY:
            printf("[\n"); break;
    }

    for ( ; i < num; i++ )
    {
    	if ( EV_NAME_P(temp) ) {
            for (j = 0; j <= _num; ++j) {
                printf("\t");
            }
            printf("%s: ", EV_NAME_P(temp));
        }

        switch (EV_TYPE_P(temp))
        {
            case EXJSON_INT:
                if ( EV_NAME_P(temp) == NULL )
                for (j = 0; j <= _num; ++j) {
                    printf("\t");
                }
				printf("%d\n", *(int *)EV_VALUE_P(temp));
                break;
            case EXJSON_DOUBLE:
                if ( EV_NAME_P(temp) == NULL )
                for (j = 0; j <= _num; ++j) {
                    printf("\t");
                }
	            printf("%f\n", *(double *)EV_VALUE_P(temp));
                break;
            case EXJSON_STRING:
                if ( EV_NAME_P(temp) == NULL )
                for (j = 0; j <= _num; ++j) {
                    printf("\t");
                }
	            printf("%s\n", (char *)EV_VALUE_P(temp));
                break;
            case EXJSON_ARRAY:
            case EXJSON_OBJECT:
                print_exjson(EV_VALUE_P(temp), _num + 1);
        }
        temp = temp + 1;
    }


    for (j = 0; j < _num; ++j) {
        printf("\t");
    }
    switch( E_TYPE_P(exjson) )
    {
        case EX_OBJECT:
            printf("}\n"); break;
        case EX_ARRAY:
            printf("]\n"); break;
    }
}

void destroy_exjson(EXJSON *exjson)
{
    EXJSON_V *temp = E_DATA_P(exjson);
    unsigned long i = 0, num = E_NUM_P(exjson);
    static int _num = 0;
    
    switch( E_TYPE_P(exjson) )
    {
        case EX_OBJECT:
        case EX_ARRAY:
        {
            for ( ; i < num; i++ )
            {
                free(EV_NAME_P(temp));
                EV_NAME_P(temp) = NULL;
                
                if ( EV_TYPE_P(temp) == EXJSON_OBJECT || EV_TYPE_P(temp) == EXJSON_ARRAY )
                {
                    _num++;
                    destroy_exjson(EV_VALUE_P(temp));
                    _num--;
                }
                else
                {
                    free( EV_VALUE_P( temp ) );
                    EV_VALUE_P( temp ) = NULL;
                    temp = temp + 1;
                }
            }
        }
    }

    if (_num == 0) free(exjson);
}
