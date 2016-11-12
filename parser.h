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
extern Lexeme * match(Parser *p, char *x);
extern Lexeme *advance(Parser *p);

// pending functions
extern int programPending(Parser *p);
extern int expressionListPending(Parser *p);
extern int expressionPending(Parser *p);
extern int exprPending(Parser *p);
extern int optParamListPending(Parser *p);
extern int paramListPending(Parser *p);
extern int primaryPending(Parser *p);
extern int operatorPending(Parser *p);
extern int literalPending(Parser *p);
extern int funcDefPending(Parser *p);
extern int lambdaPending(Parser *p);
extern int loopPending(Parser *p);
extern int blockPending(Parser *p);
extern int whileePending(Parser *p);
extern int forrPending(Parser *p);
extern int iffPending(Parser *p);
extern int optElsePending(Parser *p);

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
