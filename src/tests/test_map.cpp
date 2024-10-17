#include <gtest/gtest.h>

#include "../lib/s21_map.h"

TEST(MapTest, DefaultConstructor) {
  s21::Map<int, int> a;
  std::map<int, int> b;
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(MapTest, InitializerListConstructor) {
  s21::Map<int, int> a{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> b{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.at(2), b.at(2));
  EXPECT_EQ(a[1], b[1]);
}

TEST(MapTest, CopyConstructor) {
  s21::Map<int, int> a{{1, 1}, {2, 2}};
  s21::Map<int, int> b(a);
  EXPECT_EQ(b.size(), 2);
}

TEST(MapTest, MoveConstructor) {
  s21::Map<int, int> a{{1, 1}, {2, 2}};
  s21::Map<int, int> b(std::move(a));
  EXPECT_EQ(b.size(), 2);
  EXPECT_EQ(a.size(), 0);
}

TEST(MapTest, copy_asignment) {
  s21::Map<int, int> a{{1, 1}, {2, 2}};
  s21::Map<int, int> b{{3, 3}, {4, 4}, {5, 5}};
  a = b;
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, move_asignment) {
  s21::Map<int, int> a{{1, 1}, {2, 2}};
  s21::Map<int, int> b{{3, 3}, {4, 4}, {5, 5}};
  a = std::move(b);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 0);
}

TEST(MapTest, at) {
  s21::Map<int, int> a{{1, 68}, {2, 78}};
  std::map<int, int> b{{1, 68}, {2, 78}};
  EXPECT_EQ(a.at(1), b.at(1));
  EXPECT_ANY_THROW(a.at(3));
}

TEST(MapTest, operator_brackets) {
  s21::Map<int, int> a{{1, 68}, {2, 78}};
  std::map<int, int> b{{1, 68}, {2, 78}};
  EXPECT_EQ(a[1], b[1]);
  EXPECT_EQ(a.contains(2), 1);
  EXPECT_EQ(a[3], b[3]);
  EXPECT_EQ(a.size(), b.size());
}

TEST(MapTest, begin) {
  s21::Map<int, int> a{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
                       {6, 6}, {7, 7}, {8, 8}, {9, 9}};
  std::map<int, int> b{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
                       {6, 6}, {7, 7}, {8, 8}, {9, 9}};
  s21::Map<int, int>::iterator it = a.begin();
  std::map<int, int>::iterator map_it = b.begin();
  EXPECT_EQ(*(it), *(map_it));
}

TEST(MapTest, iterators) {
  s21::Map<int, int> a{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
                       {6, 6}, {7, 7}, {8, 8}, {9, 9}};
  std::map<int, int> b{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
                       {6, 6}, {7, 7}, {8, 8}, {9, 9}};
  s21::Map<int, int>::iterator it = a.begin();
  std::map<int, int>::iterator map_it = b.begin();
  ++it;
  ++map_it;
  EXPECT_EQ(*(it), *(map_it));
  ++it;
  ++map_it;
  EXPECT_EQ(*(it), *(map_it));
  ++it;
  ++map_it;
  EXPECT_EQ(*(it), *(map_it));
  ++it;
  ++map_it;
  EXPECT_EQ(*(it), *(map_it));
  ++it;
  ++map_it;
  EXPECT_EQ(*(it), *(map_it));
  ++it;
  ++map_it;
  EXPECT_EQ(*(it), *(map_it));
  ++it;
  ++map_it;
  EXPECT_EQ(*(it), *(map_it));
  ++it;
  ++map_it;
  EXPECT_EQ(*(it), *(map_it));

  --it;
  --map_it;
  EXPECT_EQ(*(it), *(map_it));
  --it;
  --map_it;
  EXPECT_EQ(*(it), *(map_it));
  --it;
  --map_it;
  EXPECT_EQ(*(it), *(map_it));
  --it;
  --map_it;
  EXPECT_EQ(*(it), *(map_it));
  --it;
  --map_it;
  EXPECT_EQ(*(it), *(map_it));
  --it;
  --map_it;
  EXPECT_EQ(*(it), *(map_it));
  --it;
  --map_it;
  EXPECT_EQ(*(it), *(map_it));
  --it;
  --map_it;
  EXPECT_EQ(*(it), *(map_it));
}

TEST(MapTest, erase) {
  s21::Map<int, int> a{{1, 5}, {2, 6}, {3, 7}};
  std::map<int, int> b{{1, 5}, {2, 6}, {3, 7}};
  a.erase(a.begin());
  b.erase(b.begin());
  EXPECT_EQ(a.size(), b.size());
  EXPECT_ANY_THROW(a.at(1));
  EXPECT_EQ(a.at(2), b.at(2));
  EXPECT_EQ(a.at(3), b.at(3));
}

TEST(MapTest, swap) {
  s21::Map<int, int> a{{1, 5}, {2, 6}, {3, 7}};
  s21::Map<int, int> b;
  std::map<int, int> c{{1, 5}, {2, 6}, {3, 7}};
  std::map<int, int> d;
  a.swap(b);
  c.swap(d);
  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(b.size(), d.size());
  EXPECT_EQ(b.at(1), d.at(1));
}

TEST(MapTest, insert1) {
  s21::Map<int, int> a{{1, 5}, {2, 6}, {3, 7}};
  std::map<int, int> b{{1, 5}, {2, 6}, {3, 7}};
  EXPECT_EQ((a.insert({4, 8})).second, (b.insert({4, 8})).second);
  EXPECT_EQ((a.insert({3, 2})).second, (b.insert({3, 2})).second);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.at(4), b.at(4));
}

