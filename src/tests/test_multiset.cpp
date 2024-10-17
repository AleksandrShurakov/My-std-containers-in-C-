#include <gtest/gtest.h>

#include "../lib/s21_multiset.h"

TEST(MultisetTest, DefaultConstructor) {
  s21::Multiset<int> a;
  std::multiset<int> b;
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(MultisetTest, InitializerListConstructor) {
  s21::Multiset<int> a{1, 2, 3, 4, 5};
  std::multiset<int> b{1, 2, 3, 4, 5};
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTest, Insert) {
  s21::Multiset<int> a{1, 2, 3, 4, 5};
  a.insert(1);
  EXPECT_EQ(a.size(), 6);
}

TEST(MultisetTest, CopyConstructor) {
  s21::Multiset<int> a{1, 2, 3, 4, 5};
  s21::Multiset<int> b(a);
  EXPECT_EQ(b.size(), 5);
}

TEST(MultisetTest, MoveConstructor) {
  s21::Multiset<int> a{1, 1, 2, 3, 4, 5};
  s21::Multiset<int> b(std::move(a));
  std::multiset<int> c{1, 1, 2, 3, 4, 5};
  std::multiset<int> d(std::move(c));

  EXPECT_EQ(b.size(), d.size());
}

TEST(MultisetTest, copy_asignment) {
  s21::Multiset<int> a{1, 2, 3, 4, 5};
  s21::Multiset<int> b;
  std::multiset<int> c{1, 2, 3, 4, 5};
  std::multiset<int> d;
  b = a;
  d = c;
  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(b.size(), d.size());
}

TEST(MultisetTest, move_asignment) {
  s21::Multiset<int> a{1, 2};
  s21::Multiset<int> b{3, 4, 5};
  a = std::move(b);
  std::multiset<int> c{1, 2};
  std::multiset<int> d{3, 4, 5};
  c = std::move(d);
  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(b.size(), d.size());
}

TEST(MultisetTest, begin) {
  s21::Multiset<int> a{1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9};
  std::multiset<int> b{1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 9};
  s21::Multiset<int>::iterator it = a.begin();
  std::multiset<int>::iterator set_it = b.begin();
  EXPECT_EQ(*(set_it), (*(it)));
}

TEST(MultisetTest, iterators) {
  s21::Multiset<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::multiset<int> b{1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::Multiset<int>::iterator it = a.begin();
  std::multiset<int>::iterator set_it = b.begin();
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), (*(it)));

  --it;
  --set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), (*(it)));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), (*(it)));
}
TEST(MultisetTest, swap) {
  s21::Multiset<int> a{1, 2, 3, 4, 5, 6, 7};
  s21::Multiset<int> b;
  std::multiset<int> c{1, 2, 3, 4, 5, 6, 7};
  std::multiset<int> d;
  a.swap(b);
  c.swap(d);
  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(b.size(), d.size());
}

TEST(MultisetTest, merge) {
  s21::Multiset<int> a{1, 2, 3, 4, 5, 6, 7};
  s21::Multiset<int> b{1, 2, 3, 4, 5, 6, 7};
  a.merge(b);
  std::multiset<int> c{1, 2, 3, 4, 5, 6, 7};
  std::multiset<int> d{1, 2, 3, 4, 5, 6, 7};
  c.merge(d);
  s21::Multiset<int>::iterator it = a.begin();
  EXPECT_EQ(it.iterated_node_->key_.second, 2);
  ++it;
  EXPECT_EQ(it.iterated_node_->key_.second, 2);
  EXPECT_EQ(a.size(), c.size());
}

TEST(MultisetTest, lower_bound) {
  s21::Multiset<int> a{1, 2, 3, 3, 5, 6, 7, 7};
  std::multiset<int> b{1, 2, 3, 3, 5, 6, 7, 7};
  EXPECT_EQ(*(b.lower_bound(-1045)), *(a.lower_bound(-1045)));
  EXPECT_EQ(*(a.lower_bound(3)), *(b.lower_bound(3)));
  EXPECT_EQ(*(a.lower_bound(5)), *(b.lower_bound(5)));
  EXPECT_EQ(*(a.lower_bound(7)), *(b.lower_bound(7)));
}

TEST(MultisetTest, upper_bound) {
  s21::Multiset<int> a{1, 2, 3, 3, 5, 6, 7, 7};
  std::multiset<int> b{1, 2, 3, 3, 5, 6, 7, 7};
  EXPECT_EQ(*(b.upper_bound(-1045)), *(a.upper_bound(-1045)));

  EXPECT_EQ(*(a.upper_bound(3)), *(b.upper_bound(3)));
  EXPECT_EQ(*(a.upper_bound(5)), *(b.upper_bound(5)));
  EXPECT_EQ(*(a.upper_bound(7)), 0);
}

TEST(MultisetTest, equal_range) {
  s21::Multiset<int> a{1, 1, 1, 1, 2, 3, 4, 5, 6, 6, 7, 7, 7};
  std::multiset<int> b{1, 1, 1, 1, 2, 3, 4, 5, 6, 6, 7, 7, 7};

  EXPECT_EQ(*(a.equal_range(5).first), *(b.equal_range(5).first));
  EXPECT_EQ(*(a.equal_range(6).first), *(b.equal_range(6).first));
  EXPECT_EQ(*(a.equal_range(1).first), *(b.equal_range(1).first));
  EXPECT_EQ(*(a.equal_range(7).first), *(b.equal_range(7).first));
}

TEST(MultisetTest, find) {
  s21::Multiset<int> a{1, 2, 3, 4, 5, 6, 7};
  std::multiset<int> b{1, 2, 3, 4, 5, 6, 7};

  EXPECT_EQ((*(a.find(5))), *(b.find(5)));
}

TEST(MultisetTest, erase) {
  s21::Multiset<int> a{1, 1, 2, 3};
  s21::Multiset<int>::iterator iter(a.begin());
  a.erase(iter);
  std::multiset<int> b{1, 1, 2, 3};
  std::multiset<int>::iterator mul_iter = b.begin();
  b.erase(mul_iter);
  EXPECT_EQ(a.size(), b.size());
}

TEST(MultisetTest, insert_many) {
  s21::Multiset<int> a{1, 2, 3};
  a.insert_many(1, 4, 5);
  s21::Multiset<int>::iterator iter(a.begin());
  EXPECT_EQ(a.size(), 6);
  EXPECT_EQ(iter.iterated_node_->key_.second, 2);
  ++iter;
  ++iter;
  EXPECT_EQ(iter.iterated_node_->key_.second, 1);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}