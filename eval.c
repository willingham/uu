#include <stdio.h>
#include "eval.h"
#include "lexeme.h"
#include "type.h"
#include "env.h"

void evals(Lexeme *tree, Lexeme *env) {
    char *type = tree->type;
    if (!strcmp(type, INT)) {
    } else if (!strcmp(type, STRING )) {
    } else if (!strcmp(type, VARIABLE)) {
    } else if (!strcmp(type, PLUS)) {
    } else if (!strcmp(type, MINUS)) {
    } else if (!strcmp(type, TIMES)) {
    } else if (!strcmp(type, DIVIDE)) {
    } else if (!strcmp(type, GT)) {
    } else if (!strcmp(type, LT)) {
    } else if (!strcmp(type, GTE)) {
    } else if (!strcmp(type, LTE)) {
    }
}

void eval(Lexeme *tree, Lexeme *env) {
    if (tree != NULL) {
        if (!strcmp(tree->type, STRING)) {
            printf("\"%s\"", tree->sval);
        } else if (!strcmp(tree->type, INT)) {
            printf("%d", tree->ival);
        } else if (!strcmp(tree->type, ID) || !strcmp(tree->type, FUNC)) {
            printf("%s", tree->sval);
        } else if (!strcmp(tree->type, FUNCDEF)) {
            printf("func ");
            prettyPrinter(tree->left, "");
            prettyPrinter(tree->right->left, "");
            prettyPrinter(tree->right->right, "");
        } else if (!strcmp(tree->type, EXPRESSIONLIST)) {
            prettyPrinter(tree->left, "");
            if (!strcmp(tree->left->type, EXPR)) {

                printf("; \n");
            }
            prettyPrinter(tree->right, "");
        } else if (!strcmp(tree->type, EXPR)) {
            prettyPrinter(tree->left, "");
            printf(" ");
            prettyPrinter(tree->right->left, "");
            prettyPrinter(tree->right->right, "");
        } else if (!strcmp(tree->type, PARAMLIST)) {
            prettyPrinter(tree->left, "");
            if (tree->right) {
                printf(", ");
            }
            prettyPrinter(tree->right, "");
        } else if (!strcmp(tree->type, PRIMARY)) {
            prettyPrinter(tree->left, "");
            prettyPrinter(tree->right, "");
        } else if (!strcmp(tree->type, LAMBDA)) {
            prettyPrinter(tree->left, "");
            prettyPrinter(tree->right, "");
        } else if (!strcmp(tree->type, WHILE)) {
            printf("while (");
            prettyPrinter(tree->left, "");
            printf(")\n");
            prettyPrinter(tree->right, "");
        } else if (!strcmp(tree->type, IF)) {
            printf("if (");
            prettyPrinter(tree->left, "");
            printf(")\n");
            prettyPrinter(tree->right->left, "");
            prettyPrinter(tree->right->right, "");
        } else if (!strcmp(tree->type, BLOCK)) {
            printf("{\n");
            prettyPrinter(tree->left, "");
            printf("}\n");
        } else if (!strcmp(tree->type, OPTPARAMLIST)) {
            printf("(");
            prettyPrinter(tree->left, "");
            printf(") ");
        } else if (!strcmp(tree->type, OPTELSE)) {
            if (tree->left != NULL) {
                if (!strcmp(tree->left->type, BLOCK)) {
                    printf(" else ");
                    prettyPrinter(tree->left, "");
                } else if (!strcmp(tree->left->type, IF)) {
                    printf(" else ");
                    prettyPrinter(tree->left, "");
                }
            }
        } else if (!strcmp(tree->type, FOR)) {
            printf("for (");
            prettyPrinter(tree->left->left, "");
            printf("; ");
            prettyPrinter(tree->left->right, "");
            printf("; ");
            prettyPrinter(tree->right->left, "");
            printf(") ");
            prettyPrinter(tree->right->right, "");
        } else if (!strcmp(tree->type, MINUS)) {
            printf(" - ");
        } else if (!strcmp(tree->type, PLUS)) {
            printf(" + ");
        } else if (!strcmp(tree->type, DIVIDE)) {
            printf(" / ");
        } else if (!strcmp(tree->type, MULTIPLY)) {
            printf(" * ");
        } else if (!strcmp(tree->type, NOT)) {
            printf(" ! ");
        } else if (!strcmp(tree->type, GT)) {
            printf(" > ");
        } else if (!strcmp(tree->type, LT)) {
            printf(" < ");
        } else if (!strcmp(tree->type, GTE)) {
            printf(" >= ");
        } else if (!strcmp(tree->type, LTE)) {
            printf(" <= ");
        } else if (!strcmp(tree->type, ISEQUAL)) {
            printf(" == ");
        } else if (!strcmp(tree->type, AND)) {
            printf(" & ");
        } else if (!strcmp(tree->type, OR)) {
            printf(" | ");
        } else if (!strcmp(tree->type, EQUALS)) {
            printf(" = ");
        } //else {
            //printf("%s", tree->sval);
       // }
    }
}
