#include "error.h"
#include "parser.h"
#include "lexeme.h"
#include "lexer.h"
#include "type.h"

Lexeme *parse(FILE *xfile) {
    Parser *p = malloc(sizeof(Parser));

    p->fIn = xfile;
    p->line = 1;
    p->pending = lex(p);
    /*
    while(strcmp(p->pending->type, ENDOFFILE) != 0) {
        printf("%s\n", displayLexeme(p->pending));
        p->pending = lex(p);
    } */
    Lexeme *l = program(p);
    prettyPrinter(l, "");
    return p->pending;
}

// 

int check(Parser *p, char *x) {
    #ifdef uuDebug
    printf("Line: %d, PendingType: %s, TypeCheckedFor: %s\n", p->line, p->pending->type, x);
    #endif
    return strcmp(p->pending->type, x) == 0;
}

Lexeme *match(Parser *p, char *x) {
    if (check(p, x)) {
        return advance(p);
    } else {
        error("match error");
        printf("Line: %d, PendingType: %s, TypeCheckedFor: %s\n", p->line, p->pending->type, x);
        exit(1);
    }
}

Lexeme *advance(Parser *p) {
    p->last = p->pending;
    p->pending = lex(p);
    return p->last;
}

// pending functions
int expressionListPending(Parser *p) {
   return expressionPending(p);
} 

int expressionPending(Parser *p) {
    return exprPending(p) || loopPending(p) || iffPending(p) || funcDefPending(p);
}

int exprPending(Parser *p) {
    return primaryPending(p);
}

int optParamListPending(Parser *p) {
    return paramListPending(p) || 1;  // ?? do I even need this?
}

int paramListPending(Parser *p) {
    return exprPending(p);
}

int primaryPending(Parser *p) {
    return literalPending(p) || check(p, OP) || \
           lambdaPending(p) || check(p, ID) || operatorPending(p);
}

int operatorPending(Parser *p) {
    return check(p, MINUS) || check(p, PLUS) || check(p, DIVIDE) || check(p, MULTIPLY) || \
           check(p, NOT) || check(p, GT) || check(p, LT) || check(p, GTE) || check(p, LTE) || \
           check(p, ISEQUAL) || check(p, AND) || check(p, OR) || check(p, EQUALS);
}

int literalPending(Parser *p) {
    return check(p, INT) || check(p, STRING);
}

int funcDefPending(Parser *p) {
    return check(p, FUNC);
}

int lambdaPending(Parser *p) {
    return check(p, LAMBDA);
}

int loopPending(Parser *p) {
    return whileePending(p) || forrPending(p); 
}

int blockPending(Parser *p) {
    return check(p, OCB);
}

int whileePending(Parser *p) {
    return check(p, WHILE);
}

int forrPending(Parser *p) {
    return check(p, FOR);
}

int iffPending(Parser *p) {
    return check(p, IF);
}

int optElsePending(Parser *p) {
    return check(p, ELSE) || 1; // ?? Do I need this?
}


// lhs grammar functions
Lexeme *program(Parser *p) {
    Lexeme *x =  expressionList(p);
    check(p, ENDOFFILE);
    return x;
}

Lexeme *expressionList(Parser *p) {
    Lexeme *x, *y = NULL;
    x = expression(p);
    if (expressionListPending(p)) {
        y = expressionList(p);
    }
    return cons(EXPRESSIONLIST, x, y);
}

Lexeme *expression(Parser *p) {
    if (loopPending(p)) {
        return loop(p);
    } else if (iffPending(p)) {
        return iff(p);
    } else if (funcDefPending(p)) {
        return funcDef(p);
    } else if(exprPending(p)) {
        Lexeme *x = expr(p);
        match(p, SEMI);
        return x;
    } else {
        error("Expression not found.");
        exit(1);
    }
    return NULL;
}

Lexeme *expr(Parser *p) {
    Lexeme *x = NULL, *y = NULL, *z = NULL;
    x = primary(p);
    if(operatorPending(p)) {
        y = operator(p);
        z = expr(p);
    }
    return cons(EXPR, x, cons(GLUE, y, z));
}

Lexeme *optParamList(Parser *p) {
    Lexeme *x = NULL;
    if(paramListPending(p)) {
        x = paramList(p);
    }
    return x;
}
Lexeme *paramList(Parser *p) {
    Lexeme *x, *y = NULL;
    x = expr(p);
    if(exprPending(p)) {
        match(p, COMMA);
        y = paramList(p);
    }
    return cons(PARAMLIST, x, y);
}

Lexeme *primary(Parser *p) {
    Lexeme *x, *y = NULL;
    if(literalPending(p)) {
        return literal(p);
    } else if(check(p, OP)) {
        match(p, OP);
        x = expr(p);
        match(p, CP);
        return x;
    } else if(lambdaPending(p)) {
        return lambda(p);
    } else if(check(p, ID)) {
        x = match(p, ID);
        if(check(p, OSB)) {
            match(p, OSB);
            y = literal(p);
            match(p, CSB);
        } else if(check(p, OP)) {
            match(p, OP);
            y = optParamList(p);
            match(p, CP);
        }
        return cons(PRIMARY, x, y);
    } else if(operatorPending(p)) {
        x = operator(p);
        y = primary(p);
        return cons(PRIMARY, x, y);
    } else {
        error("Primary not found.");
        exit(1);
    }
    return NULL;
}

