/*
 * Mathematical Expressions - Coded Expression
 * Implementation
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#include <stdio.h>
#include <MExprCode.h>
#include <string>
#include <sstream>
using namespace MExpr;
using namespace std;

extern "C" {
	//TODO: C functions

}

Code::Code(ASTNode* exprAST){
	int i = 0; //shared integer for all functions (called recursively)
	int stackP = 0; //shared integer (represent the current stack size (not the max))

	codeSize = (size_t)exprAST->countNodes();
	code = new Instruction[codeSize];
	stack.size = 0;
	compile(exprAST, &i, &stackP);
	stack.stack = new ValueType[stack.size];
}

/** code array population and stack size calculation */
void Code::compile(ASTNode* exprAST, int* i, int* stackP){
	unsigned int chsNum = exprAST->countChildren();

	for(int j = 0; j < chsNum; j++) compile(exprAST->getChild(j), i, stackP);
	code[*i] = exprAST->getMExprInstr(); //instruction copy on array
	(*stackP) = (*stackP) + 1 - chsNum; //evalutation returns 1 result but needs chsNum arguments
	if(*stackP > stack.size) stack.size = *stackP; //stackSize must be the max of stackP
	(*i)++;
}

string* Code::getCodeString(){
	stringstream s (stringstream::in | stringstream::out);

	for(int i = 0; i < codeSize; i++){
		switch(code[i].type){
		case iADD:
			s << "ADD" << endl;
			break;
		case iSUB:
			s << "SUB" << endl;
			break;
		case iMUL:
			s << "MUL" << endl;
			break;
		case iDIV:
			s << "DIV" << endl;
			break;
		case iPOW:
			s << "POW" << endl;
			break;
		case iVAL:
			s << "VAL: " << code[i].arg.value << endl;
			break;
		case iVAR:
			s << "VAR: " << code[i].arg.variable << endl;
			break;
		case iFUN:
			s << "FUN: " << *code[i].arg.funName << endl;
		}
	}

	return new string(s.str());
}


ValueType Code::evaluate(Environment* env) throw(Error){
	FunctionType fn;

	stack.stp = 0;
	for(int i = 0; i < codeSize; i++){

		/* Switch */
		switch(code[i].type){
		case iVAL:
			stack.stack[stack.stp] = code[i].arg.value;
			stack.stp++;
			break;
		case iVAR:
			if (!env->isSetVar(code[i].arg.variable)) throw Error(Error::variableNotDefined);
			stack.stack[stack.stp] = env->getVar(code[i].arg.variable);
			stack.stp++;
			break;
		case iADD:
			stack.stack[stack.stp-2] = stack.stack[stack.stp-2] + stack.stack[stack.stp-1];
			stack.stp--;
			break;
		case iMUL:
			stack.stack[stack.stp-2] = stack.stack[stack.stp-2] * stack.stack[stack.stp-1];
			stack.stp--;
			break;
		case iSUB:
			stack.stack[stack.stp-2] = stack.stack[stack.stp-2] - stack.stack[stack.stp-1];
			stack.stp--;
			break;
		case iDIV:
			if(stack.stack[stack.stp-1] == 0) throw Error(Error::divisionByZero);
			stack.stack[stack.stp-2] = stack.stack[stack.stp-2] / stack.stack[stack.stp-1];
			stack.stp--;
			break;
		case iPOW:
			stack.stack[stack.stp-2] = pow(stack.stack[stack.stp-2], stack.stack[stack.stp-1]);
			stack.stp--;
			break;
		case iFUN:
			fn = env->getFunction(*code[i].arg.funName);
			if(fn.fnPntr == NULL) throw Error(Error::functionNotDefined);
			(fn.fnPntr)(&stack);
			break;
		}

	}
	return stack.stack[0];
}

Code::~Code(){
	delete code;
	delete stack.stack;
}
