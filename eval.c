#include <stdio.h>
#include "eval.h"
#include "lexeme.h"
#include "type.h"
#include "env.h"

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


Lexeme *evalFuncDef(Lexeme *t, Lexeme *env) {
    Lexeme *closure = newLexeme(CLOSURE);
    setCar(closure, env);
    setCdr(closure, t);
    return insert(closure, getFuncDefName(t), env);
}

Lexeme *evalFuncCall(Lexeme *t, Lexeme *env) {
    Lexeme *closure = eval(getFuncCallName(t), env);
    Lexeme *args = getFuncCallArgs(t);
    Lexeme *params = getClosureParams(closure);
    Lexeme *body = getClosureBody(closure);
    Lexeme *senv = getClosureEnvironment(closure);
    Lexeme *eargs = evalArgs(args, env);
    Lexeme *xenv = extendEnv(senv, params, eargs);
    return eval(body, xenv);
}

Lexeme *evalArgs(Lexeme *t, Lexeme *env) {
    if (t == NULL) {
        return NULL;
    }
    return cons(GLUE, eval(car(t), env), evalArgs(cdr(t), env));
}

Lexeme *evalBlock(Lexeme *t, Lexeme *env) {
    Lexeme *result;
    while (t != NULL) {
        result = eval(car(t), env);
        t = cdr(t);
    }
    return result;
}

Lexeme *evalPlus(Lexeme *t, Lexeme *env) {
	//eval the left and the right hand sides
    Lexeme *left = eval(car(t),env);
    Lexeme *right = eval(cdr(t),env);
    if (left->type == INT && right->type == INT) {
        Lexeme *new = newLexeme(INT);
		new->ival = left->ival + right->ival;
		return new;
    } else if (left->type == INT && right->type == STRING) {
        Lexeme *new = newLexeme(STRING);
		sprintf(new->sval, "%d%s", left->ival, right->sval);
		return new;
    } else if (left->type == STRING && right->type == INT) {
        Lexeme *new = newLexeme(STRING);
		sprintf(new->sval, "%s%d", left->sval, right->ival);
		return new;
    } else if (left->type == STRING && right->type == STRING) {
        Lexeme *new = newLexeme(STRING);
		sprintf(new->sval, "%s%s", left->sval, right->sval);
		return new;
    } else {
        error("Can only add ints or strings.");
        exit(1);
        return NULL;
    } 
}

Lexeme *evalMinus(Lexeme *t, Lexeme *env) {
	//eval the left and the right hand sides
    Lexeme *left = eval(car(t),env);
    Lexeme *right = eval(cdr(t),env);
    if (left->type == INT && right->type == INT) {
        Lexeme *new = newLexeme(INT);
		new->ival = left->ival - right->ival;
		return new;
    } else {
        error("Can only subtract ints.");
        exit(1);
        return NULL;
    } 
}

Lexeme *evalDivide(Lexeme *t, Lexeme *env) {
	//eval the left and the right hand sides
    Lexeme *left = eval(car(t),env);
    Lexeme *right = eval(cdr(t),env);
    if (left->type == INT && right->type == INT) {
        Lexeme *new = newLexeme(INT);
		new->ival = left->ival / right->ival;
		return new;
    } else {
        error("Can only divide ints.");
        exit(1);
        return NULL;
    } 
}

Lexeme *evalMultiply(Lexeme *t, Lexeme *env) {
	//eval the left and the right hand sides
    Lexeme *left = eval(car(t),env);
    Lexeme *right = eval(cdr(t),env);
    if (left->type == INT && right->type == INT) {
        Lexeme *new = newLexeme(INT);
		new->ival = left->ival * right->ival;
		return new;
    } else {
        error("Can only multiply ints.");
        exit(1);
        return NULL;
    } 
}

Lexeme *evalAssign(Lexeme *t, Lexeme *env) {
    Lexeme *value = eval(cdr(t), env);
    insert(car(t), value, env);
    return value;
}

Lexeme *evalWhile(Lexeme *t, Lexeme *env) {
    Lexeme *result = NULL;
    while (isTrue(eval(car(t), env))) {
        result = eval(cdr(t), env);
    }
    return result;
}

// helpers
Lexeme *getFuncDefName(Lexeme *f) {
    return car(f);
}

Lexeme *getFuncCallName(Lexeme *t) {
    return car(t);
}

Lexeme *getFuncCallArgs(Lexeme *t) {
    // right is OPTPARAMLIST, then left is PARAMLIST
    return car(cdr(t));
}

Lexeme *getClosureParams(Lexeme *t) {
    return car(cdr(cdr(t)));
}

Lexeme *getClosureBody(Lexeme *t) {
    return cdr(cdr(cdr(t)));
}

Lexeme *getClosureEnvironment(Lexeme *t) {
    return car(t);
}

int isTrue(Lexeme *t) {
    if (t == NULL) {
        return 0;
    } else if (!strcmp(t->type, BAD)) {
        return 0;
    } else if (!strcmp(t->type, INT) && t->ival == 0) {
        return 0;
    } else {
        return 1;
    }
}
