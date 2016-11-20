#include <stdio.h>
#include "env.h"
#include "lexeme.h"

Lexeme *create() {
    return extendEnv(NULL, NULL, NULL);
}

Lexeme *extendEnv(Lexeme *env, Lexeme *vars, Lexeme *vals) {
    return cons(env
