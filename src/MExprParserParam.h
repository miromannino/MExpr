/*
 * Mathematical Expressions Parser Params
 * Definitions of the parameters for the reentrant functions of flex (yylex) and bison (yyparse)
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#ifndef __MExprParserParam_H__
#define __MExprParserParam_H__

#ifndef YY_NO_UNISTD_H
	#define YY_NO_UNISTD_H 1
#endif

#include <MExprTypeParser.h>
#include <MExprLexer.h>
#include <MExprAST.h>

#include <list>

/** structure given as argument to the reentrant 'yyparse' function */
typedef struct MExpr_StructParserParam{
	yyscan_t scanner;
	MExpr::ASTNode* expression;
	std::list<MExpr::ASTNode*>* errRecPointerPool; /* Pointer Pool to recover errors */
	std::list<MExpr::ASTNode*>* funcArgsAccumulator; /* function arguments accumulator */
	bool errors;
} MExpr_ParserParam;

/**
 * the parameter name (of the reentrant 'yyparse' function)
 * data is a pointer to a 'MExprParserParam' structure
 */
#define YYPARSE_PARAM data

/** the argument for the 'yylex' function */
#define YYLEX_PARAM ((MExpr_ParserParam*)data)->scanner

#endif
