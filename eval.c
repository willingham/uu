#include <stdio.h>
#include "eval.h"
#include "lexeme.h"
#include "type.h"
#include "env.h"

/*
void evals(Lexeme *tree, Lexeme *env) {
    char *type = tree->type;
    if (!strcmp(type, INT)) {
    } else if (!strcmp(type, STRING )) {
    } else if (!strcmp(type, VARIABLE)) {
    } else if (!strcmp(type, PLUS)) {
    } else if (!strcmp(type, MINUS)) {
    } else if (!strcmp(type, TIMES)) {
    } else if (!strcmp(type, DIVIDE)) {
    } else if (!strcmp(type, GT)) {
    } else if (!strcmp(type, LT)) {
    } else if (!strcmp(type, GTE)) {
    } else if (!strcmp(type, LTE)) {
    }
} */

Lexeme *eval(Lexeme *tree, Lexeme *env) {
    if (tree != NULL) {
        if (!strcmp(tree->type, STRING)) {
            return tree;
        } else if (!strcmp(tree->type, INT)) {
            return tree;
        } else if (!strcmp(tree->type, ID) || !strcmp(tree->type, FUNC)) {
            return lookupEnv(tree, env);
        } else if (!strcmp(tree->type, FUNCDEF)) {
            return evalFuncDef(tree, env);
        } else if (!strcmp(tree->type, EXPRESSIONLIST)) {
            return evalExpressionList(tree, env);
        } else if (!strcmp(tree->type, EXPR)) {
            return evalExpr(tree, env);
        } else if (!strcmp(tree->type, PARAMLIST)) {
            return evalParamList(tree, env);
        } else if (!strcmp(tree->type, PRIMARY)) {
            return evalPrimary(tree, env);
        } else if (!strcmp(tree->type, LAMBDA)) {
            return evalLambda(tree, env);
        } else if (!strcmp(tree->type, WHILE)) {
            return evalWhile(tree, env);
        } else if (!strcmp(tree->type, IF)) {
            return evalIf(tree, env);
        } else if (!strcmp(tree->type, BLOCK)) {
            return evalBlock(tree, env);
        } else if (!strcmp(tree->type, OPTPARAMLIST)) {
            return evalOptParamList(tree, env);
        } else if (!strcmp(tree->type, OPTELSE)) {
            return evalOptElse(tree, env);
        } else if (!strcmp(tree->type, FOR)) {
            return evalFor(tree, env);
        } else if (!strcmp(tree->type, MINUS)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, PLUS)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, DIVIDE)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, MULTIPLY)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, NOT)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, GT)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, LT)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, GTE)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, LTE)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, ISEQUAL)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, AND)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, OR)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, EQUALS)) {
            return evalSimpleOp(tree, env);
        } 
    }
    return NULL;
}
