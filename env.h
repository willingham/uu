#ifndef uuEnv
#define uuEnv
#include <stdio.h>
#include "lexeme.h"

extern Lexeme *createEnv();
extern Lexeme *extendEnv(Lexeme *env, Lexeme *vars, Lexeme *vals);
extern Lexeme *makeTable(Lexeme *vars, Lexeme *vals);



#endif
