OBJS=uu.o lexeme.o lexer.o type.o parser.o error.o env.o eval.o
CFLAGS=-D uuDebug
CFLAGS=
uu: $(OBJS)
	gcc -Wall -g $(OBJS) -D uuDebug -o uu

uu.o: uu.c parser.c env.c
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

env.o: env.c lexeme.c
	gcc -Wall -g $(CFLAGS) -c env.c

eval.o: eval.c lexeme.c type.c env.c
	gcc -Wall -g $(CFLAGS) -c eval.c

run: uu
	./uu sample.uu

clean:
	rm -f ./*.o ./uu

error1:
	cat error1.uu

error1x:
	./uu error1.uu

error2:
	cat error2.uu

error2x:
	./uu error2.uu

error3:
	cat error3.uu

error3x:
	./uu error3.uu

arrays:
	cat arrays.uu

arraysx:
	./uu arrays.uu

conditionals:
	cat conditionals.uu

conditionalsx:
	./uu conditionals.uu

recursion:
	cat recursion.uu

recursionx:
	./uu recursion.uu

iteration:
	cat iteration.uu

iterationx:
	./uu iteration.uu

functions:
	cat functions.uu

functionsx:
	./uu functions.uu

dictionary:
	cat dictionary.uu

dictionaryx:
	./uu dictionary.uu
