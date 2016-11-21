#ifndef uuEval
#define uuEval

#include <stdio.h>
#include "lexeme.h"
#include "env.h"

extern void eval(Lexeme *tree, Lexeme *env);
extern void evalFuncDef(Lexeme *t, Lexeme *env);


#endif
