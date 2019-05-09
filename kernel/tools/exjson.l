%{
    #include <stdio.h>
    #include <string.h>
    #include "exjson.tab.h"
%}

%option noyywrap case-insensitive

%s COMMENT

%%
"{"                                 { return yytext[0]; }
"}"                                 { return yytext[0]; }
"["                                 { return yytext[0]; }
"]"                                 { return yytext[0]; }
":"                                 { return yytext[0]; }
","                                 { return yytext[0]; }
"#"                                 { BEGIN COMMENT;    }
"//"                                { BEGIN COMMENT;    }
<COMMENT>.                          { }
<COMMENT>\n                         { BEGIN INITIAL;    }
[1-9][0-9]*                         { yylval.val.val_type = 2; yylval.val.ival = atol(yytext); return T_INT;     }
([1-9][0-9]*|[0-9])?\.([0-9]*)?     { yylval.val.val_type = 3; yylval.val.dval = atof(yytext); return T_DOUBLE;  }
\"[^\"]*\"                          { yylval.val.val_type = 4; yylval.val.ptr = strndup(yytext + 1, strlen(yytext+1) - 1); return T_STR;     }
(\n|\t|[ ])+                        {  }
.                                   { printf("Unkown token: %s", yytext);exit(0); }
%%

