# uu
The double u programming language.

## Features
  - Inline comments are possible with a '!'.
  - Run 'dpl -pp' to see the pretty printer.
    This will print out the parse tree without evaluating anything.  The pretty printer is a fixed-point combinator for all valid uu syntax.
  - Lambdas can be passed as variables in between functions.
  - Arrays with constant access time.  
  - Ints and Strings
  - while and for loops
  - recursion
  - comments
  - dynamic typing

## Compiling and running
  To compile uu, simply run
  ```sh
  make clean
  make
  dpl <your input file>
  ```
 
## Test functions
The following make commands allow for testing of various aspects of the language.
```sh
make error1
make error1x
make error2
make error2x
make error3
make error3x
make arrays
make arraysx
make conditionals
make conditionalsx
make recursion
make recursionx
make iteration
make iterationx
make functions
make functionsx
```

## Standard Library
These functions are ready for use in any uu program.
  - cons(a, b)
  - car(a)
  - setCar(a)
  - cdr(a)
  - setCdr(a)

  - stack()
  - push(item, stack)
  - pop(stack)
  - peek(stack)

  - print(items, to, print)
  - println(items, to, print)

  - min(a, b)
  - max(a, b)

  - node()
  - getParent(n)
  - setParent(n)
  - getGrandparent(n)
  - getValue(n)
  - setValue(n)
  - getLeft(n)
  - setLeft(n)
  - getRight(n)
  - setRight(n)

## Example function
```go
func test () {
    wer = 5;
    if(wer == 1) {
        print("wer");
    } else if (wer == 2) {
        print("wer");
        a[2];
    }
    while(wer == 1) {
        wer = wer + 1;
    }
    for(i = 4309; i < 4321; i = i + 1) {
        println(i);
    }
}
test();
```

## Grammar
This is the grammar for the uu language.
![alt tag](https://github.com/thwillingham/uu/blob/master/grammar.png)

## Parse Tree
This is the structure in which programs are parsed and then evaluated.
![alt tag](https://github.com/thwillingham/uu/blob/master/parseTree.png)
