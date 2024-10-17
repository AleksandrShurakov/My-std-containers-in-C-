#include <gtest/gtest.h>

#include "../lib/s21_vector.h"

TEST(VectorTest, constructor_default_size) {
  s21::Vector<char> test_vector;
  std::vector<char> std_test_vector;
  EXPECT_EQ(std_test_vector.size(), test_vector.size());
}

TEST(VectorTest, constructor_default_capacity) {
  s21::Vector<char> test_vector;
  std::vector<char> std_test_vector;
  EXPECT_EQ(std_test_vector.capacity(), test_vector.capacity());
}

TEST(VectorTest, constructor_default_capacity_1) {
  s21::Vector<char> test_vector;
  std::vector<char> std_test_vector;
  test_vector.push_back(1);
  std_test_vector.push_back(1);
  EXPECT_EQ(std_test_vector.capacity(), test_vector.capacity());
}

TEST(VectorTest, constructor_parametrized) {
  s21::Vector<int> test_vector(5);
  std::vector<int> std_test_vector(5);
  EXPECT_EQ(std_test_vector.size(), test_vector.size());
}

TEST(VectorTest, constructor_initializer_list) {
  std::initializer_list<int> il1{1, 2, 3, 4, 5};
  s21::Vector<int> test_vector(il1);
  std::vector<int> std_test_vector(il1);
  EXPECT_EQ(test_vector.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector.at(2), std_test_vector.at(2));
  EXPECT_EQ(test_vector.at(3), std_test_vector.at(3));
  EXPECT_EQ(test_vector.at(4), std_test_vector.at(4));
}

TEST(VectorTest, constructor_copy) {
  std::initializer_list<int> il1{1, 2, 3, 4, 5};
  s21::Vector<int> test_vector(il1);
  s21::Vector<int> copy_vector(test_vector);
  std::vector<int> std_test_vector(il1);
  std::vector<int> std_copy_vector(std_test_vector);
  EXPECT_EQ(copy_vector.at(0), std_copy_vector.at(0));
  EXPECT_EQ(copy_vector.at(1), std_copy_vector.at(1));
  EXPECT_EQ(copy_vector.at(2), std_copy_vector.at(2));
  EXPECT_EQ(copy_vector.at(3), std_copy_vector.at(3));
  EXPECT_EQ(copy_vector.at(4), std_copy_vector.at(4));
}

TEST(VectorTest, constructor_move) {
  std::initializer_list<int> il1{1, 2, 3, 4, 5};
  s21::Vector<int> test_vector(il1);
  s21::Vector<int> copy_vector(std::move(test_vector));
  std::vector<int> std_test_vector(il1);
  std::vector<int> std_copy_vector(std::move(std_test_vector));
  EXPECT_EQ(copy_vector.at(0), std_copy_vector.at(0));
  EXPECT_EQ(copy_vector.at(1), std_copy_vector.at(1));
  EXPECT_EQ(copy_vector.at(2), std_copy_vector.at(2));
  EXPECT_EQ(copy_vector.at(3), std_copy_vector.at(3));
  EXPECT_EQ(copy_vector.at(4), std_copy_vector.at(4));
}

TEST(VectorTest, constructor_operator) {
  s21::Vector<int> test_vector_1{1, 2, 3, 4, 5};
  s21::Vector<int> test_vector_2;
  test_vector_2 = std::move(test_vector_1);
  std::vector<int> std_test_vector = {1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector_2.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector_2.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector_2.at(2), std_test_vector.at(2));
  EXPECT_EQ(test_vector_2.at(3), std_test_vector.at(3));
  EXPECT_EQ(test_vector_2.at(4), std_test_vector.at(4));
}

TEST(VectorTest, at_func) {
  s21::Vector<size_t> test_vector{1, 2, 3, 4, 5};
  std::vector<size_t> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector.at(2), std_test_vector.at(2));
  EXPECT_EQ(test_vector.at(3), std_test_vector.at(3));
  EXPECT_EQ(test_vector.at(4), std_test_vector.at(4));
}

TEST(VectorTest, at_func_throw) {
  s21::Vector<int> test_vector;
  EXPECT_ANY_THROW(test_vector.at(1));
}

TEST(VectorTest, square_brackets_operator) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector.at(2), std_test_vector.at(2));
  EXPECT_EQ(test_vector.at(3), std_test_vector.at(3));
  EXPECT_EQ(test_vector.at(4), std_test_vector.at(4));
}

TEST(VectorTest, front_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.front(), std_test_vector.front());
}

TEST(VectorTest, back_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.back(), std_test_vector.back());
}

TEST(VectorTest, data_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(*test_vector.data(), *std_test_vector.data());
}

TEST(VectorTest, empty) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;
  EXPECT_EQ(test_vector.empty(), std_test_vector.empty());
}

TEST(VectorTest, size_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.size(), std_test_vector.size());
}

TEST(VectorTest, max_size_func) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;

  EXPECT_EQ(test_vector.max_size(), std_test_vector.max_size());
}

