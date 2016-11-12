#ifndef uuParser
#define uuParser

#include <stdio.h>
#include "type.h"
#include "lexeme.h"

typedef struct parser {
    FILE *fIn;
    FILE *fOut;

    int line;
    Lexeme *last;
    Lexeme *pending;
} Parser;

extern Lexeme *parse(FILE *fIn);

extern int check(Parser *p, char *x);
extern void match(Parser *p, char *x);

// lhs grammar functions
extern void program(Parser *p);
extern void expressionList(Parser *p);
extern void expression(Parser *p);
extern void expr(Parser *p);
extern void optParamList(Parser *p);
extern void paramList(Parser *p);
extern void primary(Parser *p);
extern void operator(Parser *p);
extern void literal(Parser *p);
extern void funcDef(Parser *p);
extern void lambda(Parser *p);
extern void loop(Parser *p);
extern void block(Parser *p);
extern void whilee(Parser *p);
extern void forr(Parser *p);
extern void iff(Parser *p);
extern void optElse(Parser *p);


#endif
