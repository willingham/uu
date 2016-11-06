OBJS=lexeme.o lexer.o type.o parser.o
uu: $(OBJS)
	gcc -Wall -g $(OBJS) -o uu

lexeme.o: lexeme.c
	gcc -Wall -g -c lexeme.c

lexer.o: lexer.c lexeme.c type.c parser.c
	gcc -Wall -g -c lexer.c

type.o: type.c
	gcc -Wall -g -c type.c

parser.o: parser.c
	gcc -Wall -g -c parser.c

clean:
	rm -f ./*.o
