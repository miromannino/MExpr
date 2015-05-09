# MExpr

C++ library that parses human-like arithmetic expressions like the following:

	-3xy^2 - 3(_sum(1,2) + _sum(1,2,3))(-5x)

To understand better, let's make some examples comparing them to the more traditional computer-like notation:

<table class="table">
	<tr><th>MExpr notation</th><th>Traditional computer-like notation</th></tr>
	<tr><td>3xy</td><td>3 \* x \* y</td></tr>
	<tr><td>-3(x + y)</td><td>-3 \* (x + y)</td></tr>
	<tr><td>(x + y)(x + 4)</td><td>(x + y) \* (x + 4)</td></tr>
</table>


## Features

### Implicit multiplications

The parser interprets the text to detect implicit multiplication. For example the expression `xy` is interpreted as `x * y`, and the expression `-3(x + y)(x + 4)` as `-3 * (x + y) * (x + 4)`.

### One character variables

Like the arithmetic expression which we are used to write in a sheet of paper, the variables are single-character words like: `x`, `y`, etc.

That has opened the possibility to recognize implicit multiplications in a expression like: `xy^2`.

That is also an assumption which we have in our minds, and that allow us to interprets `xy` as a multiplication between the variables `x` and `y`, rather than the single variable `xy`.

### Bytecode compilation

The library parses the input string and then it builds an abstract syntax tree. For example, with the expression <code>-3xy^2</code>, the parser builds the following abstract syntax tree:

	[ * ]─[ -1 ]
	  └───[ * ]─[ 3 ]
	        └───[ * ]─[ x ]
	              └───[ ^ ]─[ y ]
	                    └───[ 2 ]

<br/>

<p>At this point, the library can directly evaluate the expression using the tree (browsing it recursively).</p>

<p>In some cases, for example when you want to draw a plot, you need to evaluate the same expression changing only the value of a variable. For this reason, the library can "compile" the AST to have a more efficient representation of the expression. The generated code is a simple bytecode, that uses a stack to compute operations (similarly to the Java bytecode).</p>

<p>This is the representation of the bytecode generated using the previous expression:</p>

	VAL: -1
	VAL: 3
	VAR: x
	VAR: y
	VAL: 2
	POW
	MUL
	MUL
	MUL

<br/>

### Functions

MExpr has the possibility to use functions inside the expression.

The library comes with all the functions of _math.h_. Furthermore, one can also
insert new custom functions that can do almost anything!

All the function names starts with the underscore character, for example `_f(x)`. This notation is important
because it allows to disambiguate expressions like `f(x)`. In fact, that could be interprets as a multiplication
between the variables `f` and `x`, or as the call of the function `f` passing `x` as argument. On the contrary
`_f(x)` has only one interpretation.

#### Function overloading

The functions can be overloaded. For example, one can define the function `_sum(a,b)` that adds two numbers.
Furthermore, one can also define `_sum(a,b,c)`. The parser can manage overloaded functions distinguishing
the functions by the number of parameters.</p>


### Dynamic environment

The parser has a dynamic environment, that maintains all the value associated to a variable symbol. Moreover, for each function symbol, it maintains a pointer to the associated function.

This approach allows one to define a variable or a function even after the expression parsing (as well as the expression compilation). For the same reason one can redefine a previously defined function, or change the value of a variable (useful if one is drawing a plot).


## How to use it

The following examples introduces how to use MExpr in your own project. Those examples are also available in the `test` folder and compiled in the `build/test/` folder.

### Example 1

This example shows how to create an expression, assign some values to its variables and print its value.

    Expression* e = new Expression("-3(4xy^2x-2x)(8x^-(3x)+2y^-2)");
    e->setVariable('x', 4);
    e->setVariable('y', -5);

    cout << e->evaluate() << endl;

<br/>

### Example 2

This example shows how MExpr could be used to repeatedly evaluate the same expression, only changing the value of a variable.
The expression is previously compiled, to allow a faster evaluation.

    Expression* e = new Expression("x^2");
    e->compile(); //To allow a faster evaluations (e.g. to draw a plot)

    for (int i = 0; i < 10; i++) {
        e->setVariable('x', i);
        cout << e->evaluate() << ' ';
    }
    cout << endl;

<br/>

### Example 3

This example shows how to print in the console the tree representation and the bytecode representation of the expression.

	Expression* e = new Expression("-3xy^2");

    cout << "Expression AST: " << endl;
    string* s = e->getExprTreeString();
    cout << *s;
    delete s;

    e->compile();

    cout << endl << "Compiled expression: " << endl;
    s = e->getExprCodeString();
    cout << *s;
    delete s;

<br/>

### Example 4

This example shows how to create and use a custom function inside the expression.

	 // myDiv(a, b) = a / b
	void myDiv(MExpr::StackType* s) {
	    MExpr::ValueType arg1, arg2;
	    arg1 = s->stack[s->stp - 2];
	    arg2 = s->stack[s->stp - 1];
	    s->stack[s->stp - 2] = arg1 / arg2;
	    s->stp--;
	}

	int main(void) {
	    Expression* e = new Expression("_div(16,4)");
	    e->setFunction("_div", &myDiv, 2);

	    cout << e->evaluate() << endl;

	    return 0;
	}

<br/>

### Compile your code that uses MExpr

The Makefile is configured to create a shared library, you can use it with your C++ programs dynamically linking this library.

	g++ -o myExample -lmexpr myExample.cpp

<br/>

## How to compile MExpr

 - Ensure that you satisfy the requirements.
 - Open the Makefile and set your OS changing the `OperatingSystem` variable.

Run the command you need 

 - `make all` to compile the library
 - `make run-tests` to run the tests
 - `make clean-gtest` to remove the GoogleTest library folder
 - `make install` to install the library in `/usr/local/lib`
	

### Common issues

- Mac OS X, by default, doesn't have the `/usr/local/lib` and `/usr/local/include` folders, check that you have these folders.
- You can have some problems compiling your examples if you don't install it before. If you don't want to install it, ensure that the `DYLD_LIBRARY_PATH` (or the `LD_LIBRARY_PATH`) was proudly configured.
- Ensure that you have installed `wget`, that is used to download the GoogleTest library


## Requirements

Tested operating systems: OSX, Linux

To compile the library you need: bison, flex and g++.

GoogleTests library: but is automatically downloaded in the `gtest` folder during the building process (i.e. `make all`).

## License

This project is licensed under the MIT license
