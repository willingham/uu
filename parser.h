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

extern int check(char *x);
extern void match(char *x);

// lhs grammar functions
extern void program(void);
extern void expressionList(void);
extern void expression(void);
extern void expr(void);
extern void optParamList(void);
extern void paramList(void);
extern void primary(void);
extern void operator(void);
extern void literal(void);
extern void funcDef(void);
extern void lambda(void);
extern void loop(void);
extern void block(void);
extern void whilee(void);
extern void forr(void);
extern void iff(void);
extern void optElse(void);


#endif
