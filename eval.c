#include <stdio.h>
#include "eval.h"
#include "lexeme.h"
#include "type.h"
#include "env.h"
#include "type.h"
#include "error.h"

Lexeme *eval(Lexeme *tree, Lexeme *env) {
    if (tree != NULL) {
        if (!strcmp(tree->type, STRING)) {
            return tree;
        } else if (!strcmp(tree->type, INT)) {
            return tree;
        } else if (!strcmp(tree->type, ARRAY)) {
            return tree;
        } else if (!strcmp(tree->type, CLOSURE)) {
            return tree;
        } else if (!strcmp(tree->type, NIL)) {
            return tree;
        } else if (!strcmp(tree->type, BREAK)) {
            return tree;
        } else if (!strcmp(tree->type, ID) || !strcmp(tree->type, FUNC)) {
            return lookupEnv(tree, env);
        } else if (!strcmp(tree->type, FUNCDEF)) {
            return evalFuncDef(tree, env);
        } else if (!strcmp(tree->type, FUNCCALL)) {
            return evalFuncCall(tree, env);
        } else if (!strcmp(tree->type, EXPRESSIONLIST)) {
            return evalExpressionList(tree, env);
        } else if (!strcmp(tree->type, EXPR)) {
            return evalExpr(tree, env);
        } else if (!strcmp(tree->type, LAMBDA)) {
            return evalLambda(tree, env);
        } else if (!strcmp(tree->type, WHILE)) {
            return evalWhile(tree, env);
        } else if (!strcmp(tree->type, IF)) {
            return evalIf(tree, env);
        } else if (!strcmp(tree->type, BLOCK)) {
            return evalBlock(tree, env);
        } else if (!strcmp(tree->type, OPTELSE)) {
            return evalOptElse(tree, env);
        } else if (!strcmp(tree->type, FOR)) {
            return evalFor(tree, env);
        } else if (!strcmp(tree->type, MINUS)) {
            return evalMinus(tree, env);
        } else if (!strcmp(tree->type, PLUS)) {
            return evalPlus(tree, env);
        } else if (!strcmp(tree->type, DIVIDE)) {
            return evalDivide(tree, env);
        } else if (!strcmp(tree->type, MULTIPLY)) {
            return evalMultiply(tree, env);
        } else if (!strcmp(tree->type, EXPONENT)) {
            return evalExponent(tree, env);
        } else if (!strcmp(tree->type, NOT)) {
            return evalSimpleOp(tree, env);
        } else if (!strcmp(tree->type, NE)) {
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
            return evalAssign(tree, env);
        } else if (!strcmp(tree->type, ARRAYACCESS)) {
            return evalArrayAccess(tree, env);
        } else {
            printf("Type: %s not evaluated.\n", tree->type);
        } 
    }
    return NULL;
}


Lexeme *evalFuncDef(Lexeme *t, Lexeme *env) {
    Lexeme *closure = newLexeme(CLOSURE);
    setCar(closure, env);
    setCdr(closure, t);
    return insert(getFuncDefName(t), closure, env);
}

