/*
 * Mathematical Expressions Parser Params
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#ifndef __MExprTypeParser_H__
#define __MExprTypeParser_H__

#include <string>
#include <MExprInstruction.h>
#include <MExprAST.h>

/** structure used by flex and bison */
typedef union MExpr_UnionTypeParser{
	MExpr::ASTNode* exprNode;
	MExpr::ValueType value;
	char var;
	std::string* func;
	unsigned int numArgs;
} MExpr_TypeParser;

/** define the type for flex and bison */
#define YYSTYPE MExpr_TypeParser

#endif
