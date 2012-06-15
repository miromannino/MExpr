/*
 * Mathematical Expressions Error Classes
 * Headers
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#ifndef __MExprError_H__
#define __MExprError_H__

#ifdef __cplusplus
	#include <cstddef>
	#include <stdexcept>

namespace MExpr {

	class Error: public std::exception {
	public:

		enum Type {
			syntaxError,
			divisionByZero,
			lexError,
			astWrongChild,
			variableNotDefined,
			illegalVariableName,
			unknownPrimitiveOp,
			illegalArgsNum,
			illegalFunctionName,
			functionNotDefined
		};

		Error(Error::Type t);
		Error::Type getType();
		const char* what();
	private:
		Error::Type t;
	};

} //end of namespace MExpr

#endif //of #ifdef __cplusplus

#ifdef __cplusplus

	extern "C" {

#endif
	//TODO: C functions
#ifdef __cplusplus

	}

#endif

#endif
