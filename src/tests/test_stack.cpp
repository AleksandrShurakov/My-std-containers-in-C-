#include <gtest/gtest.h>

#include "../lib/s21_stack.h"

TEST(StackTest, DefaultConstructor) {
  s21::Stack<int> a;
  EXPECT_EQ(a.empty(), 1);
}

TEST(StackTest, InitializerListConstructor) {
  s21::Stack<int> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.top(), 5);
}

TEST(StackTest, CopyConstructor) {
  s21::Stack<int> a{1, 2, 3};
  s21::Stack<int> b(a);
  EXPECT_EQ(b.size(), a.size());
  EXPECT_EQ(a.top(), b.top());
}

TEST(StackTest, MoveConstructor) {
  s21::Stack<int> a{1, 2, 3};
  s21::Stack<int> b(std::move(a));
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.top(), 3);
  EXPECT_ANY_THROW(a.top());
}

TEST(StackTest, operator_equal) {
  s21::Stack<int> a{1, 2, 3};
  s21::Stack<int> b = std::move(a);
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.top(), 3);
  EXPECT_ANY_THROW(a.top());
}

TEST(StackTest, push) {
  s21::Stack<int> a{1, 2, 3};
  a.push(4);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.top(), 4);
}

TEST(StackTest, pop) {
  s21::Stack<int> a{1, 2, 3};
  s21::Stack<int> empty;
  a.pop();
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.top(), 2);
  EXPECT_ANY_THROW(empty.pop());
}

TEST(StackTest, swap) {
  s21::Stack<int> a{1, 2, 3};
  s21::Stack<int> b{11, 12, 13};
  a.swap(b);
  EXPECT_EQ(a.top(), 13);
  EXPECT_EQ(b.top(), 3);
}

TEST(StackTest, insert_many_front) {
  s21::Stack<int> a{4, 5};
  a.insert_many_front(1, 2, 3);
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.top(), 3);
}