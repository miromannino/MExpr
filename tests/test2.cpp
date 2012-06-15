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

#include <cstddef>
#include <stdio.h>
#include <iostream>
#include <map>
#include <string.h>
#include <time.h>
#include <MExpr.h>
using namespace std;
using namespace MExpr;

#define EVALUATIONS 10000000

int main(void){
//while(true){ //de-comment to check memory leaks

	for(int iter=0; iter<3; iter++){

		string expr;
		switch(iter){
		case 0:
			expr = "+2+3*5+2-2*3+(7^-3-8+5)-4+(3/3)+2*5-6-(9-(3^4)+6)-6+8/7-8";
			break;
		case 1:
			expr = "_sqrt(2_sqrt(2))";
			break;
		case 2:
			expr = "-3(4xy^2x-2x)(8x^-(3x)+2y^-2)";
			break;
		}
		cout << "Expr: " << expr << endl;

		Expression* e;

		try{
			e = new Expression(expr);
			e->compile();
		}catch(Error ex){
			cout << "Err: " << ex.what() << endl;
			return 0;
		}

		string* tr = e->getExprTreeString();
		cout << "Expr AST Tree: " << endl << *tr << endl;
		delete tr;

		e->setVariable('x', 4);
		e->setVariable('y', -5);

		clock_t start,end;

		start = clock();
		try{
			for(int i = 0; i<EVALUATIONS; i++){
				e->evaluate(true); //tree evaluation with the parameter set 'true'
			}
		}catch(MExpr::Error ex){
			cout << "Err: " << ex.what() << endl;
		}

		end = clock();
		printf ("Time for %d evaluations navigating the AST: %lf\n", EVALUATIONS, (double)(end - start) / CLOCKS_PER_SEC);

		start = clock();
		try{
			for(int i = 0; i<EVALUATIONS; i++){
				e->evaluate();
			}
		}catch(MExpr::Error ex){
			cout << "Err: " << ex.what() << endl;
		}
		end = clock();
		printf ("Time for %d evaluations in bytecode: %lf\n", EVALUATIONS, (double)(end - start) / CLOCKS_PER_SEC);

		delete e;

	}
//} //de-comment to check memory leaks

    return 0;
}
