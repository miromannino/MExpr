/*
 * Mathematical Expressions - Abstract Syntax Tree
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

#ifndef __MExprAST_H__
#define __MExprAST_H__

#include <math.h>
#include <MExprDefinitions.h>
#include <MExprError.h>
#include <MExprEnvironment.h>
#include <MExprInstruction.h>

#ifdef __cplusplus

namespace MExpr {

	/*-- Node Abstract class ---------------------*/
	/**
	 * An abstract class that represents a generic node in the abstract syntax tree.
	 * With the countChildren and getChild methods you can navigate the tree.
	 */
	class ASTNode {
	public:
		virtual ~ASTNode() {}

		/**
		 * get the tree representation in a string
		 *
		 */
		std::string* getExprTreeString();

		/**
		 * Counts the nodes of the tree/subtree that have this node as root
		 *
		 * @return the nodes count (greater or equal to zero)
		 */
		virtual unsigned int countNodes() = 0;

		/**
		 * Counts the number of children.
		 * For example the '+' has two children but the 'log' has only one child.
		 *
		 * @return the children count (greater or equal to zero)
		 */
		virtual unsigned int countChildren() = 0;

		/**
		 * Get a child.
		 * For example the '+' has two children and the getChild(0) returns the first child, the getChild(1) returns the second.
		 *
		 * @param c the number of the child (c >= 0).
		 *
		 * @return the children or NULL if it doesn't exists
		 */
		virtual ASTNode* getChild(unsigned int c) throw(Error) = 0;

		/**
		 * Set a child.
		 *
		 * @param c the number of the child (c >= 0).
		 * @param node the value of the child.
		 *
		 */
		virtual void setChild(unsigned int c, ASTNode* node) throw(Error) = 0;

		/**
		 * Returns the result of the tree/subtree that have this node as root
		 *
		 * @param env the Environment class to evalutate the expression (for variables and functions)
		 * @return the result
		 */
		virtual ValueType evaluate(Environment* env) throw(Error) = 0;

		/**
		 * Deallocate the tree/subtree that have this node as root. This function deallocate this node too.
		 */
		virtual void deleteTree() = 0;

		/**
		 * Returns he Instruction that represent this node. This is used to build the Code.
		 */
		virtual MExpr::Instruction getMExprInstr() = 0;


		virtual void getExprTreeString_rec(std::stringstream* ris, std::string* tabs, bool sameLine) = 0;

	};
	/*-------------------------------------------*/

	/*-- Primitive Operations -------------------*/
	/**
	 * A class that represents a generic primitive operation, for examplel +, -, *, ...
	 */
	class ASTPrimitiveOp: public ASTNode {
	public:
			enum Type {
				ADD, // '+'
				SUB, // '-'
				MUL, // '*'
				DIV, // '/'
				POW  // '^'
			};
	protected:
			ASTNode** children; //array of numChildren elements
			unsigned int numChildren; //depends on the PrimitiveOp::Type
			Type type;
	public:
		ASTPrimitiveOp(ASTPrimitiveOp::Type type) throw(Error);
		~ASTPrimitiveOp();
		unsigned int countNodes();
		unsigned int countChildren();
		ASTNode* getChild(unsigned int c) throw(Error);
		void setChild(unsigned int c, ASTNode* node) throw(Error);
		ValueType evaluate(Environment* env) throw(Error);
		void deleteTree();
		MExpr::Instruction getMExprInstr();
	protected:
		void getExprTreeString_rec(std::stringstream* ris, std::string* tabs, bool sameLine);
	};
	/*-------------------------------------------*/

	/*-- Function -------------------------------*/
	/* A class that represents a call to a function.
	 * */
	class ASTFunction: public ASTNode {
	private:
		std::string funcName;
		ASTNode** children; //array of numChildren elements
		unsigned int numChildren;

	public:
		ASTFunction(std::string funcName, unsigned int numArgs);
		~ASTFunction();
		unsigned int countNodes();
		unsigned int countChildren();
		ASTNode* getChild(unsigned int c) throw(Error);
		void setChild(unsigned int c, ASTNode* node) throw(Error);
		ValueType evaluate(Environment* env) throw(Error);
		void deleteTree();
		MExpr::Instruction getMExprInstr();
	protected:
		void getExprTreeString_rec(std::stringstream* ris, std::string* tabs, bool sameLine);
	};
	/*-------------------------------------------*/

	/*-- Value ----------------------------------*/
	/* A class that represents a value.
	 * The countNodes returns always 1, countChildren returns always 0 and getChild returns always NULL.
	 * setChild doesn't set anything because this node haven't children.
	 * */
	class ASTValue: public ASTNode {
	private:
		ValueType value;
	public:
		ASTValue(ValueType value);
		~ASTValue();
		unsigned int countNodes();
		unsigned int countChildren();
		ASTNode* getChild(unsigned int c) throw(Error);
		void setChild(unsigned int c, ASTNode* node) throw(Error);
		ValueType evaluate(Environment* env) throw(Error);
		void deleteTree();
		MExpr::Instruction getMExprInstr();
	protected:
		void getExprTreeString_rec(std::stringstream* ris, std::string* tabs, bool sameLine);
	};
	/*-------------------------------------------*/

	/*-- Variable -------------------------------*/
		/* A class that represents a variable.
		 * The countNodes returns always 1, countChildren returns always 0 and getChild returns always NULL.
		 * setChild doesn't set anything because this node haven't children.
		 * */
		class ASTVariable: public ASTNode {
		private:
			char var;
		public:
			ASTVariable(char var);
			~ASTVariable();
			unsigned int countNodes();
			unsigned int countChildren();
			ASTNode* getChild(unsigned int c) throw(Error);
			void setChild(unsigned int c, ASTNode* node) throw(Error);
			ValueType evaluate(Environment* env) throw(Error);
			void deleteTree();
			MExpr::Instruction getMExprInstr();
		protected:
			void getExprTreeString_rec(std::stringstream* ris, std::string* tabs, bool sameLine);
		};
		/*-------------------------------------------*/

} //end of namespace MExpr

#endif //of #ifdef __cplusplus

#endif
