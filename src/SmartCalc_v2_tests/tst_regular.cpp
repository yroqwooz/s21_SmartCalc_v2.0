#include <gtest/gtest.h>

#include "../SmartCalc_v2/sccontroller.h"
#include "../SmartCalc_v2/scmodel.h"

using namespace testing;

//  NoInput
TEST(SmartCalc_v2, NoInput) {
    s21::SCController controller(nullptr);
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0");
}

//  Single input
TEST(SmartCalc_v2, OnlyOperator) {
    s21::SCController controller(nullptr);
    controller.PassOperator("+");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "+");
}

TEST(SmartCalc_v2, OnlyDot) {
    s21::SCController controller(nullptr);
    controller.PassDot();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0.");
}

TEST(SmartCalc_v2, NoOperator) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "12");
}

//  Float num no operator/trigonometric
TEST(SmartCalc_v2, FloatNumNoOperator1) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1.1");
}

TEST(SmartCalc_v2, FloatNumNoOperator2) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1.12");
}

TEST(SmartCalc_v2, FloatNumNoOperator3) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    controller.PassNum("2");
    controller.PassNum("3");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1.123");
}

TEST(SmartCalc_v2, FloatNumNoOperator4) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    controller.PassNum("2");
    controller.PassNum("3");
    controller.PassNum("4");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1.1234");
}

TEST(SmartCalc_v2, FloatNumNoOperator5) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    controller.PassNum("2");
    controller.PassNum("3");
    controller.PassNum("4");
    controller.PassNum("5");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1.12345");
}

TEST(SmartCalc_v2, FloatNumNoOperator6) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    controller.PassNum("2");
    controller.PassNum("3");
    controller.PassNum("4");
    controller.PassNum("5");
    controller.PassNum("6");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1.123456");
}

TEST(SmartCalc_v2, FloatNumNoOperator7) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    controller.PassNum("2");
    controller.PassNum("3");
    controller.PassNum("4");
    controller.PassNum("5");
    controller.PassNum("6");
    controller.PassNum("7");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1.1234567");
}

//  Multiple dot try
TEST(SmartCalc_v2, InputMultipleDot) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassDot();
    controller.PassDot();
    controller.PassDot();
    controller.PassNum("2");
    controller.PassDot();
    controller.PassDot();
    controller.PassNum("3");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1.23");
}

//  Plus operator
TEST(SmartCalc_v2, SimpleExprWholePlusWhole) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassOperator("+");
    controller.PassNum("3");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "4");
}

TEST(SmartCalc_v2, SimpleExprWholePlusFloat) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassNum("1");
    controller.PassOperator("+");
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "12.1");
}

TEST(SmartCalc_v2, SimpleExprFloatPlusWhole) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("3");
    controller.PassOperator("+");
    controller.PassNum("9");
    controller.PassNum("0");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "91.23");
}

TEST(SmartCalc_v2, SimpleExprFloatPlusFloat) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassNum("1");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("3");
    controller.PassOperator("+");
    controller.PassNum("9");
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("0");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "212.2");
}

//  Plus operator with unary

TEST(SmartCalc_v2, SimpleExprNegWholePlusWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassOperator("+");
    controller.PassNum("3");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "2");
}

TEST(SmartCalc_v2, SimpleExprNegWholePlusFloat) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassNum("1");
    controller.PassOperator("+");
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-9.9");
}

TEST(SmartCalc_v2, SimpleExprNegFloatPlusWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("3");
    controller.PassOperator("+");
    controller.PassNum("9");
    controller.PassNum("0");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "88.77");
}

TEST(SmartCalc_v2, SimpleExprNegFloatPlusFloat) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassNum("1");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("3");
    controller.PassOperator("+");
    controller.PassNum("9");
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("0");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-12.4");
}

//  Minus operator
TEST(SmartCalc_v2, SimpleExprWholeMinusWhole) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassOperator("-");
    controller.PassNum("3");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-2");
}

TEST(SmartCalc_v2, SimpleExprWholeMinusFloat) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassNum("1");
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "9.9");
}

TEST(SmartCalc_v2, SimpleExprFloatMinusWhole) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("3");
    controller.PassOperator("-");
    controller.PassNum("9");
    controller.PassNum("0");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-88.77");
}

