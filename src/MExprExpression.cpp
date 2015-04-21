/*
 * Mathematical Expressions - Expression
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

Expression::~Expression() {
    delete expr;
    ast->deleteTree();
    if (code != NULL)
        delete code;
    delete env;
}

Expression::Expression(const string& expr, Environment* env) throw (Error) {
    this->expr = new string(expr);
    optimizedAST = false;
    code = NULL;

    if (env == NULL) {
        this->env = new Environment();
        StdFunc::initializeEnv(this->env);
    } else {
        this->env = env;
    }

    try {
        ast = MExpr_ParseExpression(this->expr);
    } catch (Error ex) {
        //before, we deallocate the expr and env.
        delete this->env;
        delete this->expr;

        throw; // re-throw
    }
}

string* Expression::getExprTreeString() {
    return ast->getExprTreeString();
}

string* Expression::getExprCodeString() {
    if (code == NULL)
        return NULL;
    return code->getCodeString();
}

void Expression::setVariable(char var, ValueType val) throw (Error) {
    env->setVar(var, val);
}

void Expression::setFunction(std::string funcName, FunctionPntrType funcPntr, unsigned int numArgs) throw (Error) {
    env->setFunction(funcName, funcPntr, numArgs);
}

void Expression::compile() {
    compile(true);
}
void Expression::compile(bool astOptimization) {

    /* check if we need to build the ast */
    if (astOptimization && !optimizedAST) {
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

    if (code == NULL) {
        code = new Code(ast);
    }
}

ValueType Expression::evaluate(bool treeEvaluation) throw (Error) {
    if (code == NULL || treeEvaluation)
        return ast->evaluate(env);
    return code->evaluate(env);
}

ValueType Expression::evaluate() throw (Error) {
    if (code == NULL)
        return ast->evaluate(env);
    return code->evaluate(env);
}

