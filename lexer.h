#ifndef uuLexer
#define uuLexer
#include "parser.h"

extern void lex(void);
extern int isNewLine(int cur);
extern int isWhiteSpace(int cur);
extern int getChar(Parser *p);
extern void skipWhiteSpace(Parser *p);

#endif
