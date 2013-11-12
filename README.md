MExpr
=====

<p>Library that parses mathematical expressions with implicit multiplications.</p>

<p>The library uses bison and flex to parse a string that represents a mathematical expression. The parser was made to manage complex expressions like this:</p>

<pre><code>2 + 2yx^2 - 3(_sum(1,2) + _sum(1,2,3))(-5x)
</code></pre>

<h3>Implicit multiplications</h3>

<p>If you write <code>xy</code>, the parser understands that you want to multiply two variables: <code>x</code> and <code>y</code>. But this is not the only case where you can have an implicit multiplication, there are some other examples:</p>

<pre><code>-3xy^2
(3+3)(5-3)
-(3-2)
</code></pre>

<p>But for this reason, you can't use variables that have more than a single character. Infact, if you write <code>xy</code>, the parser can&rsquo;t distinguish between the variable <code>xy</code> and the multiplication <code>x * y</code>.</p>

<h3>Functions</h3>

<p>Another problems, is that if you write <code>f(x)</code> the parser can&rsquo;t distinguish between the function <code>f</code> called with the <code>x</code> argument and the variable <code>f</code> that multiplies the <code>(x)</code> expression. For this reason, the functions always start with the <code>_</code> character. Now, <code>_f(x)</code> calls the <code>f</code> function and <code>f(x)</code> is a multiplication between the <code>f</code> and <code>x</code> variables.</p>

<p>The function can have more than one argument. For example, you can define the function <code>_sum(a,b)</code> that adds two numbers. Furthermore, you can define <code>_sum(a,b,c)</code> too, that adds three numbers. In fact, the parser can manage overloaded functions distinguishing the functions by the number of arguments.</p>

<h3>Environment</h3>

<p>The parser has a dynamic environment, that maintains all the value associated to a variable symbol. Moreover, for each function symbol, it maintains a pointer to the associated function. Also, you can redefine a defined function, or change the value of a defined variable (especially if you're drawing a plot).</p>

<h3>STDFunctions</h3>

<p>The library has a set of standard functions that you can use in your expressions. This functions are the same of the math.h standard library.</p>

<p>For example:</p>

<pre><code>_sqrt(_floor(_exp(5)))
</code></pre>

<p>uses the math.h functions: <code>sqrt</code>, <code>floor</code> and <code>exp</code>.</p>

<p>The standard constants (like <code>pi</code> and <code>e</code>) will be introduced with the multiple-character variables.</p>

<h2>How it works</h2>

<p>The library parses the input string and then it builds an AST Tree. For example, with the expression <code>-3xy^2</code>, the parser builds this tree:</p>

<pre><code>[ * ]─[ -1 ]
  └───[ * ]─[ 3 ]
        └───[ * ]─[ x ]
              └───[ ^ ]─[ y ]
                    └───[ 2 ]
</code></pre>

<p>Now, the library can evaluate the expression using the tree (this is done browsing recursively this tree).</p>

<p>In some cases, for example when you want to draw a plot, you need to evaluate the same expression changing only the value of a variable. For this reason, the library can &ldquo;compiles&rdquo; the AST Tree to have a more efficient representation of the expression. The generated code is a simple bytecode, that uses a stack to compute operations (similarly to the Java bytecode).</p>

<p>This is the representation of the bytecode generated using the previous expression:</p>

<pre><code>VAL: -1
VAL: 3
VAR: x
VAR: y
VAL: 2
POW
MUL
MUL
MUL
</code></pre>

<h3>Functions and variables</h3>

<p>The Environment has two maps: one for the variables and one for the functions.
After that the expression is parsed, the AST Tree (and the code too) contains the name of the variables (or the name of the functions) and not their values. On the contrary, in the evaluation phase the environment is questioned to get the values and the function pointers.</p>

<p>To distinguish the functions with the same name, but different number of arguments, the environment uses different names. For example, the function <code>_foo</code> with one argument is internally called <code>_foo_1</code>, the other function, with the same name but with two arguments, is internally called <code>_foo_2</code>. This makes the things simpler, instead of using <code>va_arg</code></p>

<h2>How to use it</h2>

<p>The Makefile is configured to create a shared library, you can use it with your C++ programs dynamically linking this library.</p>

<p>Let's me show an example of a little program that use it:</p>

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

<p>Now we need to compile it specifing the mexpr library:</p>

<pre><code>$ g++ -o myexample -lmexpr myexample.cpp
</code></pre>

<p>And now we can test all we want:</p>

<pre><code>$ ./myexample "_sum(2+2yx^2, -735)-3(_sum(1,2) + _sum(1,2,3))(-5x)"
</code></pre>

<h2>How to compile</h2>

<ul>
<li>Ensure that you satisfy the requirements.</li>
<li>Open the Makefile and set your OS changing the <code>OperatingSystem</code> variable.</li>
<li>Type <code>make</code> to compile the library</li>
</ul>


<p> If you want to install the library in <code>/usr/local/lib</code> type <code>sudo make install</code></p>

<h3>Common issues</h3>

<ul>
<li>Mac OS X, by default, doesn&rsquo;t have the <code>/usr/local/lib</code> and <code>/usr/local/include</code> folders, check that you have these folders.</li>
<li>You can have some problems compiling your examples if you don&rsquo;t install it before. If you don&rsquo;t want to install it, ensure that the <code>DYLD_LIBRARY_PATH</code> (or the <code>LD_LIBRARY_PATH</code>) was proudly configured.</li>
</ul>


<h2>Requirements</h2>

<p>Now, the library is done to work with Mac OSX an Linux.
To compile the library you need: bison, flex and g++.</p>