Lexeme *evalFuncCall(Lexeme *t, Lexeme *env) {
    Lexeme *closure = eval(getFuncCallName(t), env);
    Lexeme *args = getFuncCallArgs(t);
    Lexeme *eargs = evalArgs(args, env);
    if (!strcmp(closure->type, BUILTIN)) {
        return closure->fp(eargs);
    }

    Lexeme *params = getClosureParams(closure);
    Lexeme *body = getClosureBody(closure);
    Lexeme *senv = getClosureEnvironment(closure);
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
        if (!strcmp(result->type, BLOCK)) {
            return result;
        }
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
        error("FATAL: Can only subtract ints.");
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

Lexeme *evalExponent(Lexeme *t, Lexeme *env) {
	//eval the left and the right hand sides
    Lexeme *left = eval(car(t),env);
    Lexeme *right = eval(cdr(t),env);
    if (left->type == INT && right->type == INT) {
        Lexeme *new = newLexeme(INT);
        int i, result = 1;
        for (i=0; i < right->ival; i++) {
            result *= left->ival;
        }
		new->ival = result;
		return new;
    } else {
        error("Can only multiply ints.");
        exit(1);
        return NULL;
    } 
}

Lexeme *evalAssign(Lexeme *t, Lexeme *env) {
    Lexeme *value = eval(cdr(t), env);
    if (!strcmp(t->left->type, ARRAYACCESS)) {
        Lexeme *temp = evalArrayAccess(t->left, env);
        temp->type = value->type;
        temp->sval = value->sval;
        temp->ival = value->ival;
        temp->fp = value->fp;
        temp->left = value->left;
        temp->right = value->right;
        temp->array = value->array;
    } else {
        insert(car(t), value, env);
    }
    return value;
}

Lexeme *evalWhile(Lexeme *t, Lexeme *env) {
    Lexeme *result = NULL;
    while (isTrue(eval(car(t), env))) {
        result = eval(cdr(t), env);
        if (!strcmp(result->type, BREAK)) {
            return newLexeme(NIL);
        }
    }
    return result;
}

Lexeme *evalIf(Lexeme *t, Lexeme *env) {
    Lexeme *result = NULL;
    if (isTrue(eval(t->left, env))) {
           result =  eval(t->right->left, env);
    } else {
        result = eval(t->right->right, env);
    }
    return result;
}

Lexeme *evalOptElse(Lexeme *t, Lexeme *env) {
    if (t == NULL) {
        return NULL;
    } else {
        return eval(t->left, env);
    }
}

Lexeme *evalFor(Lexeme *t, Lexeme *env) {
    Lexeme *result = NULL;
    eval(car(car(t)), env);
    while (isTrue(eval(cdr(car(t)), env))) {
        result = eval(t->right->right, env);
        eval(t->right->left, env);
    }
    return result;
}

Lexeme *evalExpressionList(Lexeme *t, Lexeme *env) {
    Lexeme *result = newLexeme(NIL);
    while (t != NULL) {
        result = eval(t->left, env);
        if (result != NULL && !strcmp(result->type, BREAK)) {
            return result;
        }
        t = t->right;
    }
    return result;
}

Lexeme *evalExpr(Lexeme *t, Lexeme *env) {
    if (t->right == NULL) {
        return eval(t->left, env);
    } else {
        return evalSimpleOp(cons(t->right->left->type, t->left, t->right->right), env); 
    }
}

Lexeme *evalLambda(Lexeme *t, Lexeme *env) {
    Lexeme *closure = newLexeme(CLOSURE);
    Lexeme *temp = newLexeme(FUNCDEF);
    temp->right = t;
    setCar(closure, env);
    setCdr(closure, temp);
    return closure;
}

Lexeme *evalSimpleOp(Lexeme *t, Lexeme *env) {
    t->right = eval(t->right, env);
    if (!strcmp(t->type, EQUALS)) {
        return evalAssign(t, env);
    }
    t->left = eval(t->left, env);
    Lexeme *result = newLexeme(INT);
    if (!strcmp(t->type, NOT)) {
    } else if (!strcmp(t->type, NE)) {
        if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, INT)) {
            if (t->left->ival == t->right->ival) {
                result->ival = 0;
            } else {
                result->ival = 1;
            }
        } else if ((!strcmp(t->left->type, STRING) || !strcmp(t->left->type, ID)) && (!strcmp(t->right->type, STRING) || !strcmp(t->left->type, ID))) {
            result->ival = !strcmp(t->left->sval, t->right->sval);
        } else if (!strcmp(t->left->type, NIL) && !strcmp(t->right->type, STRING)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, STRING) && !strcmp(t->right->type, NIL)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, NIL) && !strcmp(t->right->type, INT)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, NIL)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, STRING) && !strcmp(t->right->type, INT)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, STRING)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, NIL) && !strcmp(t->right->type, NIL)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, NIL) && strcmp(t->right->type, NIL)) {
            result->ival = 1;
        } else if (strcmp(t->left->type, NIL) && !strcmp(t->right->type, NIL)) {
            result->ival = 1;
        } else {
            printf("l->%s, r->%s\n", t->left->type, t->right->type);
            error("Invalid comparison.");
            exit(1);
            return NULL;
        }
        
    } else if (!strcmp(t->type, GT)) {
        if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, INT)) {
            if (t->left->ival > t->right->ival) {
                result->ival = 1;
            } else {
                result->ival = 0;
            }
        } else {
            error("Can only compare INTs.");
            printf("Types: %s %s\n", t->left->type, t->right->type);
            exit(1);
            return NULL;
        }
    } else if (!strcmp(t->type, LT)) {
        if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, INT)) {
            if (t->left->ival < t->right->ival) {
                result->ival = 1;
            } else {
                result->ival = 0;
            }
        } else {
            error("Can only compare INTs.");
            printf("Types: %s %s\n", t->left->type, t->right->type);
            exit(1);
            return NULL;
        }
    } else if (!strcmp(t->type, GTE)) {
        if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, INT)) {
            if (t->left->ival >= t->right->ival) {
                result->ival = 1;
            } else {
                result->ival = 0;
            }
        } else {
            error("Can only compare INTs.");
            printf("Types: %s %s\n", t->left->type, t->right->type);
            exit(1);
            return NULL;
        }
    } else if (!strcmp(t->type, LTE)) {
        if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, INT)) {
            if (t->left->ival <= t->right->ival) {
                result->ival = 1;
            } else {
                result->ival = 0;
            }
        } else {
            error("Can only compare INTs.");
            printf("Types: %s %s\n", t->left->type, t->right->type);
            exit(1);
            return NULL;
        }
    } else if (!strcmp(t->type, ISEQUAL)) {
        if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, INT)) {
            if (t->left->ival == t->right->ival) {
                result->ival = 1;
            } else {
                result->ival = 0;
            }
        } else if ((!strcmp(t->left->type, STRING) || !strcmp(t->left->type, ID)) && (!strcmp(t->right->type, STRING) || !strcmp(t->left->type, ID))) {
            result->ival = !strcmp(t->left->sval, t->right->sval);
        } else if (!strcmp(t->left->type, NIL) && !strcmp(t->right->type, STRING)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, STRING) && !strcmp(t->right->type, NIL)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, NIL) && !strcmp(t->right->type, INT)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, NIL)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, STRING) && !strcmp(t->right->type, INT)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, INT) && !strcmp(t->right->type, STRING)) {
            result->ival = 0;
        } else if (!strcmp(t->left->type, NIL) && !strcmp(t->right->type, NIL)) {
            result->ival = 1;
        } else if (!strcmp(t->left->type, NIL) && strcmp(t->right->type, NIL)) {
            result->ival = 0;
        } else if (strcmp(t->left->type, NIL) && !strcmp(t->right->type, NIL)) {
            result->ival = 0;
        } else {
            printf("l->%s, r->%s\n", t->left->type, t->right->type);
            printf("Invalid comparison.");
            exit(1);
            return NULL;
        }
    } else if (!strcmp(t->type, AND)) {
        if (isTrue(t->left) && isTrue(t->right)) {
            result->ival = 1;
        } else {
            result->ival = 0;
        }
    } else if (!strcmp(t->type, OR)) {
        if (isTrue(t->left) || isTrue(t->right)) {
            result->ival = 1;
        } else {
            result->ival = 0;
        }
    } else if (!strcmp(t->type, PLUS)) {
        return evalPlus(t, env);
    } else if (!strcmp(t->type, MINUS)) {
        return evalMinus(t, env);
    } else if (!strcmp(t->type, DIVIDE)) {
        return evalDivide(t, env);
    } else if (!strcmp(t->type, MULTIPLY)) {
        return evalMultiply(t, env);
    } else if (!strcmp(t->type, EXPONENT)) {
        return evalExponent(t, env);
    } else {
        return NULL;
    }
    return result;
}

Lexeme *evalArrayAccess(Lexeme *t, Lexeme *env) {
    Lexeme *temp = lookupEnv(t->left, env);
    if (strcmp(temp->type, ARRAY)) {
        error("Invalid array.\n");
        exit(1);
    } 
    Lexeme *index = eval(t->right, env);
    if (strcmp(index->type, INT)) {
        error("Must access array with INT.\n");
        exit(1);
    }
    return temp->array[index->ival];
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
    return t->right->right->left->left;
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
