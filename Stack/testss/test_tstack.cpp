#include "../Stack/TStack.h"

#include "gtest.h"

TEST(TStack, can_create_stack_with_positive_size) {
    ASSERT_NO_THROW(TStack<int> st(10));
}

TEST(TStack, throws_when_create_stack_with_negative_size) {
    ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, throws_when_create_stack_with_zero_size) {
    ASSERT_ANY_THROW(TStack<int> st(0));
}

TEST(TStack, can_push_and_pop_values) {
    TStack<int> st(5);
    st.push(1);
    st.push(2);
    EXPECT_EQ(st.pop(), 2);
    EXPECT_EQ(st.pop(), 1);
}

TEST(TStack, throws_when_popping_from_empty_stack) {
    TStack<int> st(5);
    ASSERT_ANY_THROW(st.pop());
}

TEST(TStack, throws_when_pushing_to_full_stack) {
    TStack<int> st(2);
    st.push(1);
    st.push(2);
    ASSERT_ANY_THROW(st.push(3));
}

TEST(TStack, can_check_if_stack_is_empty) {
    TStack<int> st(5);
    EXPECT_TRUE(st.isEmpty());
    st.push(1);
    EXPECT_FALSE(st.isEmpty());
}

TEST(TStack, can_check_if_stack_is_full) {
    TStack<int> st(2);
    st.push(1);
    st.push(2);
    EXPECT_TRUE(st.isFull());
    st.pop();
    EXPECT_FALSE(st.isFull());
}

TEST(TStack, can_copy_stack) {
    TStack<int> st1(5);
    st1.push(1);
    st1.push(2);
    TStack<int> st2(st1);
    EXPECT_EQ(st2.pop(), 2);
    EXPECT_EQ(st2.pop(), 1);
}

TEST(TStack, can_compare_equal_stacks) {
    TStack<int> st1(5);
    TStack<int> st2(5);
    st1.push(10);
    st2.push(10);
    EXPECT_TRUE(st1 == st2);
}

TEST(TStack, can_compare_non_equal_stacks) {
    TStack<int> st1(5);
    TStack<int> st2(5);
    st1.push(1);
    st2.push(2);
    EXPECT_TRUE(st1 != st2);
}



TEST(TCalc, can_create_calc_with_default_constructor) {
    ASSERT_NO_THROW(TCalc calc);
}

TEST(TCalc, can_set_and_get_infix_expression) {
    TCalc calc;
    calc.setinfix("3+5");
    EXPECT_EQ(calc.getinfix(), "3+5");
}

TEST(TCalc, can_set_and_get_postfix_expression) {
    TCalc calc;
    calc.setpostfix("3 5 +");
    EXPECT_EQ(calc.getpostfix(), "3 5 +");
}

TEST(TCalc, can_convert_infix_to_postfix) {
    TCalc calc;
    calc.setinfix("3+5");
    calc.ToPostfix();
    EXPECT_EQ(calc.getpostfix(), "3 5 + ");
}

TEST(TCalc, can_convert_infix_to_postfix_with_unary_minus) {
    TCalc calc;
    calc.setinfix("(-3)+5");
    calc.ToPostfix();
    EXPECT_EQ(calc.getpostfix(), "-3 5 + ");
}

TEST(TCalc, can_convert_infix_to_postfix_with_doubles) {
    TCalc calc;
    calc.setinfix("1.1+2.2");
    calc.ToPostfix();
    EXPECT_EQ(calc.getpostfix(), "1.1 2.2 + ");
}
TEST(TCalc, throws_on_invalid_postfix_expression) {
    TCalc calc;
    calc.setpostfix("3 +");
    ASSERT_ANY_THROW(calc.CalcPostfix());
}


TEST(TCalc, can_convert_infix_to_postfix_with_long_numbers) {
    TCalc calc;
    calc.setinfix("122+10");
    calc.ToPostfix();
    EXPECT_EQ(calc.getpostfix(), "122 10 + ");
}

TEST(TCalc, can_calculate_postfix_with_unary_minus) {
    TCalc calc;
    calc.setpostfix("-3 5 +");
    EXPECT_EQ(calc.CalcPostfix(), 2);
}

TEST(TCalc, can_calculate_postfix_with_doubles) {
    TCalc calc;
    calc.setpostfix("1.1 2.2 +");
    EXPECT_EQ(calc.CalcPostfix(), 3.3);
}

TEST(TCalc, can_calculate_postfix_with_long_numbers) {
    TCalc calc;
    calc.setpostfix("122 23 +");
    EXPECT_EQ(calc.CalcPostfix(), 145);
}

TEST(TCalc, can_calculate_simple_postfix_expression) {
    TCalc calc;
    calc.setpostfix("3 5 +");
    EXPECT_EQ(calc.CalcPostfix(), 8);
}

TEST(TCalc, can_calculate_complex_postfix_expression) {
    TCalc calc;
    calc.setpostfix("3 5 + 2 * 4 /");
    EXPECT_EQ(calc.CalcPostfix(), 4);
}

TEST(TCalc, throws_when_dividing_by_zero_in_postfix) {
    TCalc calc;
    calc.setpostfix("3 0 /");
    ASSERT_ANY_THROW(calc.CalcPostfix());
}

TEST(TCalc, can_calculate_simple_infix_expression) {
    TCalc calc;
    calc.setinfix("3+5");
    EXPECT_EQ(calc.Calc(), 8);
}

TEST(TCalc, can_calculate_complex_infix_expression) {
    TCalc calc;
    calc.setinfix("(3+5)*2/4");
    EXPECT_EQ(calc.Calc(), 4);
}

TEST(TCalc, can_calculate_infix_with_unary_minus) {
    TCalc calc;
    calc.setinfix("(-3)+5");
    EXPECT_EQ(calc.Calc(), 2);
}

TEST(TCalc, can_calculate_infix_with_doubles) {
    TCalc calc;
    calc.setinfix("1.1+2.2");
    EXPECT_EQ(calc.Calc(), 3.3);
}

TEST(TCalc, can_calculate_infix_with_long_numbers) {
    TCalc calc;
    calc.setinfix("122+23");
    EXPECT_EQ(calc.Calc(), 145);
}

TEST(TCalc, throws_when_dividing_by_zero_in_infix) {
    TCalc calc;
    calc.setinfix("3/0");
    ASSERT_ANY_THROW(calc.Calc());
}

TEST(TCalc, throws_on_incorrect_infix_expression) {
    TCalc calc;
    calc.setinfix("3++5");
    ASSERT_ANY_THROW(calc.Calc());
}

TEST(TCalc, throws_on_incorrect_postfix_expression) {
    TCalc calc;
    calc.setpostfix("3 5 + +");
    ASSERT_ANY_THROW(calc.CalcPostfix());
}