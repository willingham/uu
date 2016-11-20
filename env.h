#ifndef uuEnv
#define uuEnv
#include <stdio.h>
#include "lexeme.h"

extern Lexeme *createEnv();
extern Lexeme *extendEnv(Lexeme *env, Lexeme *vars, Lexeme *vals);
extern Lexeme *makeTable(Lexeme *vars, Lexeme *vals);
extern Lexeme *lookupEnv(env, variable);
extern int sameVariable(Lexeme *var, Lexeme *var);
extern Lexeme *insert(Lexeme *var, Lexeme *val, Lexeme *env);


#endif
