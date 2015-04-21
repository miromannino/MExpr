/*
 * Mathematical Expressions Standard Function Code
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

#include <MExprStdFunc.h>
#include <math.h>

using namespace MExpr;

void std_acos(StackType* s) { //double acos(double);
    s->stack[s->stp - 1] = acos(s->stack[s->stp - 1]);
}

void std_asin(StackType* s) { //double asin(double);
    s->stack[s->stp - 1] = asin(s->stack[s->stp - 1]);
}

void std_atan(StackType* s) { //double atan(double);
    s->stack[s->stp - 1] = atan(s->stack[s->stp - 1]);
}

void std_atan2(StackType* s) { //double atan2(double, double);
    s->stack[s->stp - 2] = atan2(s->stack[s->stp - 2], s->stack[s->stp - 1]);
    s->stp--;
}

void std_ceil(StackType* s) { //double ceil(double);
    s->stack[s->stp - 1] = ceil(s->stack[s->stp - 1]);
}

void std_cos(StackType* s) { //double cos(double);
    s->stack[s->stp - 1] = cos(s->stack[s->stp - 1]);
}

void std_cosh(StackType* s) { //double cosh(double);
    s->stack[s->stp - 1] = cosh(s->stack[s->stp - 1]);
}

void std_exp(StackType* s) { //double exp(double);
    s->stack[s->stp - 1] = exp(s->stack[s->stp - 1]);
}

void std_fabs(StackType* s) { //double fabs(double);
    s->stack[s->stp - 1] = fabs(s->stack[s->stp - 1]);
}

void std_floor(StackType* s) { //double floor(double);
    s->stack[s->stp - 1] = floor(s->stack[s->stp - 1]);
}

void std_fmod(StackType* s) { //double fmod(double, double);
    s->stack[s->stp - 2] = fmod(s->stack[s->stp - 2], s->stack[s->stp - 1]);
    s->stp--;
}

void std_log(StackType* s) { //double log(double);
    s->stack[s->stp - 1] = log(s->stack[s->stp - 1]);
}

void std_log10(StackType* s) { //double log10(double);
    s->stack[s->stp - 1] = log10(s->stack[s->stp - 1]);
}

void std_sin(StackType* s) { //double sin(double);
    s->stack[s->stp - 1] = sin(s->stack[s->stp - 1]);
}

void std_sinh(StackType* s) { //double sinh(double);
    s->stack[s->stp - 1] = sinh(s->stack[s->stp - 1]);
}

void std_sqrt(StackType* s) { //double sqrt(double);
    s->stack[s->stp - 1] = sqrt(s->stack[s->stp - 1]);
}

void std_tan(StackType* s) { //double tan(double);
    s->stack[s->stp - 1] = tan(s->stack[s->stp - 1]);
}

void std_tanh(StackType* s) { //double tanh(double);
    s->stack[s->stp - 1] = tanh(s->stack[s->stp - 1]);
}

void std_erf(StackType* s) { //double erf(double);
    s->stack[s->stp - 1] = erf(s->stack[s->stp - 1]);
}

void std_erfc(StackType* s) { //double erfc(double);
    s->stack[s->stp - 1] = erfc(s->stack[s->stp - 1]);
}

void std_hypot(StackType* s) { //double hypot(double, double);
    s->stack[s->stp - 2] = hypot(s->stack[s->stp - 2], s->stack[s->stp - 1]);
    s->stp--;
}

void std_j0(StackType* s) { //double j0(double);
    s->stack[s->stp - 1] = j0(s->stack[s->stp - 1]);
}

void std_j1(StackType* s) { //double j1(double);
    s->stack[s->stp - 1] = j1(s->stack[s->stp - 1]);
}

void std_jn(StackType* s) { //double jn(int, double);
    s->stack[s->stp - 2] = jn((int) s->stack[s->stp - 2], s->stack[s->stp - 1]);
    s->stp--;
}

void std_lgamma(StackType* s) { //double lgamma(double);
    s->stack[s->stp - 1] = lgamma(s->stack[s->stp - 1]);
}

void std_y0(StackType* s) { //double y0(double);
    s->stack[s->stp - 1] = y0(s->stack[s->stp - 1]);
}

void std_y1(StackType* s) { //double y1(double);
    s->stack[s->stp - 1] = y1(s->stack[s->stp - 1]);
}

void std_yn(StackType* s) { //double yn(int, double);
    s->stack[s->stp - 2] = yn((int) s->stack[s->stp - 2], s->stack[s->stp - 1]);
    s->stp--;
}

void std_isnan(StackType* s) { //int    isnan(double);
    s->stack[s->stp - 1] = isnan(s->stack[s->stp - 1]);
}

void std_acosh(StackType* s) { //double acosh(double);
    s->stack[s->stp - 1] = acosh(s->stack[s->stp - 1]);
}

void std_asinh(StackType* s) { //double asinh(double);
    s->stack[s->stp - 1] = asinh(s->stack[s->stp - 1]);
}

void std_atanh(StackType* s) { //double atanh(double);
    s->stack[s->stp - 1] = atanh(s->stack[s->stp - 1]);
}

void std_cbrt(StackType* s) { //double cbrt(double);
    s->stack[s->stp - 1] = cbrt(s->stack[s->stp - 1]);
}

void std_expm1(StackType* s) { //double expm1(double);
    s->stack[s->stp - 1] = expm1(s->stack[s->stp - 1]);
}

void std_ilogb(StackType* s) { //int    ilogb(double);
    s->stack[s->stp - 1] = ilogb(s->stack[s->stp - 1]);
}

void std_log1p(StackType* s) { //double log1p(double);
    s->stack[s->stp - 1] = log1p(s->stack[s->stp - 1]);
}

void std_logb(StackType* s) { //double logb(double);
    s->stack[s->stp - 1] = logb(s->stack[s->stp - 1]);
}

void std_nextafter(StackType* s) { //double nextafter(double, double);
    s->stack[s->stp - 2] = nextafter(s->stack[s->stp - 2], s->stack[s->stp - 1]);
    s->stp--;
}

void std_remainder(StackType* s) { //double remainder(double, double);
    s->stack[s->stp - 2] = remainder(s->stack[s->stp - 2], s->stack[s->stp - 1]);
    s->stp--;
}

void std_rint(StackType* s) { //double rint(double);
    s->stack[s->stp - 1] = rint(s->stack[s->stp - 1]);
}

void std_scalb(StackType* s) { //double scalb(double, double);
    s->stack[s->stp - 2] = scalb(s->stack[s->stp - 2], s->stack[s->stp - 1]);
    s->stp--;
}

void StdFunc::initializeEnv(Environment* env) {
    env->setFunction("_acos", &std_acos, 1); //double acos(double);
    env->setFunction("_asin", &std_asin, 1); //double asin(double);
    env->setFunction("_atan", &std_atan, 1); //double atan(double);
    env->setFunction("_atan2", &std_atan2, 2); //double atan2(double, double);
    env->setFunction("_ceil", &std_ceil, 1); //double ceil(double);
    env->setFunction("_cos", &std_cos, 1); //double cos(double);
    env->setFunction("_cosh", &std_cosh, 1); //double cosh(double);
    env->setFunction("_exp", &std_exp, 1); //double exp(double);
    env->setFunction("_fabs", &std_fabs, 1); //double fabs(double);
    env->setFunction("_floor", &std_floor, 1); //double floor(double);
    env->setFunction("_fmod", &std_fmod, 2); //double fmod(double, double);
    env->setFunction("_log", &std_log, 1); //double log(double);
    env->setFunction("_log10", &std_log10, 1); //double log10(double);
    env->setFunction("_sin", &std_sin, 1); //double sin(double);
    env->setFunction("_sinh", &std_sinh, 1); //double sinh(double);
    env->setFunction("_sqrt", &std_sqrt, 1); //double sqrt(double);
    env->setFunction("_tan", &std_tan, 1); //double tan(double);
    env->setFunction("_tanh", &std_tanh, 1); //double tanh(double);
    env->setFunction("_erf", &std_erf, 1); //double erf(double);
    env->setFunction("_erfc", &std_erfc, 1); //double erfc(double);
    env->setFunction("_hypot", &std_hypot, 2); //double hypot(double, double);
    env->setFunction("_j0", &std_j0, 1); //double j0(double);
    env->setFunction("_j1", &std_j1, 1); //double j1(double);
    env->setFunction("_jn", &std_jn, 2); //double jn(int, double);
    env->setFunction("_lgamma", &std_lgamma, 1); //double lgamma(double);
    env->setFunction("_y0", &std_y0, 1); //double y0(double);
    env->setFunction("_y1", &std_y1, 1); //double y1(double);
    env->setFunction("_yn", &std_yn, 2); //double yn(int, double);
    env->setFunction("_isnan", &std_isnan, 1); //int    isnan(double);
    env->setFunction("_acosh", &std_acosh, 1); //double acosh(double);
    env->setFunction("_asinh", &std_asinh, 1); //double asinh(double);
    env->setFunction("_atanh", &std_atanh, 1); //double atanh(double);
    env->setFunction("_cbrt", &std_cbrt, 1); //double cbrt(double);
    env->setFunction("_expm1", &std_expm1, 1); //double expm1(double);
    env->setFunction("_ilogb", &std_ilogb, 1); //int    ilogb(double);
    env->setFunction("_log1p", &std_log1p, 1); //double log1p(double);
    env->setFunction("_logb", &std_logb, 1); //double logb(double);
    env->setFunction("_nextafter", &std_nextafter, 2); //double nextafter(double, double);
    env->setFunction("_remainder", &std_remainder, 2); //double remainder(double, double);
    env->setFunction("_rint", &std_rint, 1); //double rint(double);
    env->setFunction("_scalb", &std_scalb, 2); //double scalb(double, double);
}
