#ifndef uuEnv
#define uuEnv
#include <stdio.h>
#include "lexeme.h"

extern Lexeme *createEnv();
extern Lexeme *extendEnv(Lexeme *env, Lexeme *vars, Lexeme *vals);
extern Lexeme *makeTable(Lexeme *vars, Lexeme *vals);
extern Lexeme *lookupEnv(Lexeme *env, Lexeme *variable);
extern int sameVariable(Lexeme *x, Lexeme *y);
extern Lexeme *insert(Lexeme *var, Lexeme *val, Lexeme *env);


#endif
