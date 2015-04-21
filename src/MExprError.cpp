/*
 * Mathematical Expressions Error Classes
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

#include <MExprError.h>
using namespace std;
using namespace MExpr;

extern "C" {
//TODO: C functions
}

Error::Error(Error::Type t) {
    this->t = t;
}

Error::Type Error::getType() {
    return t;
}

const char* Error::what() {
    switch (t) {
    case Error::syntaxError:
        return "syntax error";
    case Error::divisionByZero:
        return "division by zero";
    case Error::lexError:
        return "can't inizialize lexer";
    case Error::astWrongChild:
        return "wrong access to the abstract syntax tree children";
    case Error::variableNotDefined:
        return "variable not defined";
    case Error::illegalVariableName:
        return "illegal variable name, it must be a char in [a-zA-Z]";
    case Error::unknownPrimitiveOp:
        return "primitive op not defined";
    case Error::illegalFunctionName:
        return "illegal function name, it must start with the '_' char";
    case Error::illegalArgsNum:
        return "wrong number of arguments to call this function";
    case Error::functionNotDefined:
        return "function not defined";
    default:
        return "undefined error";
    }
}
