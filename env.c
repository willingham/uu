#include <stdio.h>
#include "env.h"
#include "lexeme.h"
#include "type.h"

Lexeme *create() {
    return extendEnv(NULL, NULL, NULL);
}

Lexeme *extendEnv(Lexeme *env, Lexeme *vars, Lexeme *vals) {
    return cons(ENV, makeTable(vars, vals), env);
}

Lexeme *makeTable(Lexeme *vars, Lexeme *vals) {
    return cons(TABLE, vars, vals);
}

Lexeme *lookupEnv(Lexeme *env, Lexeme *var) {
    while (env != NULL) {
        Lexeme *table = car(env);
        Lexeme *vars = car(table);
        Lexeme *vals = cdr(table);
        while (vars != NULL) {
            if (sameVariable(var, car(vars))) {
                return car(vals);
            }
            //walk the lists in parallel
            vars = cdr(vars);
            vals = cdr(vals);
        }
        env = cdr(env);
    }
    fprintf(stderr, "FATAL: variable, %s, is undefined.", var->sval);
    return NULL;
}

int sameVariable(Lexeme *x, Lexeme *y) {
    return !strcmp(x->sval, y->sval);
}

Lexeme *insert(Lexeme *var, Lexeme *val, Lexeme *env) {
    Lexeme *table = car(env);
    setCar(table, cons(GLUE, var, car(table)));
    setCdr(table, cons(GLUE, val, cdr(table)));
    return val;
}
