/*
 * MExpr C Tests
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#include <stdio.h>
#include <time.h>
#include <MExpr.h>
#include <MExprCode.h>

int main(void){
	//TODO: with the new functions

//while(1){ //check memory leaks
	char expr[] = "2+3*5+2*(7*8*5)*4+3+2+2+5*6*(9*3*4+6)+6+8+7+8+";
	printf("C Calculated result: %lf\n", (double)(2+3*5+2*(7*8*5)*4+3+2+2+5*6*(9*3*4+6)+6+8+7+8));

	MExpr* e = mexpr_MExpr_new(expr);
	printf("MExpr result: %lf\n" , mexpr_MExpr_evaluate(e));

	MExprCode* c = mexpr_MExprCode_new(e);
	printf("MExpr::Code result: %lf\n" , mexpr_MExprCode_evaluate(c));
	mexpr_MExprCode_dispose(c);

	mexpr_MExpr_dispose(e);
//}
    return 0;
}
