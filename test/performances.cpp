/*
 * MExpr C++ Tests
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

#include <cstddef>
#include <stdio.h>
#include <iostream>
#include <map>
#include <string.h>
#include <time.h>
#include <MExpr.h>
using namespace std;
using namespace MExpr;

#define EVALUATIONS 10000000

int main(void) {

    string exprs[] = {
        "+2+3*5+2-2*3+(7^-3-8+5)-4+(3/3)+2*5-6-(9-(3^4)+6)-6+8/7-8",
        "_sqrt(2_sqrt(2))",
        "-3(4xy^2x-2x)(8x^-(3x)+2y^-2)"
    };

    for (int iter = 0; iter < 3; iter++) {
        cout << "Expr: " << exprs[iter] << endl;
        Expression* e;

        try {
            e = new Expression(exprs[iter]);
        } catch (Error ex) {
            cout << "Err: " << ex.what() << endl;
            return 0;
        }

        string* s = e->getExprTreeString();
        cout << "Expr AST Tree: " << endl << *s << endl;
        delete s;

        e->setVariable('x', 4);
        e->setVariable('y', -5);

        clock_t start, end;

        cout << "Evaluating in tree" << endl;

        start = clock();
        try {
            for (int i = 0; i < EVALUATIONS; i++) {
                e->evaluate(true); //tree evaluation with the parameter set 'true'
            }
        } catch (MExpr::Error ex) {
            cout << "Err: " << ex.what() << endl;
        }

        end = clock();
        printf("Time for %d evaluations navigating the AST: %lf\n\n", EVALUATIONS, (double) (end - start) / CLOCKS_PER_SEC);

        e->compile();

        cout << "Compiled Expression bytecode:" << endl;
        s = e->getExprCodeString(); //if you have not compiled s will be NULL
        if (s != NULL) {
            cout << *s;
            delete s;
        }
        cout << endl;

        cout << "Evaluating compiled expression" << endl;

        start = clock();
        try {
            for (int i = 0; i < EVALUATIONS; i++) {
                e->evaluate();
            }
        } catch (MExpr::Error ex) {
            cout << "Err: " << ex.what() << endl;
        }
        end = clock();
        printf("Time for %d evaluations in bytecode: %lf\n", EVALUATIONS, (double) (end - start) / CLOCKS_PER_SEC);

        delete e;

    }

    return 0;
}
