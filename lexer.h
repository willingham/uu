#ifndef uu-lexer
#define uu-lexer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct lexeme {
    char *type;
    char *sval;
    int ival;
    double dval;

    struct lexeme *left;
    struct lexeme *right;

} Lexeme;


#endif
