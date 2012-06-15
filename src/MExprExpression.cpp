/*
 * Mathematical Expressions - Expression
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#include <MExprExpression.h>
#include <MExprInstruction.h>
#include <MExprStdFunc.h>
#include <iostream>
using namespace std;
using namespace MExpr;

extern "C" {

	//TODO: C functions
	/*MExpr* mexpr_MExpr_new(const char* expr){
		return new MExpr(expr);
	}
	void mexpr_MExpr_dispose(MExpr* e){
		delete e;
	}
	ValueType mexpr_MExpr_evaluate(MExpr* e){
		return e->evaluate();
	}*/

}

Expression::~Expression(){
	delete expr;
	ast->deleteTree();
	if(code != NULL) delete code;
	delete env;
}

Expression::Expression(const string& expr, Environment* env) throw(Error){
	this->expr = new string(expr);
	optimizedAST = false;
	code = NULL;

	if (env == NULL){
		this->env = new Environment();
		StdFunc::initializeEnv(this->env);
	}else{
		this->env = env;
	}

	try{
		ast = MExpr_ParseExpression(this->expr);
	}catch(Error ex){
		//before, we deallocate the expr and env.
		delete this->env;
		delete this->expr;

		throw; // re-throw
	}
}

string* Expression::getExprTreeString(){
	return ast->getExprTreeString();
}

string* Expression::getExprCodeString(){
	if(code == NULL) return NULL;
	return code->getCodeString();
}

void Expression::setVariable(char var, ValueType val) throw(Error){
	env->setVar(var, val);
}

void Expression::setFunction(std::string funcName, FunctionPntrType funcPntr, unsigned int numArgs) throw(Error){
	env->setFunction(funcName, funcPntr, numArgs);
}

void Expression::compile(){
	compile(true);
}
void Expression::compile(bool astOptimization){

	/* check if we need to build the ast */
	if(astOptimization && !optimizedAST){
		//TODO:

		//build optimized ast from the current ast
		//...

		//substitute with the new ast
		//...

		//we must to destroy the non-optimized code
		/*
		if(code != NULL){
			delete code;
			code = NULL;
		}
		*/
	}

	if(code == NULL){
		code = new Code(ast);
	}
}

ValueType Expression::evaluate(bool treeEvaluation) throw(Error){
	if(code == NULL || treeEvaluation) return ast->evaluate(env);
	return code->evaluate(env);
}

ValueType Expression::evaluate() throw(Error){
	if(code == NULL) return ast->evaluate(env);
	return code->evaluate(env);
}


