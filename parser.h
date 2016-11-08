#ifndef uuParser
#define uuParser

#include <stdio.h>

typedef struct parser {
    FILE *fIn;
    FILE *fOut;

    int line;

} Parser;

#endif
