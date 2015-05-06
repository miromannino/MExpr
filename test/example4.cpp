/*
 * MExpr C++ Example 4
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

#include <stdio.h>
#include <iostream>
#include <MExpr.h>
using namespace std;
using namespace MExpr;

void myDiv(MExpr::StackType* s) { //myDiv(a,b) = a/b
    MExpr::ValueType arg1, arg2;
    arg1 = s->stack[s->stp - 2];
    arg2 = s->stack[s->stp - 1];
    s->stack[s->stp - 2] = arg1 / arg2;
    s->stp--;
}

int main(void) {
    Expression* e = new Expression("_div(16,4)");
    e->setFunction("_div", &myDiv, 2);

	cout << e->evaluate() << endl;

    return 0;
}
