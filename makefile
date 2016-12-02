OBJS=uu.o lexeme.o lexer.o type.o parser.o error.o env.o eval.o
CFLAGS=-D uuDebug
CFLAGS=
export CFLAGS
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
	@echo ""
	@echo "##################################"
	@echo "######## error1"
	@echo "##################################"
	@echo ""
	-make error1
	-make error1x
	@echo ""
	@echo "##################################"
	@echo "######## error2"
	@echo "##################################"
	@echo ""
	-make error2
	-make error2x
	@echo ""
	@echo "##################################"
	@echo "######## error3"
	@echo "##################################"
	@echo ""
	-make error3
	-make error3x
	@echo ""
	@echo "##################################"
	@echo "######## arrays"
	@echo "##################################"
	@echo ""
	-make arrays
	-make arraysx
	@echo ""
	@echo "##################################"
	@echo "######## conditionals"
	@echo "##################################"
	@echo ""
	-make conditionals
	-make conditionalsx
	@echo ""
	@echo "##################################"
	@echo "######## recursion"
	@echo "##################################"
	@echo ""
	-make recursion
	-make recursionx
	@echo ""
	@echo "##################################"
	@echo "######## iteration"
	@echo "##################################"
	@echo ""
	-make iteration
	-make iterationx
	@echo ""
	@echo "##################################"
	@echo "######## functions"
	@echo "##################################"
	@echo ""
	-make functions
	-make functionsx
	@echo ""
	@echo "##################################"
	@echo "######## dictionary"
	@echo "##################################"
	@echo ""
	-make dictionary
	-make dictionaryx
	echo ******DEMO STUFF******
	@echo ""
	@echo "##################################"
	@echo "######## cons, car, cdr"
	@echo "##################################"
	@echo ""
	cat consTest.uu
	./dpl consTest.uu
	@echo ""
	@echo "##################################"
	@echo "######## stack"
	@echo "##################################"
	@echo ""
	cat stackTest.uu
	./dpl stackTest.uu
	@echo ""
	@echo "##################################"
	@echo "######## print"
	@echo "##################################"
	@echo ""
	cat print.uu
	./dpl print.uu
	@echo ""
	@echo "##################################"
	@echo "######## stdlib: ds"
	@echo "##################################"
	@echo ""
	cat ds.uu
	@echo ""
	@echo "##################################"
	@echo "######## stdlib: math"
	@echo "##################################"
	@echo ""
	cat math.uu

