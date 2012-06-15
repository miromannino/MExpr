/*
 * Mathematical Expressions Lexer
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

%{

	#include <MExprTypeParser.h>
	#include <MExprParser.h>
	#include <math.h>
	#include <string>

%}

%option bison-bridge reentrant never-interactive noyywrap  nounistd

VAL			[0-9]+(\.[0-9]+)?
VAR			[a-zA-Z]
FUNC		\_[a-z]([a-zA-Z0-9]*)
SKIP		[ \r\n\t]*

%%

{SKIP}          { }
"("				{return tLPAR;}
")"				{return tRPAR;}
"+"				{return tADD;}
"-"				{return tSUB;}
"*"				{return tMUL;}
"/"				{return tDIV;}
"^"				{return tPOW;}
","				{return tCOMMA;}
{VAL}			{ sscanf(yytext,"%lf",&yylval->value); return tVAL; }
{VAR}			{ yylval->var = yytext[0]; return tVAR; }
{FUNC}			{ yylval->func = new std::string(yytext); return tFUNC; }
.				{ }

%%