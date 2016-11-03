#ifndef uu-lexeme
#define uu-lexeme

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct lexeme {
    char *type;

    char *sval;
    int ival;

    struct lexeme *left;
    struct lexeme *right;

    struct lexeme *array;

} Lexeme;

extern Lexeme *newLexeme(char *type);

extern Lexeme *cons(Lexeme *l, Lexeme *r);
extern Lexeme *car(Lexeme *x);
extern Lexeme *cdr(Lexeme *x);
extern void *setCar(Lexeme *x, Lexeme *l);
extern void *setCdr(Lexeme *x, Lexeme *l);
extern char *getType(Lexeme *x);
extern char *displayLexeme(Lexeme *x);

#endif
