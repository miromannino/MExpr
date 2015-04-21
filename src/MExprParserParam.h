/*
 * Mathematical Expressions Parser Params
 * Definitions of the parameters for the reentrant functions of flex (yylex) and bison (yyparse)
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
typedef struct MExpr_StructParserParam {
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
