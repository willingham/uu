OBJS=lexeme.o lexer.o type.o
uu: $(OBJS)
	gcc -Wall -g $(OBJS) -o uu

lexeme.o: lexeme.c
	gcc -Wall -g -c lexeme.c

lexer.o: lexer.c lexeme.c type.c
	gcc -Wall -g -c lexer.c

type.o: type.c
	gcc -Wall -g -c type.c

clean:
	rm -f ./*.o
