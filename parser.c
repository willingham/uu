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
    program(p);
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
Parser *program(Parser *p) {
    return expressionList(p);
    //check(p, ENDOFFILE);
}

Parser *expressionList(Parser *p) {
    Lexeme *l, *r = NULL;
    l = expression(p);
    if (expressionListPending(p)) {
        b = expressionList(p);
    }
    return cons(EXPRESSIONLIST, l, r);
}

Parser *expression(Parser *p) {
    if (loopPending(p)) {
        return loop(p);
    } else if (iffPending(p)) {
        return iff(p);
    } else if (funcDefPending(p)) {
        return funcDef(p);
    } else if(exprPending(p)) {
        Lexeme *x = expr(p);
        return x
        match(p, SEMI);
    } else {
        error("Expression not found.");
        exit(1);
    }
}

Parser *expr(Parser *p) {
    Lexeme *x, *y, *z = NULL;
    x = primary(p);
    if(operatorPending(p)) {
        y = operator(p);
        z = expr(p);
    }
    return cons(EXPR, x, cons(JOIN, y, z));
}

Parser *optParamList(Parser *p) {
    if(paramListPending(p)) {
        paramList(p);
    }
}
Parser *paramList(Parser *p) {
    expr(p);
    if(exprPending(p)) {
        match(p, COMMA);
        paramList(p);
    }
}

Parser *primary(Parser *p) {
    if(literalPending(p)) {
        literal(p);
    } else if(check(p, OP)) {
        match(p, OP);
        expr(p);
        match(p, CP);
    } else if(lambdaPending(p)) {
        lambda(p);
    } else if(check(p, ID)) {
        match(p, ID);
        if(check(p, OSB)) {
            match(p, OSB);
            literal(p);
            match(p, CSB);
        } else if(check(p, OP)) {
            match(p, OP);
            optParamList(p);
            match(p, CP);
        }
    } else if(operatorPending(p)) {
        operator(p);
        primary(p);
    } else {
        error("Primary not found.");
        exit(1);
    }
}

Parser *operator(Parser *p) {
    if (check(p, MINUS)) {
        match(p, MINUS);
    } else if (check(p, PLUS)) {
        match(p, PLUS);
    } else if (check(p, DIVIDE)) {
        match(p, DIVIDE);
    } else if (check(p, MULTIPLY)) {
        match(p, MULTIPLY);
    } else if (check(p, NOT)) {
        match(p, NOT);
    } else if (check(p, GT)) {
        match(p, GT);
    } else if (check(p, LT)) {
        match(p, LT);
    } else if (check(p, GTE)) {
        match(p, GTE);
    } else if (check(p, LTE)) {
        match(p, LTE);
    } else if (check(p, ISEQUAL)) {
        match(p, AND);
    } else if (check(p, OR)) {
        match(p, OR);
    } else if (check(p, EQUALS)) {
        match(p, EQUALS);
    } else {
        error("Operator not found.");
        exit(1);
    }
}

Parser *literal(Parser *p) {
    if (check(p, INT)) {
        match(p, INT);
    } else if (check(p, STRING)) {
        match(p, STRING);
    }
}

Parser *funcDef(Parser *p) {
    match(p, FUNC);
    match(p, ID);
    match(p, OP);
    optParamList(p);
    match(p, CP);
    block(p);
}

Parser *lambda(Parser *p) {
    match(p, LAMBDA);
    match(p, OP);
    optParamList(p);
    match(p, CP);
    block(p);
}

Parser *loop(Parser *p) {
    if (whileePending(p)) {
        whilee(p);
    } else if (forrPending(p)) {
        forr(p);
    } else {
        error("Loop not found.");
        exit(1);
    }
}

Parser *block(Parser *p) {
    match(p, OCB);
    expressionList(p);
    match(p, CCB);
}

Parser *whilee(Parser *p) {
    match(p, WHILE);
    match(p, OP);
    expr(p);
    match(p, CP);
    block(p);
}

Parser *forr(Parser *p) {
    match(p, FOR);
    match(p, OP);
    match(p, ID);
    match(p, SEMI);
    expr(p);
    match(p, SEMI);
    expr(p);
    match(p, CP);
    block(p);
}

Parser *iff(Parser *p) {
    match(p, IF);
    match(p, OP);
    expr(p);
    match(p, CP);
    block(p);
    optElse(p);
}

Parser *optElse(Parser *p) {
    if (check(p, ELSE)) {
        match(p, ELSE);
        if (blockPending(p)) {
            block(p);
        } else if (iffPending(p)) {
            iff(p);
        } else {
            error("optElse malformed.");
            exit(1);
        }
    }
}
