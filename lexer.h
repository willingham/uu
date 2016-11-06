#ifndef uuLexer
#define uuLexer
#include "parser.h"

extern void lex(void);
extern int isNewLine(char *cur);
extern int isWhiteSpace(char *cur);
extern void getChar(Parser *p);
extern void skipWhiteSpace(Parser *p);

#endif
