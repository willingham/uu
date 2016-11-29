OBJS=uu.o lexeme.o lexer.o type.o parser.o error.o env.o eval.o
CFLAGS=-D uuDebug
CFLAGS=
uu: $(OBJS)
	gcc -Wall -g $(OBJS) -D uuDebug -std=c99 -o dpl

uu.o: uu.c parser.c env.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c uu.c

lexeme.o: lexeme.c type.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c lexeme.c

lexer.o: lexer.c lexeme.c type.c parser.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c lexer.c

type.o: type.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c type.c

parser.o: parser.c error.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c parser.c

error.o: error.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c error.c

env.o: env.c lexeme.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c env.c

eval.o: eval.c lexeme.c type.c env.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c eval.c

run: uu
	./dpl sample.uu

clean:
	rm -f ./*.o ./uu

error1:
	cat error1.uu

error1x:
	./dpl error1.uu

error2:
	cat error2.uu

error2x:
	./dpl error2.uu

error3:
	cat error3.uu

error3x:
	./dpl error3.uu

arrays:
	cat arrays.uu

arraysx:
	./dpl arrays.uu

conditionals:
	cat conditionals.uu

conditionalsx:
	./dpl conditionals.uu

recursion:
	cat recursion.uu

recursionx:
	./dpl recursion.uu

iteration:
	cat iteration.uu

iterationx:
	./dpl iteration.uu

functions:
	cat functions.uu

functionsx:
	./dpl functions.uu

dictionary:
	cat dictionary.uu

dictionaryx:
	./dpl dictionary.uu

problem:
	cat problem.uu

problemx:
	./dpl problem.uu
demo: uu
	-make error1
	-make error1x
	-make error2
	-make error2x
	-make error3
	-make error3x
	-make arrays
	-make arraysx
	-make conditionals
	-make conditionalsx
	-make recursion
	-make recursionx
	-make iteration
	-make iterationx
	-make functions
	-make functionsx
	-make dictionary
	-make dictionaryx
	echo ******DEMO STUFF******
	cat consTest.uu
	./dpl consTest.uu
	cat stackTest.uu
	./dpl stackTest.uu
	cat print.uu
	./dpl print.uu

