%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "stack.h"
    #include "exjson.h"
    extern int yylex();
    extern int yylineno;
    extern char *yytext;
    int _status = 1;
    extern int yylex_destroy();
    typedef struct yy_buffer_state * YY_BUFFER_STATE;
    extern int yyparse();
    extern YY_BUFFER_STATE yy_scan_string(char * str);
    extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
    extern void yyerror(char *);
    /* (INT:    2) (DOUBLE: 3) (STR:    4)
     * (ARRAY:  5) (OBJECT: 6) (true    7)
     * (false:  8) (null:   9) */
     E_STACK   *exjson_stack;
     EXJSON    *exjson;
     E_STACK_V *temp_exjson_stack;
%}

%union {
    struct {
        long ival;
        double dval;
        void *ptr;
        unsigned char val_type;
    } val;
}

%token<val> T_INT T_STR T_DOUBLE
%type<val>  object array object_key_pair array_data value

%%
json
    : object
    | array
;

object
    : '{' object_key_pair '}'
    {

    }
;

array
    : '[' array_data ']'
    {

    }
;

object_key_pair
    :  T_STR ':' value
    {
        switch ($3.val_type)
        {
            case SV_INT:
                exjson = INIT_EXJSON();
                push(exjson_stack, exjson, 0);
                add_object_int(exjson, $1.ptr, $3.ival);
                break;
            case SV_DOUBLE:
                exjson = INIT_EXJSON();
                push(exjson_stack, exjson, 0);
                add_object_double(exjson, $1.ptr, $3.dval);
                break;
            case SV_STRING:
                exjson = INIT_EXJSON();
                push(exjson_stack, exjson, 0);
                add_object_string(exjson, $1.ptr, $3.ptr);
                free($3.ptr);
                break;
            case SV_ARRAY:
                temp_exjson_stack = pop(exjson_stack);
                if ( SV_NEXT_P(temp_exjson_stack) )
                {
                    exjson = SV_DATA_P(SV_NEXT_P(temp_exjson_stack));
                }
                else
                {
                    exjson = INIT_EXJSON();
                    push(exjson_stack, exjson, 0);
                }
                add_object_array(exjson, $1.ptr, SV_DATA_P(temp_exjson_stack));
                break;
            case SV_OBJECT:
                temp_exjson_stack = pop(exjson_stack);
                exjson = INIT_EXJSON();
                push(exjson_stack, exjson, 0);
                add_object_object(exjson, $1.ptr, SV_DATA_P(temp_exjson_stack));
                break;
        }
        free($1.ptr);
    }
    |  object_key_pair ',' T_STR ':' value
    {
        switch ($5.val_type)
        {
            case SV_INT:
                add_object_int(exjson, $3.ptr, $5.ival);
                break;
            case SV_DOUBLE:
                add_object_double(exjson, $3.ptr, $5.dval);
                break;
            case SV_STRING:
                add_object_string(exjson, $3.ptr, $5.ptr);
                free($5.ptr);
                break;
            case SV_ARRAY:
        	temp_exjson_stack = pop(exjson_stack);
                add_object_array(SV_DATA_P(SV_NEXT_P(temp_exjson_stack)), $3.ptr, SV_DATA_P(temp_exjson_stack));
                exjson = SV_DATA_P(SV_NEXT_P(temp_exjson_stack));
                break;
            case SV_OBJECT:
                temp_exjson_stack = pop(exjson_stack);
                add_object_object(SV_DATA_P(SV_NEXT_P(temp_exjson_stack)), $3.ptr, SV_DATA_P(temp_exjson_stack));
                exjson = SV_DATA_P(SV_NEXT_P(temp_exjson_stack));
                break;
        }
        free($3.ptr);
    }
;

array_data
    : value 
    {
        switch ($1.val_type)
        {
            case SV_INT:
                exjson = INIT_EXJSON();
                push(exjson_stack, exjson, 0);
                add_array_int(exjson, $1.ival);
                break;
            case SV_DOUBLE:
                exjson = INIT_EXJSON();
                push(exjson_stack, exjson, 0);
                add_array_double(exjson, $1.dval);
                break;
            case SV_STRING:
                exjson = INIT_EXJSON();
                push(exjson_stack, exjson, 0);
                add_array_string(exjson, $1.ptr);
                free($1.ptr);
                break;
            case SV_ARRAY:
                /* array */
                temp_exjson_stack = pop(exjson_stack);
                exjson = INIT_EXJSON();
                push(exjson_stack, exjson, 0);
                add_array_array(exjson, SV_DATA_P(temp_exjson_stack));
                break;
            case SV_OBJECT:
                /* object */
                temp_exjson_stack = pop(exjson_stack);
                exjson = INIT_EXJSON();
                push(exjson_stack, exjson, 0);
                add_array_object(exjson, SV_DATA_P(temp_exjson_stack));
                break;
        }
    }
    | array_data ',' value
    {
        switch ($3.val_type)
        {
            case SV_INT:
                add_array_int(exjson, $3.ival);
                break;
            case SV_DOUBLE:
                add_array_double(exjson, $3.dval);
                break;
            case SV_STRING:
                add_array_string(exjson, $3.ptr);
                free($3.ptr);
                break;
            case SV_ARRAY:
                temp_exjson_stack = pop(exjson_stack);
                add_array_array(SV_DATA_P(SV_NEXT_P(temp_exjson_stack)), SV_DATA_P(temp_exjson_stack));
                exjson = SV_DATA_P(SV_NEXT_P(temp_exjson_stack));
                break;
            case SV_OBJECT:
                temp_exjson_stack = pop(exjson_stack);
                add_array_object(SV_DATA_P(SV_NEXT_P(temp_exjson_stack)), SV_DATA_P(temp_exjson_stack));
                exjson = SV_DATA_P(SV_NEXT_P(temp_exjson_stack));
                break;
        }
    }
 ;

value
    : T_STR
    {
        $$ = $1;
    }
    | T_INT
    {
        $$ = $1;
    }
    | T_DOUBLE
    {
        $$ = $1;
    }
    | array
    {
       $$.val_type = SV_ARRAY;
    }
    | object
    {
        $$.val_type = SV_OBJECT;
    }
;
%%

/* Remember that the return value need be freed by destroy_exjson() function
 * Other than memory leak may be occcured.
 */
EXJSON *decode_json(char *json_string)
{
    exjson_stack = INIT_STACK();
    YY_BUFFER_STATE buffer = yy_scan_string(json_string);
    yyparse();
    yy_delete_buffer(buffer);
    destroy_stack2(exjson_stack);
    yylex_destroy();
    if ( !_status ) { destroy_exjson(exjson); return NULL; }
    return exjson;
}

void yyerror(char *msg)
{
    _status = 0;
    fprintf(stderr, "\n%d: %s at '%s'\n", yylineno, msg, yytext);
}