/*
 * Mathematical Expressions - Expression
 * Headers
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#ifndef __MExprExpression_H__
#define __MExprExpression_H__

#include <MExprDefinitions.h>
#include <MExprEnvironment.h>
#include <MExprError.h>
#include <MExprAST.h>
#include <MExprCode.h>

extern MExpr::ASTNode* MExpr_ParseExpression(const std::string* expr) throw(MExpr::Error);

#ifdef __cplusplus
	#include <cstddef>
	#include <stdexcept>
	#include <string>

namespace MExpr {

	/**
	 * Expression is a class that represents a mathematical expression.
	 *
	 * The constructor needs the mathematical expression represented by a string, or an abstract syntax tree.
	 * In the first case, it calls the parser that builds the abstract syntax tree of the expression.
	 * In the second case, the constructor only copy the abstract syntax tree.
	 *
	 * If you have an expression that contains variables or functions, and you must evaluate this expression a lot of times,
	 * you can compile the expression with the 'compile' method. This method creates a Code class that creates an array
	 * of simple mathematical instructions (bytecode). This representation is more efficient to evaluate because
	 * doesn't use recursive function. For example, with an abstract syntax tree, 10'000'000 evaluation of an expression
	 * with ~50 elements take 3sec, with the compiled expression, it takes only 2sec.
	 *
	 * The evaluate method calculates the result recursively navigating the syntax abstract tree, if you have compiled the
	 * expression, it use a faster non-recursive function that execute the bytecode.
	 *
	 */
	class Expression {
	private:
		std::string* expr; /* expression string */
		ASTNode* ast; /* expression abstract syntax tree */
		bool optimizedAST; /* specify if the abstract syntax tree is optimized or not */
		Code* code; /* compiled expression */
		Environment* env; /* environment to evaluate the expression */


	public:
		/**
		 * It creates a new MExprExpression. Parses the string and create an abstract syntax tree
		 * that is the representation of the mathematical expression.
		 *
		 * @param expr mathematical expression string
		 * @param env  it doesn't create a new environment, but uses the given
		 * */
		//Expression(const std::string& expr) throw(Error);
		Expression(const std::string& expr, Environment* env = NULL) throw(Error);

		/**
		 * It creates a new Expression analyzing the given abstract syntax tree. The abstract syntax tree is copied
		 * into this class.
		 *
		 * @param ast abstract syntax tree
		 * */
		/*TODO:
		 *  Expression(ASTNode* ast) throw(Error);
		 */

		/**
		 * Destroyer
		 * */
		~Expression();

		/**
		 * Return a string representation of the tree.
		 *
		 * Important: you must deallocate this string.
		 *
		 * @return a new string
		 * */
		std::string* getExprTreeString();

		/**
		 * Return a string representation of the compiled expression.
		 *
		 * Important: you must deallocate this string.
		 *
		 * @return a new string
		 * */
		std::string* getExprCodeString();

		/**
		 *
		 * */
		void setVariable(char var, ValueType val) throw(Error);

		/**
		 *
		 * */
		void setFunction(std::string funcName, FunctionPntrType funcPntr, unsigned int numArgs) throw(Error);

		/**
		 * Compile the abstract syntax tree. It creates a new Code class, this navigates the entire abstract syntax tree and
		 * transforms all nodes into bytecode instructions. For more information see the Expression class documentation.
		 *
		 * @param astOptimization if true the compile function create a new optimized abstract syntax tree, then it use this
		 * new tree to compile the expression. After the compilation, the older tree will be replaced with the newer optimized
		 * tree.
		 *
		 * */
		void compile(bool astOptimization);
		void compile();

		/**
		 * Evaluate the expression
		 *
		 * If the expression is not compiled, it performs the evaluations using a recursive
		 * function that navigate the abstract syntax tree.
		 *
		 * If the expression is compiled, it performs the evaluations using the Code.
		 *
		 * @param treeEvaluation force the evaluation on abstract syntax tree
		 *
		 * @return the result
		 * */
		ValueType evaluate() throw(Error);
		ValueType evaluate(bool treeEvaluation) throw(Error);

		static ASTNode* createAST(const char* expr) throw(Error);
	};

} //end of namespace MExpr

#else

	//typedef void* MExprExpression;

#endif //of #ifdef __cplusplus

#ifdef __cplusplus

	extern "C" {

#endif
		//TODO: C functions
		/**
		 * It creates a new MExpr. Parses the string and create an abstract syntax tree
		 * that is the representation of the mathematical expression.
		 *
		 * @param expr mathematical expression string
		 * */
		//MExpr* mexpr_MExpr_new(const char* expr);

		/**
		 * Calls the MExpr destroyer
		 */
		//void mexpr_MExpr_dispose(MExpr* e);

		/**
		 * Evaluate the expression using a recursive function that navigate the abstract syntax tree.
		 *
		 * @return the result
		 * */
		//ValueType mexpr_MExpr_evaluate(MExpr* e);

#ifdef __cplusplus

	}

#endif

#endif