TEST(SmartCalc_v2, SimpleExprFloatMinusFloat) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassNum("1");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("3");
    controller.PassOperator("-");
    controller.PassNum("9");
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("0");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "12.4");
}

//  Minus operator with unary
TEST(SmartCalc_v2, SimpleExprNegWholeMinusWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassOperator("-");
    controller.PassNum("3");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-4");
}

TEST(SmartCalc_v2, SimpleExprNegWholeMinusFloat) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassNum("1");
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-12.1");
}

TEST(SmartCalc_v2, SimpleExprNegFloatMinusWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("3");
    controller.PassOperator("-");
    controller.PassNum("9");
    controller.PassNum("0");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-91.23");
}

TEST(SmartCalc_v2, SimpleExprNegFloatMinusFloat) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassNum("1");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("3");
    controller.PassOperator("-");
    controller.PassNum("9");
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("0");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-212.2");
}

//  Multi operator
TEST(SmartCalc_v2, SimpleExprWholeMultiWhole) {
    s21::SCController controller(nullptr);
    controller.PassNum("3");
    controller.PassOperator("*");
    controller.PassNum("10");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "30");
}

TEST(SmartCalc_v2, SimpleExprWholeMultiFloat) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassNum("1");
    controller.PassOperator("*");
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "12.1");
}

TEST(SmartCalc_v2, SimpleExprFloatMultiWhole) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("3");
    controller.PassOperator("*");
    controller.PassNum("9");
    controller.PassNum("0");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "110.7");
}

TEST(SmartCalc_v2, SimpleExprFloatMultiFloat) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassNum("1");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("3");
    controller.PassOperator("*");
    controller.PassNum("9");
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("0");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "11218.77");
}

//  Multi operator with unary
TEST(SmartCalc_v2, SimpleExprNegWholeMultiWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("3");
    controller.PassOperator("*");
    controller.PassNum("10");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-30");
}

TEST(SmartCalc_v2, SimpleExprNegWholeMultiFloat) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassNum("1");
    controller.PassOperator("*");
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("1");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-12.1");
}

TEST(SmartCalc_v2, SimpleExprNegFloatMultiWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("3");
    controller.PassOperator("*");
    controller.PassNum("9");
    controller.PassNum("0");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-110.7");
}

TEST(SmartCalc_v2, SimpleExprNegFloatMultiFloat) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassNum("1");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("3");
    controller.PassOperator("*");
    controller.PassNum("9");
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("0");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-11218.77");
}

//  Div operator
TEST(SmartCalc_v2, SimpleExprWholeDivWhole) {
    s21::SCController controller(nullptr);
    controller.PassNum("9");
    controller.PassOperator("/");
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "4.5");
}

TEST(SmartCalc_v2, SimpleExprFloatDivWhole) {
    s21::SCController controller(nullptr);
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassOperator("/");
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "4.6");
}

TEST(SmartCalc_v2, SimpleExprWholeDivFloat) {
    s21::SCController controller(nullptr);
    controller.PassNum("9");
    controller.PassOperator("/");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "4.0909091");
}

TEST(SmartCalc_v2, SimpleExprFloatDivFloat) {
    s21::SCController controller(nullptr);
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassOperator("/");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "4.1818182");
}

//  Div operator with unary
TEST(SmartCalc_v2, SimpleExprNegWholeDivWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("9");
    controller.PassOperator("/");
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-4.5");
}

TEST(SmartCalc_v2, SimpleExprNegFloatDivWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassOperator("/");
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-4.6");
}

TEST(SmartCalc_v2, SimpleExprNegWholeDivFloat) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("9");
    controller.PassOperator("/");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-4.0909091");
}

TEST(SmartCalc_v2, SimpleExprNegFloatDivFloat) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassOperator("/");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-4.1818182");
}

//  Mod operator
TEST(SmartCalc_v2, SimpleExprWholeModWhole) {
    s21::SCController controller(nullptr);
    controller.PassNum("9");
    controller.PassOperator("mod");
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1");
}

TEST(SmartCalc_v2, SimpleExprFloatModWhole) {
    s21::SCController controller(nullptr);
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassOperator("mod");
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1");
}

