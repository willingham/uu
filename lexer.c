#include "lexeme.h"
#include "lexer.h"
#include "parser.h"
#include "type.h"

void lex(Parser *p) {
    int ch;
    skipWhiteSpace(p);
    ch = getChar(p);
    if (Input.failed) return Lexeme(ENDOFFILE);

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
            return newLexeme(LT);
        case '&':
            return newLexeme(AND);
        case '|':
            return newLexeme(OR);
        case '=':
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
            return newLexeme(OSB);
        case ';':
            return newLexeme(SEMI);
        case ',':
            return newLexeme(COMMA);
        
        default:
            // multi-character tokens
            // (only numbers, variables/keywords, and strings)
            if (isdigit(ch)) {
                ungetc(ch, p->fIn);
                return lexNumber();
                }
            else if (isalpha(ch))
                    {
                    Input.pushback(ch);
                    return lexVariable();  //and keywords!
                    }
                else if (ch == '\"')
                    {
                    Input.pushback(ch);
                    return lexString();
                    }
            }

        return new Lexeme(BAD_CHARACTER, ch);
        }

int isNewLine(int cur) {
    char *newLine = "\r\n\t";
    return strstr(newLine, cur) != NULL;  
}

int isWhiteSpace(int cur) {
    return isNewLine(cur) || cur == ' ';
}

int getChar(Parser *p) {
    int cur = fgetc(p->fIn);
    if (cur == '!') {
        while (!isNewLine(cur) && !feof(p->fIn)) {
            cur = fgetc(p->fIn);
        }
    }
    return cur;
}

void skipWhiteSpace(Parser *p) {
    int cur = getChar(p);
    while (isWhiteSpace(cur) && !feof(p->fIn)) {
        p->line++;
    }
}

