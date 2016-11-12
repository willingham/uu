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
void program(void) {
    expressionList();
}

void expressionList(void) {
    expression();
    if (expressionListPending()) {
        expressionList();
    }
}

void expression(void) {
    if(exprPending()) {
        expr();
        match(SEMI);
    } else if (loopPending()) {
        loop();
    } else if (iffPending()) {
        iff();
    } else if (funcDefPending()) {
        funcDef();
    } else {
        error("Expression not found.\n");
        exit(1);
    }
}

void expr(void) {
    primary();
    if(operatorPending()) {
        operator();
        expr();
    }
}

void optParamList(void) {
    if(paramListPending()) {
        paramList();
    }
}
void paramList(void) {
    expr();
    if(exprPending()) {
        match(COMMA);
        paramList();
    }
}

void primary(void) {
    if(literalPending()) {
        literal();
    } else if(check(OP)) {
        match(OP);
        expr();
        match(cp);
    } else if(lambdaPending()) {
        lembda();
    } else if(check(ID)) {
        match(ID);
        if(check(OSB)) {
            match(OSB);
            literal();
            match(CSB);
        } else if(check(OP)) {
            match(OP);
            optParamList();
            match(CP);
        }
    } else if(operatorPending()) {
        operator();
        primary();
    } else {
        error("Primary not found.\n");
        exit(1);
    }
}

extern void operator(void);
extern void literal(void);
extern void funcDef(void);
extern void lambda(void);
extern void loop(void);
extern void block(void);
extern void whilee(void);
extern void forr(void);
extern void iff(void);
extern void optElse(void);
