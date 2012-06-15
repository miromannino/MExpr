/*
 * Mathematical Expressions - Coded Expression
 * Headers
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
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
