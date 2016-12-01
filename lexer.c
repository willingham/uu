#include "lexeme.h"
#include "lexer.h"
#include "parser.h"
#include "type.h"

Lexeme *lex(Parser *p) {
    int ch;
    skipWhiteSpace(p);
    ch = getChar(p);
    if (ch == EOF) return newLexeme(ENDOFFILE);

    switch(ch) {
        // single character tokens
        case '-':
            return newLexeme(MINUS);
        case '+':
            return newLexeme(PLUS);
        case '/':
            return newLexeme(DIVIDE);
        case '*':
            return newLexeme(MULTIPLY);
        case '!':
            return newLexeme(NOT);
        case '>':
            return newLexeme(GT);
        case '<':
            ch = getChar(p);
            if (ch == '=') {
                return newLexeme(LTE);
            }
            ungetc(ch, p->fIn);
            return newLexeme(LT);
        case '&':
            return newLexeme(AND);
        case '|':
            return newLexeme(OR);
        case '=':
            ch = getChar(p);
            if (ch == '=') {
                return newLexeme(ISEQUAL);
            }
            ungetc(ch, p->fIn);
            return newLexeme(EQUALS);
        case '(':
            return newLexeme(OP);
        case ')':
            return newLexeme(CP);
        case '[':
            return newLexeme(OSB);
        case ']':
            return newLexeme(CSB);
        case '{':
            return newLexeme(OCB);
        case '}':
            return newLexeme(CCB);
        case ';':
            return newLexeme(SEMI);
        case ',':
            return newLexeme(COMMA);
        
        default:
            // multi-character tokens
            // (only numbers, variables/keywords, and strings)
            if (isdigit(ch)) {
                return lexNumber(p, ch);
            } else if (isalpha(ch)) {
                return lexID(p, ch);  //and keywords!
            } else if (ch == '\"') {
                return lexString(p, ch);
            }
    }
    return newLexeme(BAD);
}

Lexeme *lexNumber(Parser *p, int i) {
    Lexeme *l = newLexeme(INT);
    char n[64] = "";
    int size = 1;
    n[0] = i;
    i = getChar(p);

    while (!isWhiteSpace(i) && isdigit(i)) {
        n[size++] = i;
        i = getChar(p);
    }

    ungetc(i, p->fIn);
    n[size++] = '\0';
    l->ival = atoi(n);
    l->sval = n;

    return l;

}

Lexeme *lexID(Parser *p, int i) {
    Lexeme *l = newLexeme(ID);
    char s[32] = "";
    int size = 1;
    s[0] = i;
    i = getChar(p);

    while(!isWhiteSpace(i) && (isalpha(i) || isdigit(i))) {
        s[size++] = i;
        i = getChar(p);
    }

    ungetc(i, p->fIn);
    s[size++] = '\0';
   
    if (!strcmp(s, "func")) {
        l->type = FUNC;
    } else if (!strcmp(s, "lambda")) {
        l->type = LAMBDA;
    } else if (!strcmp(s, "while")) {
        l->type = WHILE;
    } else if (!strcmp(s, "for")) {
        l->type = FOR;
    } else if (!strcmp(s, "if")) {
        l->type = IF;
    } else if (!strcmp(s, "else")) {
        l->type = ELSE;
    } else if (!strcmp(s, "nil")) {
        l->type = NIL;
    } else {
        l->sval = malloc(strlen(s) + 1);
        strcpy(l->sval, s);
        //l->sval = s;
    }
    return l;
}

Lexeme *lexString(Parser *p, int i) {
    Lexeme *l = newLexeme(STRING);
    char s[128] = "";
    int size = 0;
    //s[0] = i;
    i = getChar(p);

    while(i != '\"') {
        s[size] = i;
        size++;
        i = getChar(p);
    }

    s[size++] = '\0';
    l->sval = malloc(strlen(s) + 1);
    strcpy(l->sval, s);
    l->ival = size;
    //printf("s: %s", s);
    //printf("l->sval: %s", l->sval);
    
    return l;
}

int isNewLine(int cur) {
    return cur == '\r' || cur == '\n' || cur == '\t';  
}

int isWhiteSpace(int cur) {
    return isNewLine(cur) || cur == ' ';
}

int getChar(Parser *p) {
    int cur = fgetc(p->fIn);
    if (cur == '/') {
        int curr = fgetc(p->fIn);
        if (curr == '/') {
            while (!isNewLine(cur) && !feof(p->fIn)) {
                cur = fgetc(p->fIn);
            }
        } else {
            ungetc(curr, p->fIn);
        }
    }
    return cur;
}

void skipWhiteSpace(Parser *p) {
    int cur = getChar(p);
    while (isWhiteSpace(cur) && !feof(p->fIn)) {
        if (isNewLine(cur)) {
            p->line++;
        }
        cur = getChar(p);
    }
    ungetc(cur, p->fIn);
}

