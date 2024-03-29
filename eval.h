#ifndef uuEval
#define uuEval

#include <stdio.h>
#include "lexeme.h"
#include "env.h"

extern Lexeme *eval(Lexeme *tree, Lexeme *env);
extern Lexeme *evalFuncDef(Lexeme *t, Lexeme *env);
extern Lexeme *evalFuncCall(Lexeme *t, Lexeme *env);
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
extern Lexeme *evalArgs(Lexeme *t, Lexeme *env);
extern Lexeme *evalPlus(Lexeme *t, Lexeme *env);
extern Lexeme *evalMinus(Lexeme *t, Lexeme *env);
extern Lexeme *evalDivide(Lexeme *t, Lexeme *env);
extern Lexeme *evalMultiply(Lexeme *t, Lexeme *env);
extern Lexeme *evalExponent(Lexeme *t, Lexeme *env);
extern Lexeme *evalAssign(Lexeme *t, Lexeme *env);
extern Lexeme *evalArrayAccess(Lexeme *t, Lexeme *env);
extern Lexeme *evalDot(Lexeme *t, Lexeme *env);

// helpers
extern Lexeme *getFuncDefName(Lexeme *t);
extern Lexeme *getFuncCallName(Lexeme *t);
extern Lexeme *getFuncCallArgs(Lexeme *t);
extern Lexeme *getClosureParams(Lexeme *t);
extern Lexeme *getClosureBody(Lexeme *t);
extern Lexeme *getClosureEnvironment(Lexeme *t);
extern int isTrue(Lexeme *t);


#endif
