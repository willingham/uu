#include <stdio.h>
#include <stdlib.h>
#include "lexeme.h"
#include "lexer.h"
#include "parser.h"
#include "env.h"
#include "eval.h"
#include "error.h"

void initEnv(Lexeme *env);
Lexeme *printUU(Lexeme *args);
Lexeme *printlnUU(Lexeme *args);
Lexeme *arrayUU(Lexeme *args);

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
    if (pp) {
        pretty(parseTree);
    }
    Lexeme *global = createEnv();
    initEnv(global);
    eval(parseTree, global);
    parseTree = NULL;
}

void initEnv(Lexeme *env) {
    Lexeme *var = newLexeme(ID);
    var->sval = "print";
    Lexeme *val = newLexeme(BUILTIN);
    val->fp = printUU;
    insert(var, val, env);

    var = newLexeme(ID);
    var->sval = "println";
    val = newLexeme(BUILTIN);
    val->fp = printlnUU;
    insert(var, val, env);

    var = newLexeme(ID);
    var->sval = "array";
    val = newLexeme(BUILTIN);
    val->fp = arrayUU;
    insert(var, val, env);
}

Lexeme *printUU(Lexeme *args) {
    Lexeme *result = NULL;
    while (args != NULL) {
        if (!strcmp(args->left->type, INT)) {
            printf("%d", args->left->ival);
        } else if (!strcmp(args->left->type, STRING)) {
            printf("%s", args->left->sval);
        } else {
            printf("Can't print type: %s\n", args->left->type);
            exit(1);
        }
        result = args;
        args = args->right;
    }
    return result;
}

Lexeme *printlnUU(Lexeme *args) {
    Lexeme *result = printUU(args);
    printf("\n");
    return result;
}

Lexeme *arrayUU(Lexeme *args) {
    if (args == NULL) {
        error("Not enough arguments for array\n");
        exit(1);
    } else if (args->right != NULL) {
        error("Too many arguments for array\n");
        exit(1);
    } else if (strcmp(args->left->type, INT)) {
        error("Argument to array must be an INT\n");
        exit(1);
    } else if (args->left->ival < 1) {
        error("Can't declare array with 0 or negative elements.\n");
        exit(1);
    } else {
        Lexeme *arr = newLexeme(ARRAY);
        arr->array = malloc(args->left->ival * sizeof(Lexeme *));
        for (int i = 0; i < args->left->ival; i++) {
            arr->array[i] = newLexeme(BAD);
        }
        return arr;
    }
}
