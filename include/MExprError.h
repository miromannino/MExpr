/*
 * Mathematical Expressions Error Classes
 * Headers
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
