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