TEST(SmartCalc_v2, SimpleExprWholeModFloat) {
    s21::SCController controller(nullptr);
    controller.PassNum("9");
    controller.PassOperator("mod");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1");
}

TEST(SmartCalc_v2, SimpleExprFloatModFloat) {
    s21::SCController controller(nullptr);
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassOperator("mod");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1");
}

// Mod operator with unary
TEST(SmartCalc_v2, SimpleExprNegWholeModWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("9");
    controller.PassOperator("mod");
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-1");
}

TEST(SmartCalc_v2, SimpleExprNegFloatModWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassOperator("mod");
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-1");
}

TEST(SmartCalc_v2, SimpleExprNegWholeModFloat) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("9");
    controller.PassOperator("mod");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-1");
}

TEST(SmartCalc_v2, SimpleExprNegFloatModFloat) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("9");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassOperator("mod");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-1");
}

// Times operator
TEST(SmartCalc_v2, SimpleExprWholeTimesWhole) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassNum("0");
    controller.PassOperator("^");
    controller.PassNum("2");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "100");
}

TEST(SmartCalc_v2, SimpleExprWholeTimesFloat) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassNum("0");
    controller.PassOperator("^");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "158.4893192");
}

TEST(SmartCalc_v2, SimpleExprFloatTimesWhole) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassOperator("^");
    controller.PassNum("2");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "104.04");
}

TEST(SmartCalc_v2, SimpleExprFloatTimesFloat) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassOperator("^");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "165.5466428");
}

//  Times operator with unary
TEST(SmartCalc_v2, SimpleExprNegWholeTimesWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassNum("0");
    controller.PassOperator("^");
    controller.PassNum("2");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "100");
}

TEST(SmartCalc_v2, SimpleExprNegWholeTimesFloat) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassNum("0");
    controller.PassOperator("^");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-158.4893192");
}

TEST(SmartCalc_v2, SimpleExprNegFloatTimesWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassOperator("^");
    controller.PassNum("2");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "104.04");
}

TEST(SmartCalc_v2, SimpleExprNegFloatTimesFloat) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassOperator("^");
    controller.PassNum("2");
    controller.PassDot();
    controller.PassNum("2");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-165.5466428");
}

//  Sqrt operator
TEST(SmartCalc_v2, SimpleExprSqrtWhole) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("sqrt");
    controller.PassNum("16");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "4");
}

TEST(SmartCalc_v2, SimpleExprSqrtNegWhole) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("sqrt");
    controller.PassOperator("-");
    controller.PassNum("16");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "sqrt(-16)");
}

TEST(SmartCalc_v2, SimpleExprSqrtFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("sqrt");
    controller.PassNum("17.4");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "4.1713307");
}

TEST(SmartCalc_v2, SimpleExprSqrtNegFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("sqrt");
    controller.PassOperator("-");
    controller.PassNum("17.4");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "sqrt(-17.4)");
}

//  Natural logarifm (e)
TEST(SmartCalc_v2, SimpleExprLnWhole) {

    s21::SCController controller(nullptr);
    controller.PassTringonometric("ln");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0");
}

TEST(SmartCalc_v2, SimpleExprLnNegWhole) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("ln");
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "ln(-1)");
}

TEST(SmartCalc_v2, SimpleExprLnFloat) {

    s21::SCController controller(nullptr);
    controller.PassTringonometric("ln");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-0.6931472");
}

TEST(SmartCalc_v2, SimpleExprLnNegFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("ln");
    controller.PassOperator("-");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "ln(-0.5)");
}

// Logarifm (10)
TEST(SmartCalc_v2, SimpleExprLogWhole) {

    s21::SCController controller(nullptr);
    controller.PassTringonometric("log");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0");
}

TEST(SmartCalc_v2, SimpleExprLogNegWhole) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("log");
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "log(-1)");
}

TEST(SmartCalc_v2, SimpleExprLogFloat) {

    s21::SCController controller(nullptr);
    controller.PassTringonometric("log");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-0.30103");
}

TEST(SmartCalc_v2, SimpleExprLogNegFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("log");
    controller.PassOperator("-");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "log(-0.5)");
}

