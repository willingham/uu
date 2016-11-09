#include <stdio.h>
#include <stdlib.h>

#include "lexeme.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char **argv, char **env) {
    if(argc != 2) {
        fprintf(stderr, "Usage: ./uu <uu source file>\n");
        exit(1);
    }
    
    Lexeme *parseTree = parse(fopen(argv[1], "r"));

}
