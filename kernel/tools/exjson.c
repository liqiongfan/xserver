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
    if ( ptr == NULL )
    {
        free(ptr); return NULL;
    }
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
    if ( ptr == NULL )
    {
        free(ptr); return NULL;
    }
    memset(ptr, 0, sizeof(EXJSON));
    
    E_DATA_P(ptr) = NULL;
    E_NUM_P(ptr) = 0;
    E_TYPE_P(ptr) = 0;
    return ptr;
}

int add_object_int(EXJSON *exjson, char *key, long val)
{
    EXJSON_V *val_ptr  = E_DATA_P(exjson),
             *temp_ptr = INIT_EXJSON_V(),
             *ptr;
    unsigned long size = E_NUM_P(exjson) + 1,
                  key_len = strlen(key);
    
    /* Allocate key memory and store it. */
    EV_NAME_P(temp_ptr) = malloc(sizeof(char) * (key_len + 1));
    if ( EV_NAME_P(temp_ptr) == NULL )
    {
        free(EV_NAME_P(temp_ptr)); return 0;
    }
    memset(EV_NAME_P(temp_ptr), 0, key_len + 1);
    memcpy(EV_NAME_P(temp_ptr), key, key_len);
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = malloc( sizeof(long) );
    if ( EV_VALUE_P(temp_ptr) == NULL )
    {
        free(EV_VALUE_P(temp_ptr));return 0;
    }
    memcpy(EV_VALUE_P(temp_ptr), &val, sizeof(long));
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_INT;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    if ( ptr == NULL )
    {
        free(val_ptr); return 0;
    }
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    free(temp_ptr);
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_OBJECT;
    return 1;
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
    if ( EV_NAME_P(temp_ptr) == NULL )
    {
        free( EV_NAME_P(temp_ptr) ); return 0;
    }
    assert(EV_NAME_P(temp_ptr) != NULL);
    memset(EV_NAME_P(temp_ptr), 0, (key_len + 1));
    memcpy(EV_NAME_P(temp_ptr), key, (key_len));
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = malloc( sizeof( double) );
    if ( EV_VALUE_P(temp_ptr) == NULL )
    {
        free(EV_VALUE_P(temp_ptr)); return 0;
    }
    memcpy(EV_VALUE_P(temp_ptr), &val, sizeof( double ));
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_DOUBLE;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    if ( ptr == NULL )
    {
        free(val_ptr); return 0;
    }
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    free(temp_ptr);
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_OBJECT;
    return 1;
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
    if ( EV_NAME_P(temp_ptr) == NULL )
    {
        free( EV_NAME_P(temp_ptr) );return 0;
    }
    assert(EV_NAME_P(temp_ptr) != NULL);
    memset(EV_NAME_P(temp_ptr), 0, key_len + 1);
    memcpy(EV_NAME_P(temp_ptr), key, key_len);
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = malloc( sizeof( char) * ( val_len + 1 ));
    if ( EV_VALUE_P(temp_ptr) == NULL )
    {
        free( EV_VALUE_P(temp_ptr) ); return 0;
    }
    memset(EV_VALUE_P(temp_ptr), 0, val_len + 1);
    assert(EV_VALUE_P(temp_ptr) != NULL);
    memcpy(EV_VALUE_P(temp_ptr), val, (val_len));
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_STRING;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    if ( ptr == NULL )
    {
        free(val_ptr); return 0;
    }
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    free(temp_ptr);
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_OBJECT;
    return 1;
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
    if ( EV_NAME_P(temp_ptr) == NULL )
    {
        free( EV_NAME_P(temp_ptr) ); return 0;
    }
    memset(EV_NAME_P(temp_ptr), 0, key_len + 1);
    memcpy(EV_NAME_P(temp_ptr), key, key_len);
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = val;
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_OBJECT;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    if ( ptr == NULL )
    {
        free(val_ptr); return 0;
    }
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    free(temp_ptr);
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_OBJECT;
    return 1;
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
    if ( EV_NAME_P(temp_ptr) == NULL )
    {
        free( EV_NAME_P(temp_ptr) ); return 0;
    }
    memset(EV_NAME_P(temp_ptr), 0, key_len + 1);
    memcpy(EV_NAME_P(temp_ptr), key, key_len);
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = val;
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_ARRAY;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V) * size);
    if ( ptr == NULL )
    {
        free( val_ptr ); return 0;
    }
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    free(temp_ptr);
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_OBJECT;
    return 1;
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

