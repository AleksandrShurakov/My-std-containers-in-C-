#include <gtest/gtest.h>

#include "../lib/s21_set.h"

TEST(SetTest, DefaultConstructor) {
  s21::Set<int> a;
  std::set<int> b;
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(SetTest, InitializerListConstructor) {
  s21::Set<int> a{1, 2, 3, 4, 5};
  std::set<int> b{1, 2, 3, 4, 5};
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, CopyConstructor) {
  s21::Set<int> a{1, 2, 3, 4, 5};
  s21::Set<int> b(a);
  EXPECT_EQ(b.size(), 5);
}

TEST(SetTest, MoveConstructor) {
  s21::Set<int> a{1, 2, 3, 4, 5};
  s21::Set<int> b(std::move(a));
  std::set<int> c{1, 2, 3, 4, 5};
  std::set<int> d(std::move(c));

  EXPECT_EQ(b.size(), d.size());
}

TEST(SetTest, copy_asignment) {
  s21::Set<int> a{1, 2, 3, 4, 5};
  s21::Set<int> b;
  std::set<int> c{1, 2, 3, 4, 5};
  std::set<int> d;
  b = a;
  d = c;
  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(b.size(), d.size());
}

TEST(SetTest, move_asignment) {
  s21::Set<int> a{1, 2};
  s21::Set<int> b{3, 4, 5};
  a = std::move(b);
  std::set<int> c{1, 2};
  std::set<int> d{3, 4, 5};
  c = std::move(d);
  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(b.size(), d.size());
}

TEST(SetTest, begin) {
  s21::Set<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::set<int> b{1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::Set<int>::iterator it = a.begin();
  std::set<int>::iterator set_it = b.begin();
  EXPECT_EQ(*(set_it), ((*(it)).first));
}

TEST(SetTest, iterators) {
  s21::Set<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::set<int> b{1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::Set<int>::iterator it = a.begin();
  std::set<int>::iterator set_it = b.begin();
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  ++it;
  ++set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));

  --it;
  --set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
  --it;
  --set_it;
  EXPECT_EQ(*(set_it), ((*(it)).first));
}

TEST(SetTest, erase) {
  s21::Set<int> a{1, 2, 3, 4, 5, 6, 7};
  std::set<int> b{1, 2, 3, 4, 5, 6, 7};
  a.erase(a.begin());
  b.erase(b.begin());
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, swap) {
  s21::Set<int> a{1, 2, 3, 4, 5, 6, 7};
  s21::Set<int> b;
  std::set<int> c{1, 2, 3, 4, 5, 6, 7};
  std::set<int> d;
  a.swap(b);
  c.swap(d);
  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(b.size(), d.size());
}

TEST(SetTest, insert) {
  s21::Set<int> a{1, 2, 3, 4, 5, 6, 7};
  std::set<int> b{1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ((a.insert(0)).second, (b.insert(0)).second);
  EXPECT_EQ((a.insert(1)).second, (b.insert(1)).second);
  EXPECT_EQ(a.size(), b.size());
}

TEST(SetTest, merge) {
  s21::Set<int> a{1, 2, 3, 4, 5, 6, 7};
  s21::Set<int> b{1, 2, 3, 4, 5, 6, 7};
  a.merge(b);
  std::set<int> c{1, 2, 3, 4, 5, 6, 7};
  std::set<int> d{1, 2, 3, 4, 5, 6, 7};
  c.merge(d);
  EXPECT_EQ(a.size(), c.size());
}

TEST(SetTest, find) {
  s21::Set<int> a{1, 2, 3, 4, 5, 6, 7};
  std::set<int> b{1, 2, 3, 4, 5, 6, 7};

  EXPECT_EQ((*(a.find(5))).first, *(b.find(5)));
}

TEST(SetTest, insert_many) {
  s21::Set<int> a{1, 2};
  a.insert_many(3, 4, 5);
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.contains(3), 1);
  EXPECT_EQ(a.contains(4), 1);
  EXPECT_EQ(a.contains(5), 1);
}