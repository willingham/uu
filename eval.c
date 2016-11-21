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

Lexeme *eval(Lexeme *tree, Lexeme *env) {
    if (tree != NULL) {
        if (!strcmp(tree->type, STRING)) {
            printf("\"%s\"", tree->sval);
        } else if (!strcmp(tree->type, INT)) {
            printf("%d", tree->ival);
        } else if (!strcmp(tree->type, ID) || !strcmp(tree->type, FUNC)) {
            printf("%s", tree->sval);
        } else if (!strcmp(tree->type, FUNCDEF)) {
            printf("func ");
            eval(tree->left);
            eval(tree->right->left);
            eval(tree->right->right);
        } else if (!strcmp(tree->type, EXPRESSIONLIST)) {
            eval(tree->left);
            if (!strcmp(tree->left->type, EXPR)) {

                printf("; \n");
            }
            eval(tree->right);
        } else if (!strcmp(tree->type, EXPR)) {
            eval(tree->left);
            printf(" ");
            eval(tree->right->left);
            eval(tree->right->right);
        } else if (!strcmp(tree->type, PARAMLIST)) {
            eval(tree->left);
            if (tree->right) {
                printf(", ");
            }
            eval(tree->right);
        } else if (!strcmp(tree->type, PRIMARY)) {
            eval(tree->left);
            eval(tree->right);
        } else if (!strcmp(tree->type, LAMBDA)) {
            eval(tree->left);
            eval(tree->right);
        } else if (!strcmp(tree->type, WHILE)) {
            printf("while (");
            eval(tree->left);
            printf(")\n");
            eval(tree->right);
        } else if (!strcmp(tree->type, IF)) {
            printf("if (");
            eval(tree->left);
            printf(")\n");
            eval(tree->right->left);
            eval(tree->right->right);
        } else if (!strcmp(tree->type, BLOCK)) {
            printf("{\n");
            eval(tree->left);
            printf("}\n");
        } else if (!strcmp(tree->type, OPTPARAMLIST)) {
            printf("(");
            eval(tree->left);
            printf(") ");
        } else if (!strcmp(tree->type, OPTELSE)) {
            if (tree->left != NULL) {
                if (!strcmp(tree->left->type, BLOCK)) {
                    printf(" else ");
                    eval(tree->left);
                } else if (!strcmp(tree->left->type, IF)) {
                    printf(" else ");
                    eval(tree->left);
                }
            }
        } else if (!strcmp(tree->type, FOR)) {
            printf("for (");
            eval(tree->left->left);
            printf("; ");
            eval(tree->left->right);
            printf("; ");
            eval(tree->right->left);
            printf(") ");
            eval(tree->right->right);
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
