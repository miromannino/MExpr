/*
 * Mathematical Expressions Parser
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

%{
	
	#include <MExprParserParam.h>
	#include <MExprTypeParser.h>
	#include <string>
	#include <sstream>
	using namespace MExpr;
	using namespace std;

	int MExpr_parse(void *param);
	
	int MExpr_error(const char *msg){ }
	
	ASTNode* MExpr_ParseExpression(const string* expr) throw(Error){
		const char* cexpr;
		MExpr_ParserParam p;
	    YY_BUFFER_STATE state;
		int ret = 0;
		
		cexpr = expr->c_str();
		  
	    ret = MExpr_lex_init(&p.scanner);
	    if(ret){ // error inizialize yylex
	    	throw Error(Error::lexError);
	    }

	    p.funcArgsAccumulator = new list<ASTNode*>;
	    p.errRecPointerPool = new list<ASTNode*>;
	    p.expression = NULL;
	    p.errors = false;

		state = MExpr__scan_string(cexpr, p.scanner);

		ret = MExpr_parse(&p);
	    if (ret || p.errors){ // error parsing
	    	/* Error Recovering to avoid memory leaks */
	    	for (list<ASTNode*>::iterator it = p.errRecPointerPool->begin(); it != p.errRecPointerPool->end(); it++){
				delete *it; //delete the ASTNode
				p.errRecPointerPool->erase(it); //delete the list element, it not call the ASTNode deconstructor
			}
	    	MExpr__delete_buffer(state, p.scanner);
	    	MExpr_lex_destroy(p.scanner);
	    	p.funcArgsAccumulator->clear();
	    	delete p.errRecPointerPool;
	    	delete p.funcArgsAccumulator;	
	    	throw Error(Error::syntaxError);
	    }

	    MExpr__delete_buffer(state, p.scanner);
	    MExpr_lex_destroy(p.scanner);
	    p.errRecPointerPool->clear(); //delete only the list, not the ASTNodes (they are pointers)
	    p.funcArgsAccumulator->clear(); //delete only the list, not the ASTNodes (they are pointers)
	    delete p.errRecPointerPool;
	    delete p.funcArgsAccumulator;

	    return p.expression;
	}

%}

%pure-parser

%type <numArgs> funcArgs
%type <exprNode> powNum
%type <exprNode> power
%type <exprNode> atomicExpr
%type <exprNode> expr

%left tADD
%left tSUB
%left tPREADD
%left tPRESUB
%left tMUL 
%left tDIV
%left tCOMMA
%right tPOW

%token tLPAR
%token tRPAR
%token <value> tVAL
%token <var> tVAR
%token <func> tFUNC

%%

input:
	expr				{ 
							((MExpr_ParserParam*)data)->expression = $1; 
						}
;

funcArgs:

	expr					{
								$$ = 1;
								((MExpr_ParserParam*)data)->funcArgsAccumulator->push_back($1);
							}
|	expr tCOMMA funcArgs	{
								$$ = 1 + $3;
								((MExpr_ParserParam*)data)->funcArgsAccumulator->push_back($1);
							}
;	
	
powNum:

	tLPAR expr tRPAR	{ 
							$$ = $2; 
						}
	
|	tSUB tLPAR expr tRPAR	{ 
								$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::MUL);
								MExpr::ASTNode* usubValue = new MExpr::ASTValue(-1);
								$$->setChild(0, usubValue);
								$$->setChild(1, $3);
								((MExpr_ParserParam*)data)->errRecPointerPool->push_back(usubValue);
								((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
							}	

|	tVAL				{ 
							$$ = new MExpr::ASTValue($1);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}

|	tVAR				{	
  							$$ = new MExpr::ASTVariable($1);
  							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
  						}

|	tSUB tVAL			{ 
							$$ = new MExpr::ASTValue(-$2);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}

|	tADD tVAL			{ 
							$$ = new MExpr::ASTValue($2);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}

|	tSUB tVAR			{	
							$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::MUL);
							MExpr::ASTNode* usubValue = new MExpr::ASTValue(-1);
							MExpr::ASTNode* var = new MExpr::ASTVariable($2);
							$$->setChild(0, usubValue);
							$$->setChild(1, var);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back(usubValue);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back(var);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}
|	tADD tVAR			{	
							$$ = new MExpr::ASTVariable($2);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}
;

power:

	tVAL tPOW powNum	{	
							$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::POW);
							MExpr::ASTNode* val = new MExpr::ASTValue($1);
							$$->setChild(0, val);
							$$->setChild(1, $3);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back(val);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}

|	tVAR tPOW powNum	{	
							$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::POW);
							MExpr::ASTNode* var = new MExpr::ASTVariable($1);
							$$->setChild(0, var);
							$$->setChild(1, $3);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back(var);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}

|	tLPAR expr tRPAR tPOW powNum	{	
										$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::POW);
										$$->setChild(0, $2);
										$$->setChild(1, $5);
										((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
									}
;

atomicExpr:

	tLPAR expr tRPAR	{ 
							$$ = $2; 
						}
|	tLPAR expr tRPAR atomicExpr		{
  										$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::MUL);
  										$$->setChild(0, $2);
  										$$->setChild(1, $4);
  										((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
  									}

|	tVAL				{ 
							$$ = new MExpr::ASTValue($1);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
					 	}

|	tVAR				{	
							$$ = new MExpr::ASTVariable($1);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}

|	tFUNC tLPAR funcArgs tRPAR	{
								ostringstream ss;
								ss << *$1 << "_" << $3;
								delete $1;
								$$ = new MExpr::ASTFunction(ss.str(), $3);
								for(int i=0; i<$3; i++){
									$$->setChild(i, ((MExpr_ParserParam*)data)->funcArgsAccumulator->back());
									((MExpr_ParserParam*)data)->funcArgsAccumulator->pop_back();
								}
								((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
  							}

|	tVAL atomicExpr 	{
  							$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::MUL);
  							MExpr::ASTNode* val = new MExpr::ASTValue($1);
  							$$->setChild(0, val);
  							$$->setChild(1, $2);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back(val);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}
|	tVAR atomicExpr 	{
							$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::MUL);
							MExpr::ASTNode* var = new MExpr::ASTVariable($1);
							$$->setChild(0, var);
							$$->setChild(1, $2);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back(var);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}

|	power atomicExpr	{
							$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::MUL);
							$$->setChild(0, $1);
							$$->setChild(1, $2);
	  						((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}

|	power

;

expr:

	expr tADD expr		{ 	
							$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::ADD);
							$$->setChild(0, $1);
							$$->setChild(1, $3);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}
  
|	expr tSUB expr		{	
							$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::SUB);
							$$->setChild(0, $1);
							$$->setChild(1, $3);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
  						}

|	expr tMUL expr		{	
							$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::MUL);
							$$->setChild(0, $1);
							$$->setChild(1, $3);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}

|	expr tDIV expr		{	
							$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::DIV);
							$$->setChild(0, $1);
							$$->setChild(1, $3);
							((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
						}
						
|	tADD atomicExpr %prec tPREADD		{	
											$$ = $2
										}

|	tSUB atomicExpr %prec tPREADD		{	
											$$ = new MExpr::ASTPrimitiveOp(MExpr::ASTPrimitiveOp::MUL);
											MExpr::ASTNode* usubValue = new MExpr::ASTValue(-1); 
											$$->setChild(0, usubValue);
											$$->setChild(1, $2);
											((MExpr_ParserParam*)data)->errRecPointerPool->push_back($$);
											((MExpr_ParserParam*)data)->errRecPointerPool->push_back(usubValue);
										}

|	atomicExpr

;

%%