TEST(VectorTest, reserve_func) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;
  test_vector.reserve(10);
  std_test_vector.reserve(10);
  EXPECT_EQ(test_vector.capacity(), std_test_vector.capacity());
}

TEST(VectorTest, reserve_func_1) {
  s21::Vector<int> test_vector(10);
  std::vector<int> std_test_vector(10);
  test_vector.reserve(2);
  std_test_vector.reserve(2);
  EXPECT_EQ(test_vector.capacity(), std_test_vector.capacity());
}

TEST(VectorTest, reserve_func_except) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;
  EXPECT_THROW(test_vector.reserve(2305843009213693952), std::length_error);
  EXPECT_THROW(std_test_vector.reserve(2305843009213693952), std::length_error);
}

TEST(VectorTest, capacity_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.capacity(), std_test_vector.capacity());
}

TEST(VectorTest, shrink_to_fit_func) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;
  test_vector.reserve(10);
  std_test_vector.reserve(10);
  test_vector.shrink_to_fit();
  std_test_vector.shrink_to_fit();
  EXPECT_EQ(test_vector.capacity(), std_test_vector.capacity());
}

TEST(VectorTest, clear_func) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;
  test_vector.clear();
  std_test_vector.clear();
  EXPECT_EQ(test_vector.size(), std_test_vector.size());
}

TEST(VectorTest, insert_func) {
  s21::Vector<int> test_vector{1, 2, 3};
  std::vector<int> std_test_vector{1, 2, 3};
  test_vector.insert(test_vector.begin() + 1, 5);
  std_test_vector.insert(std_test_vector.begin() + 1, 5);

  EXPECT_EQ(test_vector.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector.at(2), std_test_vector.at(2));
}

TEST(VectorTest, erase_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4};
  std::vector<int> std_test_vector{1, 2, 3, 4};

  test_vector.erase(test_vector.begin() + 1);
  std_test_vector.erase(std_test_vector.begin() + 1);

  EXPECT_EQ(test_vector.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector.at(2), std_test_vector.at(2));
}

TEST(VectorTest, push_back_func) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;

  test_vector.push_back(2);
  test_vector.push_back(3);
  test_vector.push_back(4);
  test_vector.push_back(5);

  std_test_vector.push_back(2);
  std_test_vector.push_back(3);
  std_test_vector.push_back(4);
  std_test_vector.push_back(5);

  EXPECT_EQ(test_vector.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector.at(2), std_test_vector.at(2));
  EXPECT_EQ(test_vector.at(3), std_test_vector.at(3));
}

TEST(VectorTest, pop_back_func) {
  s21::Vector<int> test_vector{1, 2};

  test_vector.pop_back();
  test_vector.pop_back();
  test_vector.pop_back();
  test_vector.pop_back();

  EXPECT_EQ(test_vector.size(), 0);
  EXPECT_EQ(test_vector.capacity(), 2);
}

TEST(VectorTest, swap_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  s21::Vector<int> test_vector_copy{1, 2, 3};

  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector_copy{1, 2, 3};

  test_vector_copy.swap(test_vector);
  std_test_vector_copy.swap(std_test_vector);

  EXPECT_EQ(test_vector.size(), std_test_vector.size());
  EXPECT_EQ(test_vector.capacity(), std_test_vector.capacity());

  EXPECT_EQ(test_vector_copy.size(), std_test_vector_copy.size());
  EXPECT_EQ(test_vector_copy.capacity(), std_test_vector_copy.capacity());
}

TEST(VectorTest, iterator_operator_minus_minus) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(2)--, std_test_vector.at(2)--);
}
TEST(VectorTest, iterator_operator_plus_plus) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(1)++, std_test_vector.at(1)++);
}
TEST(VectorTest, iterator_operator_plus) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(0) + test_vector.at(1),
            std_test_vector.at(0) + std_test_vector.at(1));
}
TEST(VectorTest, iterator_operator_minus) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(2) - test_vector.at(1),
            std_test_vector.at(2) - std_test_vector.at(1));
}
TEST(VectorTest, iterator_operator_eq) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(4) == std_test_vector.at(4), 1);
}
TEST(VectorTest, iterator_operator_not_eq) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(3) != std_test_vector.at(4), 1);
}

TEST(VectorTest, insert_many) {
  s21::Vector<int> vector{1, 2, 3};
  s21::Vector<int>::iterator iter(vector.begin());
  vector.insert_many(iter, 4, 5);
  EXPECT_EQ(vector.size(), 5);
  iter = vector.begin();
  EXPECT_EQ(*iter, 4);
  ++iter;
  EXPECT_EQ(*iter, 5);
  ++iter;
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
}

TEST(VectorTest, insert_many_back) {
  s21::Vector<int> vector{1, 2, 3};
  vector.insert_many_back(4, 5);
  s21::Vector<int>::iterator iter(vector.begin());
  EXPECT_EQ(vector.size(), 5);
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 4);
  ++iter;
  EXPECT_EQ(*iter, 5);
}