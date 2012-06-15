/*
 * Mathematical Expressions - Environment
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#include <MExprEnvironment.h>
#include <map>
#include <sstream>
using namespace std;
using namespace MExpr;

extern "C" {

//TODO: C functions

}

Environment::~Environment(){
	variables->clear();
	functions->clear();
	delete variables;
	delete functions;
}

Environment::Environment(){
	variables = new map<char, ValueType>;
	functions = new map<string, FunctionType>; 
}

ValueType Environment::getVar(char var){
	return (*variables)[var];
}

void Environment::setVar(char var, ValueType val) throw(Error){
	//check if not is [a-zA-Z]
	if(var < 'A' || var > 'z' || ('Z' < var && var < 'a')) throw Error(Error::illegalVariableName);

	(*variables)[var] = val;
}

bool Environment::isSetVar(char var){
	return variables->find(var) != variables->end();
}

FunctionType Environment::getFunction(string funcName){
	map<string, FunctionType>::iterator it;
	if((it = functions->find(funcName)) != functions->end()){
		return it->second;
	}else{
		return (FunctionType){NULL,0};
	}
}

void Environment::setFunction(string funcName, FunctionPntrType funcPntr, unsigned int numArgs) throw(Error){
	//check function name
	if(funcName[0] != '_') throw Error(Error::illegalFunctionName);

	FunctionType str;
	str.fnPntr = funcPntr;
	str.numArgs = numArgs;
	ostringstream ss;
	ss << funcName << "_" << numArgs;
	(*functions)[ss.str()] = str; //save the function name with the number of parameters
}

bool Environment::isSetFunction(string funcName){
	return functions->find(funcName) != functions->end();
}
