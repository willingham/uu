#ifndef uuParser
#define uuParser

#include <stdio.h>
#include "type.h"
#include "lexeme.h"

typedef struct parser {
    FILE *fIn;
    FILE *fOut;

    int line;
    Lexeme *pending;
} Parser;

extern Lexeme *parse(FILE *fIn);

#endif
