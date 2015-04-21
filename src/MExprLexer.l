/*
 * Mathematical Expressions Lexer
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

%{

#include <MExprTypeParser.h>
#include <MExprParser.h>
#include <math.h>
#include <string>

%}

%option bison-bridge reentrant never-interactive noyywrap nounistd

VAL         [0-9]+(\.[0-9]+)?
VAR         [a-zA-Z]
FUNC        \_[a-z]([a-zA-Z0-9]*)
SKIP        [ \r\n\t]*

%%

{SKIP}      { }
"("         {return tLPAR;}
")"         {return tRPAR;}
"+"         {return tADD;}
"-"         {return tSUB;}
"*"         {return tMUL;}
"/"         {return tDIV;}
"^"         {return tPOW;}
","         {return tCOMMA;}
{VAL}       { sscanf(yytext,"%lf",&yylval->value); return tVAL; }
{VAR}       { yylval->var = yytext[0]; return tVAR; }
{FUNC}      { yylval->func = new std::string(yytext); return tFUNC; }
.           { }

%%