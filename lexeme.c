#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexeme.h"
#include "type.h"

Lexeme *newLexeme(char *type) {
    Lexeme *x = malloc(sizeof(Lexeme));
    x->type = type;
    x->sval = NULL;
    x->ival = 0;
    x->left = NULL;
    x->right = NULL;
    x->array = NULL;
    return x;
}

Lexeme *cons(Lexeme *l, Lexeme *r) {
    Lexeme *x = malloc(sizeof(Lexeme));
    x->type = NULL;
    x->left = l;
    x->right = r;
    return x;
}

Lexeme *car(Lexeme *x) {
    return x->left;
}

Lexeme *cdr(Lexeme *x) {
    return x->right;
}

void setCar(Lexeme *x, Lexeme *l) {
    x->left = l;
}

void setCdr(Lexeme *x, Lexeme *r) {
    x->right = r;
}

char *getType(Lexeme *x) {
    return x->type;
}

char *displayLexeme(Lexeme *x) {
    char *display = malloc(sizeof(char) * 128);
    if(x->type == STRING) {
        strcpy(display, x->type);
        strcat(display, " ");
        strcat(display, x->sval);
    } else if (x->type == INT) {
        strcpy(display, x->type);
        char buf[10];
        sprintf(buf, "%d", x->ival);
        strcat(display, " ");
        strcat(display, buf);
    } else {
        strcpy(display, x->type);
    }
    return display;
}
