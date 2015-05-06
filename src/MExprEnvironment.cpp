/*
 * Mathematical Expressions - Environment
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

#include <map>
#include <sstream>
#include <MExprEnvironment.h>
using namespace MExpr;
using namespace std;

Environment::~Environment() {
    variables->clear();
    functions->clear();
    delete variables;
    delete functions;
}

Environment::Environment() {
    variables = new map<char, ValueType>;
    functions = new map<string, FunctionType>;
}

ValueType Environment::getVar(char var) {
    return (*variables)[var];
}

void Environment::setVar(char var, ValueType val) throw (Error) {
    //check if not is [a-zA-Z]
    if (var < 'A' || var > 'z' || ('Z' < var && var < 'a'))
        throw Error(Error::illegalVariableName);

    (*variables)[var] = val;
}

bool Environment::isSetVar(char var) {
    return variables->find(var) != variables->end();
}

FunctionType Environment::getFunction(string funcName) {
    map<string, FunctionType>::iterator it;
    if ((it = functions->find(funcName)) != functions->end()) {
        return it->second;
    } else {
        return (FunctionType ) { NULL, 0 } ;
            }
        }

        void Environment::setFunction(string funcName, FunctionPntrType funcPntr, unsigned int numArgs) throw (Error) {
            //check function name
            if (funcName[0] != '_')
                throw Error(Error::illegalFunctionName);

            FunctionType str;
            str.fnPntr = funcPntr;
            str.numArgs = numArgs;
            ostringstream ss;
            ss << funcName << "_" << numArgs;
            (*functions)[ss.str()] = str; //save the function name with the number of parameters
        }

        bool Environment::isSetFunction(string funcName) {
            return functions->find(funcName) != functions->end();
        }
