#include "lexer.h"

    function lex()
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
