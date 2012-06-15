/*
 * Mathematical Expressions Error Classes
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#include <MExprError.h>
using namespace std;
using namespace MExpr;

extern "C" {
	//TODO: C functions
}

Error::Error(Error::Type t){
	this->t = t;
}

Error::Type Error::getType(){
	return t;
}

const char* Error::what(){
	switch(t){
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
