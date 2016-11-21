#ifndef uuEval
#define uuEval

#include <stdio.h>
#include "lexeme.h"
#include "env.h"

extern Lexeme *eval(Lexeme *tree, Lexeme *env);
extern Lexeme *evalFuncDef(Lexeme *t, Lexeme *env);
extern Lexeme *evalExpressionList(Lexeme *t, Lexeme *env);
extern Lexeme *evalExpr(Lexeme *t, Lexeme *env);
extern Lexeme *evalParamList(Lexeme *t, Lexeme *env);
extern Lexeme *evalPrimary(Lexeme *t, Lexeme *env);
extern Lexeme *evalLambda(Lexeme *t, Lexeme *env);
extern Lexeme *evalWhile(Lexeme *t, Lexeme *env);
extern Lexeme *evalIf(Lexeme *t, Lexeme *env);
extern Lexeme *evalBlock(Lexeme *t, Lexeme *env);
extern Lexeme *evalOptParamList(Lexeme *t, Lexeme *env);
extern Lexeme *evalOptElse(Lexeme *t, Lexeme *env);
extern Lexeme *evalFor(Lexeme *t, Lexeme *env);
extern Lexeme *evalSimpleOp(Lexeme *t, Lexeme *env);



#endif