TEST(MapTest, insert2) {
  s21::Map<int, int> a{{1, 5}, {2, 6}, {3, 7}};
  std::map<int, int> b{{1, 5}, {2, 6}, {3, 7}};
  EXPECT_EQ((a.insert(4, 8)).second, (b.insert({4, 8})).second);
  EXPECT_EQ((a.insert(3, 2)).second, (b.insert({3, 2})).second);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.at(4), b.at(4));
}

TEST(MapTest, insert3) {
  s21::Map<int, int> a{{1, 5}, {2, 6}, {3, 7}};
  std::map<int, int> b{{1, 5}, {2, 6}, {3, 7}};
  EXPECT_EQ((a.insert_or_assign(4, 8)).second,
            (b.insert_or_assign(4, 8)).second);
  EXPECT_EQ((a.insert_or_assign(3, 2)).second,
            (b.insert_or_assign(3, 2)).second);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.at(4), b.at(4));
}

TEST(MapTest, merge) {
  s21::Map<int, int> a{{1, 5}, {2, 6}, {3, 7}};
  s21::Map<int, int> b{{1, 3}, {4, 8}, {5, 5}};
  a.merge(b);
  std::map<int, int> c{{1, 5}, {2, 6}, {3, 7}};
  std::map<int, int> d{{1, 3}, {4, 8}, {5, 5}};
  c.merge(d);
  EXPECT_EQ(a.size(), c.size());
  EXPECT_EQ(a.at(1), c.at(1));
}

TEST(MapTest, insert_many) {
  std::pair<int, int> pair1(1, 5);
  std::pair<int, int> pair2(2, 4);
  std::pair<int, int> pair3(3, 3);
  std::pair<int, int> pair4(4, 2);
  std::pair<int, int> pair5(5, 1);
  s21::Map<int, int> a{pair1, pair2};
  a.insert_many(pair3, pair4, pair5);
  s21::Map<int, int>::iterator iter(a.begin());
  EXPECT_EQ((*iter).first, 1);
  ++iter;
  EXPECT_EQ((*iter).first, 2);
  ++iter;
  EXPECT_EQ((*iter).first, 3);
  ++iter;
  EXPECT_EQ((*iter).first, 4);
  ++iter;
  EXPECT_EQ((*iter).first, 5);
}