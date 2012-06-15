/*
 * MExpr C++ Tests
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

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
//while(true){ //de-comment to check memory leaks

	MExpr::Expression* e;
	MExpr::ValueType ris;

	string expr(argv[1]);

	try{
		/*the Expression constructor parse the string and make the AST Tree */
		e = new MExpr::Expression(expr);
	}catch(MExpr::Error ex){
		switch(ex.getType()){
		case MExpr::Error::lexError:
		case MExpr::Error::syntaxError:
			cout << "Err: " << ex.what() << endl;
		}
		return 0;
		//continue; //de-comment to check memory leaks
	}

	try{
		//example variables definitions
		e->setVariable('x', 3);
		e->setVariable('y', 2);
		e->setVariable('z', 3);
		e->setVariable('x', 5); //variable redefinition, old value will be canceled

		//example functions definitions
		e->setFunction("_math", &myfunc, 1);
		e->setFunction("_div", &myDiv, 2);
		e->setFunction("_sum", &mySum2, 2); //_sum is an example of overloaded function
		e->setFunction("_sum", &mySum3, 3); //_sum is an example of overloaded function

	}catch(MExpr::Error ex){
		//Catch errors if variable has strange symbols or function names doesn't start with '_'
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

	//e->compile();
	cout << "Compiled Expression Code:" << endl;
	s = e->getExprCodeString(); //if you have not compiled s will be NULL
	if(s != NULL){
		cout << *s;
		delete s;
	}

	try{
		/*
		 * if you compiled the evaluation is made using the code (most efficient)
		 * it you have not compiled it is made navigating the AST tree
		 * */
		cout << e->evaluate() << endl;
	}catch(MExpr::Error ex){
		cout << "Err: " << ex.what() << endl;
	}

	delete e;

//} //de-comment to check memory leaks

    return 0;
}
