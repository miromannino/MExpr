/*
 * Mathematical Expressions Expression
 * Various definitions
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#ifndef __MExprDefinitions_H__
#define __MExprDefinitions_H__

namespace MExpr {

/** Instruction value type */
typedef double ValueType;

/** stack type */
typedef struct {
	ValueType* stack;
	unsigned int size;
	unsigned int stp;
} StackType;

/** functions type */
typedef void (*FunctionPntrType) (StackType*);
typedef struct {
	FunctionPntrType fnPntr;
	unsigned int numArgs;
}FunctionType;

} //end of namespace MExpr

#endif
