#include <gtest/gtest.h>

#include "../lib/s21_queue.h"

TEST(QueueTest, DefaultConstructor) {
  s21::Queue<int> a;
  EXPECT_EQ(a.empty(), 1);
}

TEST(QueueTest, InitializerListConstructor) {
  s21::Queue<int> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 5);
}

TEST(QueueTest, CopyConstructor) {
  s21::Queue<int> a{1, 2, 3};
  s21::Queue<int> b(a);
  EXPECT_EQ(b.size(), a.size());
  EXPECT_EQ(a.front(), b.front());
  EXPECT_EQ(a.back(), b.back());
}

TEST(QueueTest, MoveConstructor) {
  s21::Queue<int> a{1, 2, 3};
  s21::Queue<int> b(std::move(a));
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.front(), 1);
  EXPECT_EQ(b.back(), 3);
  EXPECT_ANY_THROW(a.back());
  EXPECT_ANY_THROW(a.front());
}

TEST(QueueTest, operator_equal) {
  s21::Queue<int> a{1, 2, 3};
  s21::Queue<int> b = std::move(a);
  EXPECT_EQ(b.size(), 3);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.front(), 1);
  EXPECT_EQ(b.back(), 3);
  EXPECT_ANY_THROW(a.back());
  EXPECT_ANY_THROW(a.front());
}

TEST(QueueTest, push) {
  s21::Queue<int> a{1, 2, 3};
  a.push(4);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 4);
}

TEST(QueueTest, pop) {
  s21::Queue<int> a{1, 2, 3};
  s21::Queue<int> empty;
  a.pop();
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.front(), 2);
  EXPECT_EQ(a.back(), 3);
  EXPECT_ANY_THROW(empty.pop());
}

TEST(QueueTest, swap) {
  s21::Queue<int> a{1, 2, 3};
  s21::Queue<int> b{11, 12, 13};
  a.swap(b);
  EXPECT_EQ(a.front(), 11);
  EXPECT_EQ(a.back(), 13);
  EXPECT_EQ(b.front(), 1);
  EXPECT_EQ(b.back(), 3);
}

TEST(QueueTest, insert_many_back) {
  s21::Queue<int> a{1, 2, 3};
  a.insert_many_back(4, 5);
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.back(), 5);
  EXPECT_EQ(a.front(), 1);
}