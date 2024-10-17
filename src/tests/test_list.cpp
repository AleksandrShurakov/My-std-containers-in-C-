#include <gtest/gtest.h>

#include "../lib/s21_list.h"

TEST(ListTest, DefaultConstructor) {
  s21::List<int> a;
  s21::List<char> b;
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 0);
}

TEST(ListTest, CustomConstructor) {
  s21::List<int> a(10);
  EXPECT_EQ(a.size(), 10);
  EXPECT_EQ(a.front(), 0);
}

TEST(ListTest, InitializerListConstructor) {
  s21::List<int> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 5);
}

TEST(ListTest, CopyConstructor) {
  s21::List<int> list_for_copy{1, 2, 3, 4, 5};
  s21::List<int> target_list(list_for_copy);
  s21::List<int>::ListIterator copy_iter(list_for_copy.begin());
  EXPECT_EQ(target_list.size(), list_for_copy.size());
  for (int item : target_list) {
    EXPECT_EQ(item, *copy_iter);
    ++copy_iter;
  }
}

TEST(ListTest, MoveConstructor) {
  s21::List<int> list_for_move{1, 2, 3, 4, 5};
  s21::List<int> target_list(std::move(list_for_move));
  EXPECT_EQ(target_list.size(), 5);
  EXPECT_EQ(list_for_move.size(), 0);
  int i = 1;
  for (int item : target_list) {
    EXPECT_EQ(item, i);
    i++;
  }
}

TEST(ListTest, operator_equal) {
  s21::List<int> list1{10, 11, 12, 13, 14, 15};
  s21::List<int> list2{0, 1, 2, 3, 4};
  list1 = std::move(list2);
  EXPECT_EQ(list2.size(), 0);
  EXPECT_EQ(list1.size(), 5);
  int i = 0;
  for (int item : list1) {
    EXPECT_EQ(item, i);
    i++;
  }
}

TEST(ListTest, insert) {
  s21::List<int> list1{1, 3, 4, 5};
  s21::List<int>::ListIterator it(list1.begin());
  ++it;
  list1.insert(it, 2);
  int i = 1;
  for (int item : list1) {
    EXPECT_EQ(item, i);
    i++;
  }
}

TEST(ListTest, erase) {
  s21::List<int> list1{1, 2, 2, 3, 4, 5};
  s21::List<int>::ListIterator it(list1.begin());
  ++it;
  list1.erase(it);
  int i = 1;
  for (int item : list1) {
    EXPECT_EQ(item, i);
    i++;
  }
}

TEST(ListTest, push_back) {
  s21::List<int> list{1, 2, 3, 4};
  list.push_back(5);
  int i = 1;
  for (int item : list) {
    EXPECT_EQ(item, i);
    i++;
  }
}

TEST(ListTest, pop_back) {
  s21::List<int> list{1, 2, 3, 4};
  s21::List<int> ex_list;
  list.pop_back();
  int i = 1;
  for (int item : list) {
    EXPECT_EQ(item, i);
    i++;
  }
  EXPECT_ANY_THROW(ex_list.pop_back());
}

TEST(ListTest, push_front) {
  s21::List<int> list{2, 3, 4, 5};
  list.push_front(1);
  int i = 1;
  for (int item : list) {
    EXPECT_EQ(item, i);
    i++;
  }
}

TEST(ListTest, pop_front) {
  s21::List<int> list{1, 1, 2, 3, 4, 5};
  s21::List<int> ex_list;
  list.pop_front();
  int i = 1;
  for (int item : list) {
    EXPECT_EQ(item, i);
    i++;
  }
  EXPECT_ANY_THROW(ex_list.pop_front());
}

TEST(ListTest, splice) {
  s21::List<int> list1{1, 2, 5};
  s21::List<int> list2{3, 4};
  s21::List<int>::ListConstIterator it(list1.begin());
  ++it;
  ++it;
  list1.splice(it, list2);
  int i = 1;
  for (int item : list1) {
    EXPECT_EQ(item, i);
    i++;
  }
}

TEST(ListTest, reverse) {
  s21::List<int> list{5, 4, 3, 2, 1};
  list.reverse();
  int i = 1;
  for (int item : list) {
    EXPECT_EQ(item, i);
    i++;
  }
}

TEST(ListTest, unique) {
  s21::List<int> list{1, 1, 1, 2, 3, 3, 4, 5, 5, 5};
  list.unique();
  int i = 1;
  for (int item : list) {
    EXPECT_EQ(item, i);
    i++;
  }
}

TEST(ListTest, sort) {
  s21::List<int> l1{27, 0, 16, -1, 3, 1};
  l1.sort();

  EXPECT_EQ(l1.size(), 6);
  s21::List<int>::iterator iter = l1.begin();
  EXPECT_EQ(*iter, -1);
  ++iter;
  EXPECT_EQ(*iter, 0);
  ++iter;
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 16);
  ++iter;
  EXPECT_EQ(*iter, 27);

  s21::List<int> l2{27};
  l2.sort();
  EXPECT_EQ(l2.size(), 1);
  EXPECT_EQ(l2.front(), 27);

  s21::List<int> l3;
  l3.sort();
  EXPECT_EQ(l3.size(), 0);
  EXPECT_ANY_THROW(l3.front());
}

TEST(ListTest, merge) {
  s21::List<int> list0;
  s21::List<int> list1{3, 2, 4};
  s21::List<int> list2{1, 6, 7, 5};
  list1.merge(list2);
  list0.merge(list1);
  int i = 1;
  for (int item : list0) {
    EXPECT_EQ(item, i);
    i++;
  }
}

TEST(ListTest, insert_many) {
  s21::List<int> list{1, 2, 3};
  s21::List<int>::iterator iter(list.begin());
  list.insert_many(iter, 4, 5);
  iter = list.begin();
  EXPECT_EQ(list.size(), 5);
  EXPECT_EQ(*iter, 4);
  ++iter;
  EXPECT_EQ(*iter, 5);
  ++iter;
  EXPECT_EQ(*iter, 1);

  s21::List<int> list2{1, 2, 3};
  iter = list2.end();
  list2.insert_many(iter, 4, 5);
  iter = list2.begin();
  EXPECT_EQ(list2.size(), 5);
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

TEST(ListTest, insert_many_back) {
  s21::List<int> list{1, 2, 3};
  s21::List<int>::iterator iter(list.begin());
  list.insert_many_back(4, 5);
  EXPECT_EQ(list.size(), 5);
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

TEST(ListTest, insert_many_front) {
  s21::List<int> list{4, 5};
  list.insert_many_front(1, 2, 3);
  s21::List<int>::iterator iter(list.begin());
  EXPECT_EQ(list.size(), 5);
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