//  Unary cases
TEST(SmartCalc_v2, SimpleExprNegativeWholePlusWhole) {
    s21::SCController controller(nullptr);
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassNum("0");
    controller.PassOperator("+");
    controller.PassNum("9");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-1");
}


//  Trigonometrics
//  Sinus
TEST(SmartCalc_v2, SimpleExprSinusWhole) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("sin");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0.841471");
}

TEST(SmartCalc_v2, SimpleExprSinusNegWhole) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("sin");
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-0.841471");
}

TEST(SmartCalc_v2, SimpleExprSinusFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("sin");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0.4794255");
}

TEST(SmartCalc_v2, SimpleExprSinusNegFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("sin");
    controller.PassOperator("-");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-0.4794255");
}

//  Arcsinus
TEST(SmartCalc_v2, SimpleExprArcSinusWhole) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("asin");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1.5707963");
}

TEST(SmartCalc_v2, SimpleExprArcSinusNegWhole) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("asin");
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-1.5707963");
}

TEST(SmartCalc_v2, SimpleExprArcSinusFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("asin");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0.5235988");
}

TEST(SmartCalc_v2, SimpleExprArcSinusNegFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("asin");
    controller.PassOperator("-");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-0.5235988");
}

//  Cosinus
TEST(SmartCalc_v2, SimpleExprCosinusWhole) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("cos");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0.5403023");
}

TEST(SmartCalc_v2, SimpleExprCosinusNegWhole) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("cos");
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0.5403023");
}

TEST(SmartCalc_v2, SimpleExprCosinusFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("cos");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0.8775826");
}

TEST(SmartCalc_v2, SimpleExprCosinusNegFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("cos");
    controller.PassOperator("-");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0.8775826");
}

//  Arccosinus
TEST(SmartCalc_v2, SimpleExprArcCosinusWhole) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("acos");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0");
}

TEST(SmartCalc_v2, SimpleExprArcCosinusNegWhole) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("acos");
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "3.1415927");
}

TEST(SmartCalc_v2, SimpleExprArcCosinusFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("acos");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1.0471976");
}

TEST(SmartCalc_v2, SimpleExprArcCosinusNegFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("acos");
    controller.PassOperator("-");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "2.0943951");
}

//  Tangens
TEST(SmartCalc_v2, SimpleExprTangensWhole) {

    s21::SCController controller(nullptr);
    controller.PassTringonometric("tan");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "1.5574077");
}

TEST(SmartCalc_v2, SimpleExprTangensNegWhole) {

    s21::SCController controller(nullptr);
    controller.PassTringonometric("tan");
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-1.5574077");
}

TEST(SmartCalc_v2, SimpleExprTangensFloat) {

    s21::SCController controller(nullptr);
    controller.PassTringonometric("tan");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0.5463025");
}

TEST(SmartCalc_v2, SimpleExprTangensNegFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("tan");
    controller.PassOperator("-");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-0.5463025");
}

//  Arctangens
TEST(SmartCalc_v2, SimpleExprArcTangensWhole) {

    s21::SCController controller(nullptr);
    controller.PassTringonometric("atan");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0.7853982");
}

TEST(SmartCalc_v2, SimpleExprArcTangensNegWhole) {

    s21::SCController controller(nullptr);
    controller.PassTringonometric("atan");
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-0.7853982");
}

TEST(SmartCalc_v2, SimpleExprArcTangensFloat) {

    s21::SCController controller(nullptr);
    controller.PassTringonometric("atan");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0.4636476");
}

TEST(SmartCalc_v2, SimpleExprArcTangensNegFloat) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("atan");
    controller.PassOperator("-");
    controller.PassNum("0");
    controller.PassDot();
    controller.PassNum("5");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-0.4636476");
}

//  Complex expressions
TEST(SmartCalc_v2, ComplexExpr_case1) {
    s21::SCController controller(nullptr);
    controller.PassNum("(+15^2-3200mod300)*(1/3)^2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "2.7777778");
}

TEST(SmartCalc_v2, ComplexExpr_case2) {
    s21::SCController controller(nullptr);
    controller.PassNum("-(-1+343)/2+67/(-56)+7/2*23");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-91.6964286");
}

TEST(SmartCalc_v2, ComplexExpr_case3) {
    s21::SCController controller(nullptr);
    controller.PassNum("2^3^2");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "64");
}

