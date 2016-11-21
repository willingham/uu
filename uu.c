#include <stdio.h>
#include <stdlib.h>

#include "lexeme.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char **argv, char **env) {
    int pp = 0;  //pretty printer variable
    char *fname = argv[1];
    if(argc < 2) {
        fprintf(stderr, "Usage: ./uu <uu source file>\n");
        exit(1);
    } else if (argc == 3) {
        if (!strcmp(argv[1], "-pp")) {
            pp = 1;
            fname = argv[2];
        }
    }
    
    Lexeme *parseTree = parse(fopen(fname, "r"));
    pretty(parseTree);
    parseTree = NULL;
}
