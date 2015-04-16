/*
 * Mathematical Expressions - Expression Tree
 * Implementation
 *
 * @author Miro Mannino
 *
 * Copyright (c) 2012 Miro Mannino
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <MExprAST.h>
#include <cstddef>
#include <string>
#include <sstream>
using namespace MExpr;
using namespace std;

/*-- ASTNode ---------------------------*/
string* ASTNode::getExprTreeString(){
	stringstream ris (stringstream::in | stringstream::out);
	string tabs ("");
	getExprTreeString_rec(&ris, &tabs, true);
	return new string(ris.str());
}
/*--------------------------------------*/

/*-- Primitive Operations --------------*/

ASTPrimitiveOp::ASTPrimitiveOp(ASTPrimitiveOp::Type type) throw(Error){
	switch(type){
	case ASTPrimitiveOp::ADD:
	case ASTPrimitiveOp::SUB:
	case ASTPrimitiveOp::MUL:
	case ASTPrimitiveOp::DIV:
	case ASTPrimitiveOp::POW:
		numChildren = 2;
		this->type = type;
		break;
	default:
		throw Error(Error::unknownPrimitiveOp);
	}

	children = new ASTNode*[numChildren];
}

ASTPrimitiveOp::~ASTPrimitiveOp(){
	delete children;
}

void ASTPrimitiveOp::getExprTreeString_rec(stringstream* s, string* tabs, bool sameLine){
	switch(type){
	case ASTPrimitiveOp::ADD:
		*s << "[ + ]";
		break;
	case ASTPrimitiveOp::SUB:
		*s << "[ - ]";
		break;
	case ASTPrimitiveOp::MUL:
		*s << "[ * ]";
		break;
	case ASTPrimitiveOp::DIV:
		*s << "[ / ]";
		break;
	case ASTPrimitiveOp::POW:
		*s << "[ ^ ]";
		break;
	}

	/* first child, print on the same line */
	*s << "─";
	string nt (*tabs);
	nt += "  │   ";
	children[0]->getExprTreeString_rec(s, &nt, true);

	/* second child */
	*s << *tabs << "  └───";
	string nt2 (*tabs);
	nt2 += "      ";
	children[1]->getExprTreeString_rec(s, &nt2, false);
}

unsigned int ASTPrimitiveOp::countNodes(){
	unsigned int sum = 1;
	for(int i = 0; i < numChildren; i++) sum += children[i]->countNodes();
	return sum;
}

unsigned int ASTPrimitiveOp::countChildren(){
	return numChildren;
}

ASTNode* ASTPrimitiveOp::getChild(unsigned int c) throw(Error){
	if (c >= numChildren) throw Error(Error::astWrongChild);
	return children[c];
}

void ASTPrimitiveOp::setChild(unsigned int c, ASTNode* node) throw(Error){
	if (c >= numChildren) throw Error(Error::astWrongChild);
	children[c] = node;
}

ValueType ASTPrimitiveOp::evaluate(Environment* env) throw(Error){
	ValueType q;

	switch(type){
	case ASTPrimitiveOp::ADD:
		return children[0]->evaluate(env) + children[1]->evaluate(env);
	case ASTPrimitiveOp::SUB:
		return children[0]->evaluate(env) - children[1]->evaluate(env);
	case ASTPrimitiveOp::MUL:
		return children[0]->evaluate(env) * children[1]->evaluate(env);
	case ASTPrimitiveOp::DIV:
		q = children[1]->evaluate(env);
		if(q == 0) throw Error(Error::divisionByZero);
		return children[0]->evaluate(env) / q;
	case ASTPrimitiveOp::POW:
		return pow(children[0]->evaluate(env), children[1]->evaluate(env));
	/*default:*/
		/* no possible errors, the type was filtered by constructor */
	}

}

void ASTPrimitiveOp::deleteTree(){
	for(int i = 0; i < numChildren; i++) children[i]->deleteTree(); // deallocate subtree
	delete this; //will deallocates the children array
}

Instruction ASTPrimitiveOp::getMExprInstr(){
	Instruction ris;
	switch(type){
	case ASTPrimitiveOp::ADD:
		ris.type = iADD;
		break;
	case ASTPrimitiveOp::SUB:
		ris.type = iSUB;
		break;
	case ASTPrimitiveOp::MUL:
		ris.type = iMUL;
		break;
	case ASTPrimitiveOp::DIV:
		ris.type = iDIV;
		break;
	case ASTPrimitiveOp::POW:
		ris.type = iPOW;
		break;
	/*default:*/
		/* no possible errors, the type was filtered by constructor */
	}
	return ris;
}

/*-------------------------------------------*/

/*-- Functions ------------------------------*/

ASTFunction::ASTFunction(string funcName, unsigned int numArgs){
	this->funcName = funcName;
	numChildren = numArgs;
	children = new ASTNode*[numChildren];
}

ASTFunction::~ASTFunction(){
	delete children;
}

