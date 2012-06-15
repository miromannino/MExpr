/*
 * Mathematical Expressions Standard Function Headers
 *
 * @author Miro Mannino
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 2.5 Generic License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nd/2.5/
 * or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#ifndef __MExprStdFunc_H__
#define __MExprStdFunc_H__

#ifdef __cplusplus
	#include <cstddef>
	#include <stdexcept>
	#include <MExprDefinitions.h>
	#include <MExprEnvironment.h>

namespace MExpr {

	class StdFunc {
	public:
		static void initializeEnv(Environment* env);
	};

} //end of namespace MExpr

#endif //of #ifdef __cplusplus

#endif
