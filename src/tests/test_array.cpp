#include <gtest/gtest.h>

#include "../lib/s21_array.h"

s21::Array<int, 0> s21_array_empty;
s21::Array<char, 5> s21_array_init{'a', 'b', 'c', 'd'};
s21::Array<int, 5> s21_array_for_copy{1, 2, 3, 4, 5};
s21::Array<int, 5> s21_array_for_swap_1{12, 23, 23, 435, -51};
s21::Array<int, 5> s21_array_for_swap_2{423423, 234, 623, 12, 1};

std::array<int, 0> std_array_empty;
std::array<char, 5> std_array_init{'a', 'b', 'c', 'd'};
std::array<int, 5> std_array_for_copy{1, 2, 3, 4, 5};
std::array<int, 5> std_array_for_swap_1{12, 23, 23, 435, -51};
std::array<int, 5> std_array_for_swap_2{423423, 234, 623, 12, 1};

TEST(s21ArrayTest, DefaultConstructor) {
  EXPECT_EQ(s21_array_empty.size(), std_array_empty.size());
  EXPECT_EQ(s21_array_empty.empty(), std_array_empty.empty());
}

TEST(s21ArrayTest, InitializerListConstructor) {
  EXPECT_EQ(s21_array_init.size(), std_array_init.size());
  EXPECT_EQ(s21_array_init.front(), std_array_init.front());
  EXPECT_EQ(s21_array_init.back(), std_array_init.back());
  for (size_t i = 0; i < s21_array_init.size(); i++) {
    EXPECT_EQ(s21_array_init[i], std_array_init[i]);
  }
  try {
    s21::Array<int, 5> arr{1, 2, 3, 4, 5, 6};
    FAIL() << "Expected std::out_of_range exception";
  } catch (const std::out_of_range &ex) {
    SUCCEED();
  } catch (...) {
    FAIL() << "Unexpected exception";
  }
}

TEST(s21ArrayTest, CopyConstructor) {
  s21::Array<int, 5> s21_array(s21_array_for_copy);
  std::array<int, 5> std_array(std_array_for_copy);

  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.front(), std_array.front());
  EXPECT_EQ(s21_array.back(), std_array.back());
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(s21ArrayTest, AssignmentOperatorCopying) {
  s21::Array<int, 5> s21_array;
  s21_array = s21_array_for_copy;
  std::array<int, 5> std_array;
  std_array = std_array_for_copy;

  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.front(), std_array.front());
  EXPECT_EQ(s21_array.back(), std_array.back());
  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(s21ArrayTest, MoveConstructor) {
  s21::Array<int, 5> s21_array(std::move(s21_array_for_copy));
  std::array<int, 5> std_array(std::move(std_array_for_copy));

  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.front(), std_array.front());
  EXPECT_EQ(s21_array.back(), std_array.back());
  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(s21ArrayTest, AssignmentOperatorMoving) {
  s21::Array<int, 5> s21_array;
  s21_array = std::move(s21_array_for_copy);
  std::array<int, 5> std_array;
  std_array = std::move(std_array_for_copy);

  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.front(), std_array.front());
  EXPECT_EQ(s21_array.back(), std_array.back());
  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(s21ArrayTest, Swap) {
  s21_array_for_swap_1.swap(s21_array_for_swap_2);
  std_array_for_swap_1.swap(std_array_for_swap_2);

  EXPECT_EQ(s21_array_for_swap_1.size(), std_array_for_swap_1.size());
  EXPECT_EQ(s21_array_for_swap_1.front(), std_array_for_swap_1.front());
  EXPECT_EQ(s21_array_for_swap_1.back(), std_array_for_swap_1.back());
  for (size_t i = 0; i < s21_array_for_swap_1.size(); i++) {
    EXPECT_EQ(s21_array_for_swap_1[i], std_array_for_swap_1[i]);
  }

  EXPECT_EQ(s21_array_for_swap_2.size(), std_array_for_swap_2.size());
  EXPECT_EQ(s21_array_for_swap_2.front(), std_array_for_swap_2.front());
  EXPECT_EQ(s21_array_for_swap_2.back(), std_array_for_swap_2.back());
  for (size_t i = 0; i < s21_array_for_swap_2.size(); i++) {
    EXPECT_EQ(s21_array_for_swap_2[i], std_array_for_swap_2[i]);
  }
}

TEST(s21ArrayTest, Fill) {
  s21_array_init.fill('o');
  std_array_init.fill('o');

  EXPECT_EQ(s21_array_init.size(), std_array_init.size());
  EXPECT_EQ(s21_array_init.front(), std_array_init.front());
  EXPECT_EQ(s21_array_init.back(), std_array_init.back());
  for (size_t i = 0; i < s21_array_init.size(); i++) {
    EXPECT_EQ(s21_array_init[i], std_array_init[i]);
  }
}

TEST(s21ArrayTest, Iterators) {
  char *s21_begin = s21_array_init.begin();
  char *std_begin = std_array_init.begin();
  char *s21_end = s21_array_init.end();
  char *std_end = std_array_init.end();

  while (s21_begin < s21_end && std_begin < std_end) {
    EXPECT_EQ(*s21_begin++, *std_begin++);
  }

  EXPECT_EQ(s21_array_empty.begin(), s21_array_empty.end());
  EXPECT_EQ(*s21_array_init.data(), s21_array_init[0]);
}

TEST(s21ArrayTest, At) {
  EXPECT_EQ(s21_array_init.at(0), s21_array_init[0]);
  s21_array_init.at(0) = 'c';
  EXPECT_EQ(s21_array_init.at(0), 'c');

  EXPECT_THROW(s21_array_init.at(-1) = 4, std::out_of_range);
  EXPECT_THROW(s21_array_init.at(s21_array_init.size() + 10) = 4,
               std::out_of_range);
}