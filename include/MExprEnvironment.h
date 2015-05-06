/*
 * Mathematical Expressions - Environment
 * Headers
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

#ifndef __MExprEnvironment_H__
#define __MExprEnvironment_H__

#include <cstddef>
#include <stdexcept>
#include <map>
#include <string>

#include <MExprDefinitions.h>
#include <MExprError.h>

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


#endif
