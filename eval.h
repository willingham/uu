#ifndef uuEval
#define uuEval

#include <stdio.h>
#include "lexeme.h"
#include "env.h"

extern Lexeme *eval(Lexeme *tree, Lexeme *env);
extern Lexeme *evalFuncDef(Lexeme *t, Lexeme *env);


#endif
