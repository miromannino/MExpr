/*
 * Mathematical Expressions Instruction
 * Headers
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#ifndef __MExprInstr_H__
#define __MExprInstr_H__

#include <MExprDefinitions.h>
#include <string>

namespace MExpr {

		/** Instruction types */
		typedef enum StructInstructionType{
			iVAL, // constant value, like 5, 3, 10, 42
			iVAR,  // variable like 'x', 'y', 'z'
			iADD, // '+'
			iMUL, // '*'
			iSUB, // '-'
			iDIV, // '/'
			iPOW, // '^'
			iFUN  // functions
		} InstructionType;

		/** Instruction structure */
		typedef struct StructInstr{
			InstructionType type;
			union {
				ValueType value;
				char variable;
				std::string* funName;
			} arg;
		} Instruction;

} //end of namespace MExpr

#endif