void ASTFunction::getExprTreeString_rec(stringstream* s, string* tabs, bool sameLine){
	*s << "[ " << funcName << " ]";

	/* first child, print on the same line */
	*s << "─";
	string nt (*tabs);
	if(numChildren > 1) nt += "  │  "; else nt += "     ";
	for(int i=0; i<funcName.length(); i++) nt += " ";
	children[0]->getExprTreeString_rec(s, &nt, true);

	/* intermediate children (for operators with more than 3 children) */
	if(numChildren > 2){
		string nt2 (*tabs);
		nt2 += "  |  ";
		for(int j=0; j<funcName.length(); j++) nt2 += " ";

		for(int i=1; i<numChildren-1; i++){
			*s << *tabs << "  ├──";
			for(int j=0; j<funcName.length(); j++) *s << "─";
			children[i]->getExprTreeString_rec(s, &nt2, false);
		}
	}

	/* last child */
	if(numChildren > 1){
		*s << *tabs << "  └──";
		string nt2 (*tabs);
		nt2 += "     ";
		for(int i=0; i<funcName.length(); i++){
			*s << "─";
			nt2 += " ";
		}
		children[numChildren-1]->getExprTreeString_rec(s, &nt2, false);
	}
}

unsigned int ASTFunction::countNodes(){
	unsigned int sum = 1;
	for(int i = 0; i < numChildren; i++) sum += children[i]->countNodes();
	return sum;
}

unsigned int ASTFunction::countChildren(){
	return numChildren;
}

ASTNode* ASTFunction::getChild(unsigned int c) throw(Error){
	if (c >= numChildren) throw Error(Error::astWrongChild);
	return children[c];
}

void ASTFunction::setChild(unsigned int c, ASTNode* node) throw(Error){
	if (c >= numChildren) throw Error(Error::astWrongChild);
	children[c] = node;
}

ValueType ASTFunction::evaluate(Environment* env) throw(Error){
	FunctionType fn = env->getFunction(funcName);
	if(fn.fnPntr == NULL) throw Error(Error::functionNotDefined);
	if(fn.numArgs != numChildren) throw Error(Error::illegalArgsNum);
	ValueType vals[numChildren];

	/* in the following way the function has the args in the inverse sequence,
	   args.stack[args.stp-1] is the last args, args.stack[args.stp-2] is the second-last, and so on. */
	for(int i=0; i<numChildren; i++) vals[i] = children[i]->evaluate(env);

	StackType stack;
	stack.size = numChildren;
	stack.stack = vals;
	stack.stp = numChildren;
	(fn.fnPntr)(&stack);
	return stack.stack[stack.stp-1];
}

void ASTFunction::deleteTree(){
	for(int i = 0; i < numChildren; i++) children[i]->deleteTree(); // deallocate subtree
	delete this; //will deallocates the children array
}

Instruction ASTFunction::getMExprInstr(){
	Instruction ris;
	ris.type = iFUN;
	ris.arg.funName = &funcName;
	return ris;
}

/*-------------------------------------------*/

/*-- Value ----------------------------------*/

ASTValue::ASTValue(ValueType value){
	this->value = value;
}

ASTValue::~ASTValue(){

}

void ASTValue::getExprTreeString_rec(stringstream* s, string* tabs, bool sameLine){
	*s << "[ " << value << " ]" << endl;
}

unsigned int ASTValue::countNodes(){
	return 1;
}

unsigned int ASTValue::countChildren(){
	return 0;
}

ASTNode* ASTValue::getChild(unsigned int c) throw(Error){
	throw Error(Error::astWrongChild);
}

void ASTValue::setChild(unsigned int c, ASTNode* node) throw(Error){
	throw Error(Error::astWrongChild);
}

void ASTValue::deleteTree(){
	delete this;
}

ValueType ASTValue::evaluate(Environment* env) throw(Error){
	return value;
}

Instruction ASTValue::getMExprInstr(){
	Instruction ris;
	ris.type = iVAL;
	ris.arg.value = value;
	return ris;
}

/*-------------------------------------------*/

/*-- Variable -------------------------------*/

ASTVariable::ASTVariable(char var){
	this->var = var;
}

ASTVariable::~ASTVariable(){

}

void ASTVariable::getExprTreeString_rec(stringstream* s, string* tabs, bool sameLine){
	*s << "[ " << var << " ]" << endl;
}

unsigned int ASTVariable::countNodes(){
	return 1;
}

unsigned int ASTVariable::countChildren(){
	return 0;
}

ASTNode* ASTVariable::getChild(unsigned int c) throw(Error){
	throw Error(Error::astWrongChild);
}

void ASTVariable::setChild(unsigned int c, ASTNode* node) throw(Error){
	throw Error(Error::astWrongChild);
}

void ASTVariable::deleteTree(){
	delete this;
}

ValueType ASTVariable::evaluate(Environment* env) throw(Error){
	if (!env->isSetVar(var)) throw Error(Error::variableNotDefined);
	return env->getVar(var);
}

Instruction ASTVariable::getMExprInstr(){
	Instruction ris;
	ris.type = iVAR;
	ris.arg.variable = var;
	return ris;
}

/*-------------------------------------------*/
