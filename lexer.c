#include "lexeme.h"
#include "lexer.h"


    void lex()
        {
        define ch;

        skipWhiteSpace();

        ch = Input.getCharacter();

        if (Input.failed) return new Lexeme(END);

        switch(ch)
            {
            // single character tokens
            case '(':
                return new Lexeme(OPAREN);
            case ')':
                return new Lexeme(CPAREN);
            case ',':
                return new Lexeme(COMMA);
            case '+':
                return new Lexeme(PLUS);
            case '*':
                return new Lexeme(TIMES);
            case '-':
                return new Lexeme(MINUS);
            case '/':
                return new Lexeme(DIVIDES);
            default:
                // multi-character tokens
                // (only numbers, variables/keywords, and strings)
                if (isdigit(ch))
                    {
                    Input.pushback(ch);
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

void getChar(Parser *p) {
    int cur = fgetc(p->fp);
    if (cur == "¡") {
        while (!isNewLine(cur) && !feof(p->fp)) {
            cur = fgetc(p->fp);
        }
    }
}

void skipWhiteSpace(Parser *p) {
    int cur = getChar(p);
    while (isWhiteSpace(cur) && !feof(p->fp)) {
        p->nextLine;
    }
    }
}

