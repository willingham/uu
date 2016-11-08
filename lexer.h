#ifndef uuLexer
#define uuLexer
#include "parser.h"
#include "lexeme.h"

extern Lexeme *lex(Parser *p);
extern Lexeme *lexNumber(Parser *p, int i);
extern Lexeme *lexID(Parser *p, int i);
extern Lexeme *lexString(Parser *p, int i);
extern int isNewLine(int cur);
extern int isWhiteSpace(int cur);
extern int getChar(Parser *p);
extern void skipWhiteSpace(Parser *p);

#endif
