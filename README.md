MExpr
=====

Library that parse mathematical expression with implicit multiplications.

The library use bison and flex to parse a string that represent a mathematical expression. The parser was made to manage complex expression like this:

	_sum(2+2yx^2, -735)-3(_sum(1,2) + _sum(1,2,3))(-5x)
	
	
###Implicit multiplication

As you can see it use implicit multiplications, if you write `xy` the parser understands that you want multiply two variables `x` and `y`. But is not the only case where you can have an implicit multiplication, there are some examples:

	-3xy^2
	(3+3)(5-3)
	-(3-2)
	
But for this reason, you can't use variables that have more of a single character, because if you write `xy` the parser can't distinguishes if it is the variable `xy` or if it is `x * y`. In the future I write something to support multi-character variables, using some special symbols.


###Functions

Another problems is that if you write `f(x)` the parser can't distinguishes if it is a function `f` called with the `x` argument, or if it is a variable `f` that multiply the `(x)` expression. For this reason the functions always start with the `_` character. Now, `_f(x)` calls the `f` function and `f(x)` is a multiplication between the `f` and `x` variables.

The function can have more than one argument. For example you can define the function `_sum(a,b)` that sum two number. But you can define `_sum(a,b,c)` too, at the same time. In fact, the parser can manages overloaded function distinguishing the two function from the number of arguments.


###Environment

The Environment maintains the value associated to a variable symbol, and the pointer to a function associated to a function symbol. The Environment is dynamic, you may have a parsed expression that use the `_foo` function, but it has never been define. If you try to evaluate this expression, the interpreter give you an exception. Then, if you define the `_foo` function, you can evaluate the expression without any problem. Also, you can redefine function, or change the value of a defined variable. 


###STDFunctions

The library has a set of standard functions that you can use in your expression, the standard function is the same of the math.h library.

For example:

	_sqrt(_floor(_exp(5)))
	
The standard constants (like `pi` and `e`) will be introduced with the multiple-character variables.


How it works
------------

The library parse the input string and builds an AST Tree, for example the `-3xy^2` build this tree:

	[ * ]─[ -1 ]
  	  └───[ * ]─[ 3 ]
      	    └───[ * ]─[ x ]
          	      └───[ ^ ]─[ y ]
              	        └───[ 2 ]

Now, the library can evaluate the expression using the tree, it simply recursively navigate this tree.

In some case, for example when you must draw a function plot, you need to evaluate the same expression changing only the value of a variable. For this reason the library can "compile" the AST Tree to have a more efficient representation of the expression. The generated code is a simple bytecode that use a stack to compute operations.

This is the representation of the bytecode generated using the previous expression:

	VAL: -1
	VAL: 3
	VAR: x
	VAR: y
	VAL: 2
	POW
	MUL
	MUL
	MUL

###Function and variables

The Environment has two maps, the variables and the functions is stored in these map. 
After the expression is parsed, the AST Tree (and the code too) contains the name of the variable (or the name of the function) and not its value. On the contrary, in the evaluation phase the environment is interrogated to get the values and the function pointers.

To distinguish the function with the same name, but different number of arguments, the function `_foo` with one argument is internally called `_foo_1` and the other function, with the same name but with two arguments, is internally called `_foo_2`.


How to use it
-------------

The Makefile is configured to create a shared library, you can use it with your C++ programs linking dynamically this library.

Let's see an example of a little program that use it:

	#include <iostream>
	#include <MExpr.h>
	using namespace std;

	void myfunc(MExpr::StackType* s){ //myfunc(n) = n*3
		s->stack[s->stp-1] *= 3;
	}

	void myDiv(MExpr::StackType* s){ //myDiv(a,b) = a/b
		MExpr::ValueType arg1, arg2;
		arg1 = s->stack[s->stp-2];
		arg2 = s->stack[s->stp-1];
		s->stack[s->stp-2] = arg1 / arg2;
		s->stp--;
	}

	void mySum2(MExpr::StackType* s){ //mySum2(a,b) = a+b
		s->stack[s->stp-2] = s->stack[s->stp-2] + s->stack[s->stp-1];
		s->stp--;
	}
	void mySum3(MExpr::StackType* s){ //mySum2(a,b,c) = a+b+c
		s->stack[s->stp-3] = s->stack[s->stp-3]
		                   + s->stack[s->stp-2]
		                   + s->stack[s->stp-1];
		s->stp -= 2;
	}

	int main(int argc, char** argv){
		MExpr::Expression* e;
		MExpr::ValueType ris;

		string expr(argv[1]);

		try{
			/*the Expression constructor parse the string and make the AST Tree */
			e = new MExpr::Expression(expr);
		}catch(MExpr::Error ex){
			cout << "Err: " << ex.what() << endl;
			return 0;
		}

		try{
			//example variables definitions
			e->setVariable('x', 3);
			e->setVariable('y', 2);
			e->setVariable('z', 3);
			e->setVariable('x', 5); //variable redefinition

			//example functions definitions
			e->setFunction("_math", &myfunc, 1);
			e->setFunction("_div", &myDiv, 2);
			e->setFunction("_sum", &mySum2, 2); //example of overloaded function
			e->setFunction("_sum", &mySum3, 3); //example of overloaded function

		}catch(MExpr::Error ex){
			/* Catch errors if variable has strange symbols or function names 
			 * doesn't start with '_' */
			cout << "Err: " << ex.what() << endl;
		}

		try{
			e->setVariable('-', 3); //the error will be catch
		}catch(MExpr::Error ex){
			cout << "Err: " << ex.what() << endl;
		}
		try{
			e->setFunction("nounderscore", &mySum3, 3); //the error will be catch
		}catch(MExpr::Error ex){
			cout << "Err: " << ex.what() << endl;
		}

		cout << "AST Tree:" << endl;
		string* s = e->getExprTreeString();
		cout << *s;
		delete s;

		try{
			cout << "Result: " << e->evaluate() << endl;
		}catch(MExpr::Error ex){
			cout << "Err: " << ex.what() << endl;
		}

		e->compile();
		cout << "Compiled Expression Code:" << endl;
		s = e->getExprCodeString(); //if you have not compiled s will be NULL
		if(s != NULL){ cout << *s; delete s; }

		try{
			/* if you compiled the evaluation is made using the code (most efficient)
			 * it you have not compiled it is made navigating the AST tree */
			cout << e->evaluate() << endl;
		}catch(MExpr::Error ex){
			cout << "Err: " << ex.what() << endl;
		}

		delete e;
	    return 0;
	}


Now we need to compile it specifing the mexpr library:

	$ g++ -o myexample -lmexpr myexample.cpp
	
And now we can test all we want:

	$ ./myexample "_sum(2+2yx^2, -735)-3(_sum(1,2) + _sum(1,2,3))(-5x)"


How to compile
--------------

 - Ensure that you satisfy the requirements.
 - Open the Makefile and set your OS changing the `OperatingSystem` variable.
 - type `make` to compile the library

 If you want to install the library in `/usr/local/lib` type `sudo make install`
 
 
###Common issues

 - In Mac OS X, by default, doesn't have the `/usr/local` folder, check this one if the installation have some problems.
 - You can have some problem compiling your examples if you don't install it before, if you don't want to install it ensure that the `DYLD_LIBRARY_PATH` (or the `LD_LIBRARY_PATH`) was proudly configured.


Requirements
------------

Now, the library is done to work with Mac OSX an Linux.
To compile the library you need: bison, flex and g++.