Lexeme *operator(Parser *p) {
    if (check(p, MINUS)) {
        return match(p, MINUS);
    } else if (check(p, PLUS)) {
        return match(p, PLUS);
    } else if (check(p, DIVIDE)) {
        return match(p, DIVIDE);
    } else if (check(p, MULTIPLY)) {
        return match(p, MULTIPLY);
    } else if (check(p, NOT)) {
        return match(p, NOT);
    } else if (check(p, GT)) {
        return match(p, GT);
    } else if (check(p, LT)) {
        return match(p, LT);
    } else if (check(p, GTE)) {
        return match(p, GTE);
    } else if (check(p, LTE)) {
        return match(p, LTE);
    } else if (check(p, ISEQUAL)) {
        return match(p, AND);
    } else if (check(p, OR)) {
        return match(p, OR);
    } else if (check(p, EQUALS)) {
        return match(p, EQUALS);
    } else {
        error("Operator not found.");
        exit(1);
    }
    return NULL;
}

Lexeme *literal(Parser *p) {
    if (check(p, INT)) {
        return match(p, INT);
    } else if (check(p, STRING)) {
        return match(p, STRING);
    }
    return NULL;
}

Lexeme *funcDef(Parser *p) {
    Lexeme *x, *y, *z = NULL;
    match(p, FUNC);
    x = match(p, ID);
    match(p, OP);
    y = optParamList(p);
    match(p, CP);
    z = block(p);
    return cons(FUNCDEF, x, cons(GLUE, y, z));
}

Lexeme *lambda(Parser *p) {
    Lexeme *x, *y = NULL;
    match(p, LAMBDA);
    match(p, OP);
    x = optParamList(p);
    match(p, CP);
    y = block(p);
    return cons(LAMBDA, x, y);
}

Lexeme *loop(Parser *p) {
    if (whileePending(p)) {
        return whilee(p);
    } else if (forrPending(p)) {
        return forr(p);
    } else {
        error("Loop not found.");
        exit(1);
    }
    return NULL;
}

Lexeme *block(Parser *p) {
    match(p, OCB);
    return expressionList(p);
    match(p, CCB);
}

Lexeme *whilee(Parser *p) {
    Lexeme *x, *y = NULL;
    match(p, WHILE);
    match(p, OP);
    x = expr(p);
    match(p, CP);
    y = block(p);
    return cons(WHILE, x, y);
}

Lexeme *forr(Parser *p) {
    Lexeme *x, *y, *z, *a = NULL;
    match(p, FOR);
    match(p, OP);
    x = match(p, ID);
    match(p, SEMI);
    y = expr(p);
    match(p, SEMI);
    z = expr(p);
    match(p, CP);
    a = block(p);
    return cons(FOR, cons(GLUE, x, y), cons(GLUE, z, a));
}

Lexeme *iff(Parser *p) {
    Lexeme *x, *y, *z = NULL;
    match(p, IF);
    match(p, OP);
    x = expr(p);
    match(p, CP);
    y = block(p);
    z = optElse(p);
    return cons(IF, x, cons(GLUE, y, z));
}

Lexeme *optElse(Parser *p) {
    if (check(p, ELSE)) {
        match(p, ELSE);
        if (blockPending(p)) {
            return block(p);
        } else if (iffPending(p)) {
            return iff(p);
        } else {
            error("optElse malformed.");
            exit(1);
        }
    }
    return NULL;
}
/*
void prettyPrinter(Lexeme *l, char *s) {
    if (l != NULL) {
        char *temp = malloc(sizeof(char) * 128);
        strcat(temp, s);
        strcat(temp, "");
        prettyPrinter(l->left, temp);
        printf("%s\n", displayLexeme(l));
        prettyPrinter(l->right, temp);
    }
}*/

void prettyPrinter(Lexeme *l, char *s) {
    if (l != NULL) {
        if (!strcmp(l->type, STRING)) {
            printf("\"%s\"", l->sval);
        } else if (!strcmp(l->type, INT)) {
            printf("%d", l->ival);
        } else if (!strcmp(l->type, ID) || !strcmp(l->type, FUNC)) {
            printf("%s", l->sval);
        } else if (!strcmp(l->type, FUNCDEF)) {
            printf("func ");
            prettyPrinter(l->left, "");
            printf("(");
            prettyPrinter(l->right->left, "");
            printf(") { \n");
            prettyPrinter(l->right->right, "");
            printf("}\n");
        } else if (!strcmp(l->type, EXPRESSIONLIST)) {
            prettyPrinter(l->left, "");
            printf(";\n");
        } else if (!strcmp(l->type, EXPR)) {
            prettyPrinter(l->left, "");
            printf(" ");
            prettyPrinter(l->right->left, "");
            prettyPrinter(l->right->right, "");
        } else if (!strcmp(l->type, PARAMLIST)) {
            printf("(");
            prettyPrinter(l->left, "");
            printf(", ");
            prettyPrinter(l->right, "");
            printf(")");
        } else if (!strcmp(l->type, PRIMARY)) {
            prettyPrinter(l->left, "");
            prettyPrinter(l->right, "");
        } else {
            printf("%s", l->sval);
        }
    }
}
