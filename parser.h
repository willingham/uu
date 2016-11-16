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
extern Parser *program(Parser *p);
extern Parser *expressionList(Parser *p);
extern Parser *expression(Parser *p);
extern Parser *expr(Parser *p);
extern Parser *optParamList(Parser *p);
extern Parser *paramList(Parser *p);
extern Parser *primary(Parser *p);
extern Parser *operator(Parser *p);
extern Parser *literal(Parser *p);
extern Parser *funcDef(Parser *p);
extern Parser *lambda(Parser *p);
extern Parser *loop(Parser *p);
extern Parser *block(Parser *p);
extern Parser *whilee(Parser *p);
extern Parser *forr(Parser *p);
extern Parser *iff(Parser *p);
extern Parser *optElse(Parser *p);


#endif
