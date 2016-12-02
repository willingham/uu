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
    Lexeme *tree;
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
extern int idListPending(Parser *p);
extern int variablePending(Parser *p);

// lhs grammar functions
extern Lexeme *program(Parser *p);
extern Lexeme *expressionList(Parser *p);
extern Lexeme *expression(Parser *p);
extern Lexeme *expr(Parser *p);
extern Lexeme *optParamList(Parser *p);
extern Lexeme *paramList(Parser *p);
extern Lexeme *primary(Parser *p);
extern Lexeme *operator(Parser *p);
extern Lexeme *literal(Parser *p);
extern Lexeme *funcDef(Parser *p);
extern Lexeme *lambda(Parser *p);
extern Lexeme *loop(Parser *p);
extern Lexeme *block(Parser *p);
extern Lexeme *whilee(Parser *p);
extern Lexeme *forr(Parser *p);
extern Lexeme *iff(Parser *p);
extern Lexeme *optElse(Parser *p);
extern Lexeme *idList(Parser *p);
extern Lexeme *optIdList(Parser *p);

extern void pretty(Lexeme *l);
extern void prettyPrinter(Lexeme *l, char *s);

#endif