TEST(SmartCalc_v2, ComplexExpr_case4) {
    s21::SCController controller(nullptr);
    controller.PassNum("2^(3^2)");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "512");
}

TEST(SmartCalc_v2, ComplexExpr_case5) {
    s21::SCController controller(nullptr);
    controller.PassNum("12");
    controller.PassOperator("^");
    controller.PassOpenBracket();
    controller.PassNum("12-10");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "144");
}

TEST(SmartCalc_v2, ComplexExpr_case6) {
    s21::SCController controller(nullptr);
    controller.PassNum("12");
    controller.PassOperator("+");
    controller.PassOpenBracket();
    controller.PassOperator("-");
    controller.PassNum("12");
    controller.PassOperator("-");
    controller.PassNum("10");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-10");
}

//  Input features
TEST(SmartCalc_v2, SimpleExprChangindMind_case1) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassOperator("+");
    controller.PassOperator("-");
    controller.PassNum("3");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-2");
}

TEST(SmartCalc_v2, SimpleExprChangindMind_case2) {
    s21::SCController controller(nullptr);
    controller.PassNum("1");
    controller.PassOperator("mod");
    controller.PassOperator("+");
    controller.PassOperator("-");
    controller.PassNum("3");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "-2");
}

TEST(SmartCalc_v2, SimpleExprChangindMind_case3) {
    s21::SCController controller(nullptr);
    controller.PassNum("10");
    controller.PassOperator("mod");
    controller.PassOpenBracket();
    controller.PassOperator("+");
    controller.PassOperator("-");
    controller.PassOperator("+");
    controller.PassNum("3");
    controller.PassOperator("+");
    controller.PassOperator("-");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0");
}

TEST(SmartCalc_v2, OnlyAnyTrigonometric) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("sin");
    ASSERT_EQ(controller.InitCalculation().toStdString(), "sin(");
}

TEST(SmartCalc_v2, InsertTrigoPhantomMulti) {
    s21::SCController controller(nullptr);
    controller.PassNum("12");
    controller.PassTringonometric("acos");
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0");
}

TEST(SmartCalc_v2, EraseTrigonometrics) {
    s21::SCController controller(nullptr);
    controller.PassNum("12");
    controller.PassTringonometric("acos");
    controller.PassTringonometric("sin");
    controller.ClickedBS();
    controller.PassTringonometric("cos");
    controller.ClickedBS();
    controller.PassNum("1");
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0");
}

TEST(SmartCalc_v2, EraseOnlyTrigonometrics) {
    s21::SCController controller(nullptr);
    controller.PassTringonometric("acos");
    controller.ClickedBS();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "0");
}

TEST(SmartCalc_v2, EraseClosingBRacket) {
    s21::SCController controller(nullptr);
    controller.PassNum("12");
    controller.PassOperator("+");
    controller.PassOpenBracket();
    controller.PassNum("23");
    controller.PassOperator("-");
    controller.PassNum("23");
    controller.PassClosingBracket();
    controller.ClickedBS();
    controller.ClickedBS();
    controller.PassClosingBracket();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "33");
}

// TEST(SmartCalc_v2, EraseClosingBRacket) {
//     s21::SCController controller(nullptr);
//     controller.PassNum("12");
    
//     ASSERT_EQ(controller.InitCalculation().toStdString(), "33");
// }

//  Erase last
TEST(SmartCalc_v2, EraseLastCheck) {
    s21::SCController controller(nullptr);
    controller.PassNum("10000+1234");
    ASSERT_EQ(controller.ClickedBS().toStdString(), "10000+123");
}

//  Clear expr
TEST(SmartCalc_v2, ClearLastCheck) {
    s21::SCController controller(nullptr);
    controller.PassNum("10000+1234");
    ASSERT_EQ(controller.ClickedAC().toStdString(), "0");
}

//  PassX
TEST(SmartCalc_v2, XPassing_case1) {
    s21::SCController controller(nullptr);
    controller.PassX();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "x");
}

TEST(SmartCalc_v2, XPassing_case2) {
    s21::SCController controller(nullptr);
    controller.PassNum("12+");
    controller.PassX();
    ASSERT_EQ(controller.InitCalculation().toStdString(), "12+x");
}


