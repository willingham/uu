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

// lhs grammar functions
void program(Parser *p) {
    expressionList(p);
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
        error("Expression not found.\n");
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
        match(p, cp);
    } else if(lambdaPending(p)) {
        lembda(p);
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
        error("Primary not found.\n");
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
        error("Operator not found.\n");
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
        error("Loop not found.\n");
        exit(1);
    }
}

void block(Parser *p) {
    match(p, OCB);
    expressionList(p);
    match(p, CCB);
}

void whilee(Parser *p) {
    match(WHILE);
    match(p, OP);
    expr(p);
    match(p, OP);
    block(p);
}

void forr(Parser *p) {
    match(FOR);
    match(OP);
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
    if (check(ELSE)) {
        match(ELSE);
        if (blockPending(p)) {
            block(p);
        } else if (iffPending(p)) {
            iff(p);
        } else {
            error("optElse malformed.\n");
            exit(1);
        }
    }
}
