/*
 * Mathematical Expressions Parser Params
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
