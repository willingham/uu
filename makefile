OBJS=uu.o lexeme.o lexer.o type.o parser.o error.o
CFLAGS= 
uu: $(OBJS)
	gcc -Wall -g $(OBJS) -D uuDebug -o uu

uu.o: uu.c parser.c
	gcc -Wall -g $(CFLAGS) -c uu.c

lexeme.o: lexeme.c type.c
	gcc -Wall -g $(CFLAGS) -c lexeme.c

lexer.o: lexer.c lexeme.c type.c parser.c
	gcc -Wall -g $(CFLAGS) -c lexer.c

type.o: type.c
	gcc -Wall -g $(CFLAGS) -c type.c

parser.o: parser.c error.c
	gcc -Wall -g $(CFLAGS) -c parser.c

error.o: error.c
	gcc -Wall -g $(CFLAGS) -c error.c

run: uu
	./uu sample.uu

clean:
	rm -f ./*.o ./uu
