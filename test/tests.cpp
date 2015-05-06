/*
 * MExpr C Tests
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

#include <gtest/gtest.h>
#include <MExpr.h>

using namespace std;
using namespace MExpr;

double valueOfExpr(string expr) {
    Expression* e = new Expression(expr);
    return e->evaluate();
}

TEST(TestConst, TestIntegers) {
    EXPECT_EQ(42, valueOfExpr("42"));
    EXPECT_EQ(0, valueOfExpr("0"));
}

TEST(TestConst, TestDoubles) {
    EXPECT_EQ(42, valueOfExpr("42.0"));
    EXPECT_EQ(0, valueOfExpr("0.0"));
    EXPECT_EQ(1.23456, valueOfExpr("1.23456"));
}

TEST(TestConst, TestVariables) {
    Expression* e = new Expression("x");
    e->setVariable('x', 3);
    EXPECT_EQ(3, e->evaluate());
}

TEST(TestConst, TestWrongVariables) {
    Expression* e = new Expression("x");
    EXPECT_ANY_THROW(e->setVariable('-', 3));
}

TEST(TestBinaryOp, TestSum) {
    EXPECT_EQ(4, valueOfExpr("2 + 2"));
    EXPECT_EQ(2.1, valueOfExpr("0.1 + 2"));
}

TEST(TestBinaryOp, TestSubtraction) {
    EXPECT_EQ(2, valueOfExpr("2 - 0"));
    EXPECT_EQ(-1.9, valueOfExpr("0.1 - 2"));
    EXPECT_EQ(2, valueOfExpr("2 - 0"));
    EXPECT_EQ(1.9, valueOfExpr("2 - 0.1"));
}

TEST(TestBinaryOp, TestMultiplication) {
    EXPECT_EQ(1, valueOfExpr("2 * 0.5"));
    EXPECT_EQ(0, valueOfExpr("2 * 0.0"));
    EXPECT_EQ(6, valueOfExpr("2 * 3"));
}

TEST(TestBinaryOp, TestDivision) {
    EXPECT_EQ(4, valueOfExpr("12 / 3"));
    EXPECT_EQ(-4, valueOfExpr("12 / -3"));
    ASSERT_ANY_THROW(valueOfExpr("42 / 0"));
    ASSERT_ANY_THROW(valueOfExpr("42 / 0.0"));
    ASSERT_ANY_THROW(valueOfExpr("42 / -0.0"));
}

TEST(TestBinaryOp, TestPow) {
    EXPECT_EQ(8, valueOfExpr("2 ^ 3"));
    EXPECT_EQ(0.5, valueOfExpr("2 ^ -1"));
    EXPECT_EQ(1, valueOfExpr("0 ^ 0"));
    EXPECT_EQ(4, valueOfExpr("16 ^ (1/2)"));
}


TEST(TestProperties, TestMulAddAssociativity) {
    EXPECT_EQ(14, valueOfExpr("2 + 3 * 4"));
    EXPECT_EQ(14, valueOfExpr("3 * 4 + 2"));
    EXPECT_EQ(14, valueOfExpr("2 + (3 * 4)"));
    EXPECT_EQ(20, valueOfExpr("(2 + 3) * 4"));
}

TEST(TestProperties, TestDivAddAssociativity) {
    EXPECT_EQ(5, valueOfExpr("2 + 12 / 4"));
    EXPECT_EQ(5, valueOfExpr("12 / 4 + 2"));
    EXPECT_EQ(5, valueOfExpr("2 + (12 / 4)"));
    EXPECT_EQ(3.5, valueOfExpr("(2 + 12) / 4"));
}

TEST(TestProperties, TestDivAssociativity) {
    EXPECT_EQ(0.75, valueOfExpr("12 / 4 / 4"));
    EXPECT_EQ(0.75, valueOfExpr("(12 / 4) / 4"));
    EXPECT_EQ(12, valueOfExpr("12 / (4 / 4)"));
}

TEST(TestProperties, TestPowAssociativity) {
    EXPECT_EQ(512, valueOfExpr("2 ^ (3 ^ 2)"));
    EXPECT_EQ(64, valueOfExpr("(2 ^ 3) ^ 2"));

    EXPECT_EQ(32, valueOfExpr("2 ^ 3 * 4"));
    EXPECT_EQ(32, valueOfExpr("4 * 2 ^ 3"));
    EXPECT_EQ(32, valueOfExpr("(2 ^ 3) * 4"));
    EXPECT_EQ(4096, valueOfExpr("2 ^ (3 * 4)"));
}

TEST(TestUnaryOp, TestUnaryOp) {
    EXPECT_EQ(-2, valueOfExpr("-2"));
    EXPECT_EQ(+4, valueOfExpr("+4"));
    ASSERT_ANY_THROW(valueOfExpr("++4"));
    ASSERT_ANY_THROW(valueOfExpr("--4"));
}

TEST(TestImplicitMultiplications, TestVariables) {
    Expression* e = new Expression("xy");
    e->setVariable('x', 3);
    e->setVariable('y', 4);
    EXPECT_EQ(12, e->evaluate());
}

TEST(TestImplicitMultiplications, TestParenthesis) {
    Expression* e = new Expression("(x)(y + 2)");
    e->setVariable('x', 3);
    e->setVariable('y', 4);
    EXPECT_EQ(18, e->evaluate());
}

TEST(TestImplicitMultiplications, TestWithConstant) {
    Expression* e = new Expression("5xy");
    e->setVariable('x', 3);
    e->setVariable('y', 4);
    EXPECT_EQ(60, e->evaluate());
}

TEST(TestImplicitMultiplications, TestWithPower) {
    Expression* e = new Expression("5xy^2");
    e->setVariable('x', 3);
    e->setVariable('y', 4);
    EXPECT_EQ(240, e->evaluate());
}

TEST(TestImplicitMultiplications, TestWithPower2) {
    Expression* e = new Expression("5x^3y^2");
    e->setVariable('x', 3);
    e->setVariable('y', 4);
    EXPECT_EQ(2160, e->evaluate());
}

TEST(TestFunctions, TestFunctions) {
    EXPECT_EQ(0.25, valueOfExpr("_cos(0)*_log10(100)/2_sqrt(16)"));
}


void myfunc(MExpr::StackType* s) { //myfunc(n) = n*3
    s->stack[s->stp - 1] *= 3;
}

void myDiv(MExpr::StackType* s) { //myDiv(a,b) = a/b
    MExpr::ValueType arg1, arg2;
    arg1 = s->stack[s->stp - 2];
    arg2 = s->stack[s->stp - 1];
    s->stack[s->stp - 2] = arg1 / arg2;
    s->stp--;
}

void mySum2(MExpr::StackType* s) { //mySum2(a,b) = a+b
    s->stack[s->stp - 2] = s->stack[s->stp - 2] + s->stack[s->stp - 1];
    s->stp--;
}
void mySum3(MExpr::StackType* s) { //mySum2(a,b,c) = a+b+c
    s->stack[s->stp - 3] = s->stack[s->stp - 3] + s->stack[s->stp - 2] + s->stack[s->stp - 1];
    s->stp -= 2;
}

TEST(TestFunctions, TestCustomFunctions) {
    Expression* e = new Expression("_math(42) + _div(16,4)");
    e->setFunction("_math", &myfunc, 1);
    e->setFunction("_div", &myDiv, 2);
    EXPECT_EQ(130, e->evaluate());
}

TEST(TestFunctions, TestCustomFunctionsWithoutUnderscore) {
    Expression* e = new Expression("2+2");
    ASSERT_ANY_THROW(e->setFunction("funcWithoutUnderscore", &myfunc, 1));
}

TEST(TestFunctions, TestFunctionsOverload) {
    Expression* e = new Expression("_sum(1,2) + _sum(3,4,5)");
    e->setFunction("_sum", &mySum2, 2);
    e->setFunction("_sum", &mySum3, 3);
    EXPECT_EQ(15, e->evaluate());
}

TEST(GenericTest, Test1) {
    Expression* e = new Expression("-3(4xy^2x-2x)(8x^-(3x)+2y^-2)");
    e->setVariable('x', 4);
    e->setVariable('y', -5);
    EXPECT_NEAR(-382.082, e->evaluate(), 0.001);
}

TEST(GenericTest, Test2) {
    EXPECT_NEAR(64.1457, valueOfExpr("+2+3*5+2-2*3+(7^-3-8+5)-4+(3/3)+2*5-6-(9-(3^4)+6)-6+8/7-8"), 0.0001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