int add_array_int(EXJSON *exjson, long val)
{
    EXJSON_V *val_ptr  = E_DATA_P(exjson),
             *temp_ptr = INIT_EXJSON_V(),
             *ptr;
    unsigned long size = E_NUM_P(exjson) + 1;

    /* Allocate key memory and store it. */
    EV_NAME_P(temp_ptr) = NULL;
    
    /* Allocate data memory and store it */
    EV_VALUE_P(temp_ptr) = malloc( sizeof( long) );
    if ( EV_VALUE_P(temp_ptr) == NULL )
    {
        free( EV_VALUE_P(temp_ptr) ); return 0;
    }
    memcpy(EV_VALUE_P(temp_ptr), &val, sizeof( long));
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_INT;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    if ( ptr == NULL )
    {
        free(val_ptr); return 0;
    }
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    free(temp_ptr);
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_ARRAY;
    return 1;
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
    if ( EV_VALUE_P(temp_ptr) == NULL )
    {
        free( EV_VALUE_P(temp_ptr) ); return 0;
    }
    memcpy(EV_VALUE_P(temp_ptr), &val, sizeof( double ));
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_DOUBLE;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    if ( ptr == NULL )
    {
        free( val_ptr ); return 0;
    }
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    free(temp_ptr);
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_ARRAY;
    return 1;
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
    if ( EV_VALUE_P(temp_ptr) == NULL )
    {
        free( EV_VALUE_P(temp_ptr) ); return 0;
    }
    memset(EV_VALUE_P(temp_ptr), 0, val_len + 1);
    memcpy(EV_VALUE_P(temp_ptr), val, (val_len));
    
    /* Set value type */
    EV_TYPE_P(temp_ptr) = EXJSON_STRING;
    
    /* add to exjson */
    ptr = realloc(val_ptr, sizeof(EXJSON_V)*size);
    if ( ptr == NULL )
    {
        free(val_ptr); return 0;
    }
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    free(temp_ptr);
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_ARRAY;
    return 1;
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
    if ( ptr == NULL )
    {
        free(val_ptr); return 0;
    }
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    free(temp_ptr);
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_ARRAY;
    return 1;
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
    if ( ptr == NULL )
    {
        free(val_ptr); return 0;
    }
    memcpy(ptr + E_NUM_P(exjson), temp_ptr, sizeof(EXJSON_V));
    E_NUM_P(exjson)++;
    
    E_DATA_P(exjson) = ptr;
    E_TYPE_P(exjson) = EX_ARRAY;
    return 1;
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
	if ( !exjson ) return NULL;
	EXJSON_V *temp = E_DATA_P(exjson);
	unsigned long i = 0, num = E_NUM_P(exjson);
	if ( E_TYPE_P(exjson) == EX_ARRAY )
	{
		perror("Array only can't be get by index");
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
    if ( !exjson ) return NULL;
	EXJSON_V *temp = E_DATA_P(exjson);
	if ( E_TYPE_P(exjson) == EX_OBJECT )
	{
		perror("Object only can be get with index");
		return NULL;
	}

	if ( E_NUM_P(exjson) < index ) {
		perror("Index out of range");
		return NULL;
	}

	temp = temp + index;

	return EV_VALUE_P(temp);
}

void *
exjson_get_val_from_key(EXJSON *exjson, char *key)
{
	if ( !exjson ) return NULL;
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
	if ( !exjson ) return NULL;
	EXJSON_V *temp = E_DATA_P(exjson);
	unsigned long num = E_NUM_P(exjson);

	if ( num <= index ) {
		perror("Index out of range");
		return NULL;
	}

	temp = temp + index;
	return EV_VALUE_P(temp);
}

void
/* Print EXJSON not fully ok, as the format has some mistask.
 * but encoding & decoding are perfectly ok. */
print_exjson(EXJSON *exjson, int _num)
{
	if ( !exjson ) return ;
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

static inline char *
/* for example:
 * char *str = malloc(sizeof(1000));
 * int _dest_space = 1000, _used_num = 0;
 * _exjson_strcat_(str, "hello", &_dest_space, &_used_num);
 * _exjson_strcat_(str, "world", &_dest_space, &_used_num); */
_exjson_strcat_(char *dest, char *source, int *_dest_space, int *_used_num)
{
    int _time_incr_ = 512;
    char *_temp_ptr = NULL;
    unsigned long _source_len = strlen(source);
    if ( *_used_num > ( *_dest_space - 1 ) )
    {
        _temp_ptr = realloc(dest, sizeof(char) * (*_dest_space + _time_incr_));
        if ( _temp_ptr == NULL )
        {
        	free(dest); return NULL;
        }
        assert(_temp_ptr != NULL);
        dest = _temp_ptr;
        *_dest_space+= _time_incr_;
    }
    /* if the source string is not enough to store */
    if ( _source_len > (*_dest_space - *_used_num) )
    {
        if ( _source_len > _time_incr_ )
        {
            _temp_ptr = realloc(dest, sizeof(char) * (*_dest_space + _source_len + 1));
            if ( _temp_ptr == NULL )
            {
            	free(dest); return NULL;
            }
            assert(_temp_ptr != NULL);
            dest = _temp_ptr;
            *_dest_space+= _source_len + 1;
        }
        else
        {
            _temp_ptr = realloc(dest, sizeof(char) * (*_dest_space + _time_incr_));
	        if ( _temp_ptr == NULL )
	        {
		        free(dest); return NULL;
	        }
            assert(_temp_ptr != NULL);
            dest = _temp_ptr;
            *_dest_space+= _time_incr_;
        }
    }
    
    /* Space is enough */
    strncat(dest, source, _source_len);
    *_used_num += _source_len;
    return dest;
}

/* Output the EXJSON structure to the JSON string
 * NOTE that: free the returned string after used
 * if not memory leak will occurred! */
char *encode_json(EXJSON *exjson)
{
    if ( !exjson ) return NULL;
    EXJSON_V *temp = E_DATA_P(exjson);
    int _sum = 1, _used_num = 0;
    unsigned long i = 0, num = E_NUM_P(exjson);
    
    char *inner_str = NULL;
    char *_result_str = malloc(sizeof(char) * (_sum + 1) );
    if ( _result_str == NULL )
    {
    	free(_result_str); return NULL;
    }
    assert(_result_str != NULL);
    memset(_result_str, 0, sizeof(char) * ( _sum + 1 ) );
    
    switch( E_TYPE_P(exjson) )
    {
        case EX_OBJECT:
            _result_str = _exjson_strcat_(_result_str, "{", &_sum, &_used_num); break;
        case EX_ARRAY:
            _result_str = _exjson_strcat_(_result_str, "[", &_sum, &_used_num); break;
    }
    
    for ( ; i < num; i++ )
    {
        if ( EV_NAME_P(temp) ) {
            _result_str = _exjson_strcat_(_result_str, "\"", &_sum, &_used_num);
            _result_str = _exjson_strcat_(_result_str, EV_NAME_P(temp), &_sum, &_used_num);
            _result_str = _exjson_strcat_(_result_str, "\":", &_sum, &_used_num);
        }
        
        char _temp[20] = {0};
        switch (EV_TYPE_P(temp))
        {
            case EXJSON_INT:
                memset(_temp, 0, 20);
                sprintf(_temp, "%ld", *(long *)EV_VALUE_P(temp));
                _result_str = _exjson_strcat_(_result_str, _temp, &_sum, &_used_num);
                break;
            case EXJSON_DOUBLE:
                memset(_temp, 0, 20);
                sprintf(_temp, "%f", *(double *)EV_VALUE_P(temp));
                _result_str = _exjson_strcat_(_result_str, _temp, &_sum, &_used_num);
                break;
            case EXJSON_STRING:
                _result_str = _exjson_strcat_(_result_str, "\"", &_sum, &_used_num);
                _result_str = _exjson_strcat_(_result_str, EV_VALUE_P(temp), &_sum, &_used_num);
                _result_str = _exjson_strcat_(_result_str, "\"", &_sum, &_used_num);
                break;
            case EXJSON_ARRAY:
            case EXJSON_OBJECT:
                inner_str = encode_json(EV_VALUE_P(temp));
                _result_str = _exjson_strcat_(_result_str, inner_str, &_sum, &_used_num);
                free(inner_str);
                break;
                
        }
        if ( i < num - 1 )
        {
            _result_str = _exjson_strcat_(_result_str, ",", &_sum, &_used_num);
        }
        temp = temp + 1;
    }
    
    
    switch( E_TYPE_P(exjson) )
    {
        case EX_OBJECT:
            _result_str = _exjson_strcat_(_result_str, "}", &_sum, &_used_num);
            break;
        case EX_ARRAY:
            _result_str = _exjson_strcat_(_result_str, "]", &_sum, &_used_num);
            break;
    }
    
    return _result_str;
}

void destroy_exjson(EXJSON *exjson)
{
    if ( !exjson ) return ;
    static int _num = 0;
    
    for ( int i = 0; i < E_NUM_P(exjson); ++i )
    {
        EXJSON_V *temp = E_DATA_P(exjson) + i;
        switch ( EV_TYPE_P(temp) )
        {
            case EXJSON_OBJECT:
            case EXJSON_ARRAY:
                free( EV_NAME_P(temp) );
                ++_num;
                destroy_exjson(EV_VALUE_P(temp));
                --_num;
                free( EV_VALUE_P(temp) );
                break;
            default:
                free( EV_NAME_P(temp) );
                free( EV_VALUE_P(temp) );
                break;
        }
        if ( i == E_NUM_P(exjson) - 1 )
        {
            free( E_DATA_P(exjson) );
        }
    }
    
    if ( _num == 0 ) free(exjson);
}
