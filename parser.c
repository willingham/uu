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

    while(strcmp(p->pending->type, ENDOFFILE) != 0) {
        printf("%s\n", displayLexeme(p->pending));
        p->pending = lex(p);
    }
    return p->pending;
}

// 

int check(Parser *p, char *x) {
    return !strcmp(p->pending->type, x);
}

Lexeme *match(Parser *p, char *x) {
    if (check(p, x)) {
        return advance(p);
    } else {
        error("match error");
        printf("x: %s, Pending:  %s", x, p->pending->type);
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
           lambdaPending(p) || idPending(p) || operatorPending(p);
}

int operatorPending(Parser *p) {
    return check(p, MINUS) || check(p, PLUS) || check(p, DIVIDE) || check(p, MULTIPLY) || \
           check(p, NOT) || check(p, GT) || check(p, LT) || check(p, GTE) || check(p, LTE) || \
           check(p, ISEQUAL) || check(p, AND) || check(p, OR) || check(p, EQUALS);
}



// lhs grammar functions
void program(Parser *p) {
    expressionList(p);
    check(p, ENDOFFILE);
}

void expressionList(Parser *p) {
    expression(p);
    if (expressionListPending(p)) {
        expressionList(p);
    }
}

void expression(Parser *p) {
    if(exprPending(p)) {
        expr(p);
        match(p, SEMI);
    } else if (loopPending(p)) {
        loop(p);
    } else if (iffPending(p)) {
        iff(p);
    } else if (funcDefPending(p)) {
        funcDef(p);
    } else {
        error("Expression not found.");
        exit(1);
    }
}

void expr(Parser *p) {
    primary(p);
    if(operatorPending(p)) {
        operator(p);
        expr(p);
    }
}

void optParamList(Parser *p) {
    if(paramListPending(p)) {
        paramList(p);
    }
}
void paramList(Parser *p) {
    expr(p);
    if(exprPending(p)) {
        match(p, COMMA);
        paramList(p);
    }
}

void primary(Parser *p) {
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

void operator(Parser *p) {
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

void literal(Parser *p) {
    if (check(p, INT)) {
        match(p, INT);
    } else if (check(p, STRING)) {
        match(p, STRING);
    }
}

void funcDef(Parser *p) {
    match(p, FUNC);
    match(p, ID);
    match(p, OP);
    optParamList(p);
    match(p, CP);
    block(p);
}

void lambda(Parser *p) {
    match(p, LAMBDA);
    match(p, OP);
    optParamList(p);
    match(p, CP);
    block(p);
}

void loop(Parser *p) {
    if (whileePending(p)) {
        whilee(p);
    } else if (forrPending(p)) {
        forr(p);
    } else {
        error("Loop not found.");
        exit(1);
    }
}

void block(Parser *p) {
    match(p, OCB);
    expressionList(p);
    match(p, CCB);
}

void whilee(Parser *p) {
    match(p, WHILE);
    match(p, OP);
    expr(p);
    match(p, OP);
    block(p);
}

void forr(Parser *p) {
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

void iff(Parser *p) {
    match(p, IF);
    match(p, OP);
    expr(p);
    match(p, CP);
    block(p);
    optElse(p);
}

void optElse(Parser *p) {
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
