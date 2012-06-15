/*
 * Mathematical Expressions - Environment
 * Headers
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#ifndef __MExprEnvironment_H__
#define __MExprEnvironment_H__

#include <MExprDefinitions.h>
#include <MExprError.h>

#ifdef __cplusplus
	#include <cstddef>
	#include <stdexcept>
	#include <map>
	#include <string>

namespace MExpr {

	/**
	 * TODO
	 *
	 */
	class Environment {
	private:
		std::map<char, ValueType>* variables;
		std::map<std::string, FunctionType>* functions;

	public:
		/**
		 *
		 * */
		Environment();

		/**
		 * Destroyer
		 * */
		~Environment();

		/**
		 * Returns the value of a variable. If it doesn't exist, it creates a new variables with the 'var' name and
		 * assign it the 0 value. If you want to be sure that the variable exists you must use the isSetVar method.
		 * */
		ValueType getVar(char var);

		/**
		 * Sets the value of a variable. If the variable doesn't exist, it creates it and assign the given value.
		 * if the variable exists the value will be overwritten
		 * */
		void setVar(char var, ValueType val) throw(Error);

		/**
		 * checks if a variable exists
		 * */
		bool isSetVar(char var);

		/**
		 * Returns the value of a variable. If it doesn't exist, it returns {NULL,0}
		 * */
		FunctionType getFunction(std::string funcName);

		/**
		 * Sets the value of a function giving its pointer
		 * if the function exists it will be overwritten
		 * */
		void setFunction(std::string funcName, FunctionPntrType funcPntr, unsigned int numArgs) throw(Error);

		/**
		 * checks if a function exists
		 * */
		bool isSetFunction(std::string funcName);

	};

} //end of namespace MExpr

#endif //of #ifdef __cplusplus

#ifdef __cplusplus

	extern "C" {

#endif

	//TODO: C functions
//C definitions

#ifdef __cplusplus

	}

#endif

#endif
