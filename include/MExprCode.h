/*
 * Mathematical Expressions - Coded Expression
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

#ifndef __MExprExprCode_H__
#define __MExprExprCode_H__

#include <MExprDefinitions.h>
#include <MExprInstruction.h>
#include <MExprEnvironment.h>
#include <MExprAST.h>

#ifdef __cplusplus
	#include <string>
	#include <cstddef>

namespace MExpr {

	/**
	 * Code is a class that represents a mathematical expression with an array of simple instructions.
	 *
	 * If you have an expression that contains variables or functions, and you must evaluate this expression a lot of times,
	 * you can create this Code. This is an array of simple mathematical instructions (bytecode). This representation
	 * is more efficient to evaluate because doesn't use recursive function. For example, with an abstract syntax tree,
	 * 10'000'000 evaluation of an expression with ~50 elements take 3sec, with the compiled expression, it takes only 2sec.
	 *
	 */
	class Code {
		Instruction* code; /* array of instructions */
		size_t codeSize; /* size of the array */
		StackType stack; /* array that memorize the stack used to evaluate the code */

	public:

		/**
		 * Creates the Code.
		 * It counts the number of nodes of the abstract syntax tree, then allocates an array of instructions,
		 * this array has the same length of the nodes in the abstract syntax tree.
		 * Then, with a recursive navigation of the tree, it calculate the stack size and copy all the instruction in the
		 * code array.
		 * */
		Code(ASTNode* exprAST);

		/**
		 * Destroyer
		 * */
		~Code();

		/**
		 * Evaluate the code.
		 * This evaluation is faster than the evaluation used in the abstract syntax tree. In fact this evaluation
		 * is not recursive, doesn't call virtual methods and so on. It was designed to be fast.
		 **/
		ValueType evaluate(Environment* env) throw(Error);

		/**
		 * Returns a string representation of the code.
		 *
		 * Note: you must deallocate the string
		 */
		std::string* getCodeString();

	private:

		/**
		 * This method is used by the constructor to navigate the abstract syntax tree (populating the bytecode and
		 * calculating the stack size)
		 * */
		void compile(ASTNode* exprAST, int* i, int* stackP);
	};

} //end of namespace MExpr

#else

	//typedef void* MExprCode;

#endif //of #ifdef __cplusplus

#ifdef __cplusplus

	extern "C" {

#endif
	//TODO: C functions


#ifdef __cplusplus

	}

#endif

#endif
