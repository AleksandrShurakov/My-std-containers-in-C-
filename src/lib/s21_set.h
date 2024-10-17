#ifndef CPP2_S21_CONTAINERS_SRC_LIB_SET_H
#define CPP2_S21_CONTAINERS_SRC_LIB_SET_H

#include "s21_avl_tree.h"

namespace s21 {
template <typename Key>
class Set {
 public:
  using key_type = Key;
  using value_type = key_type;
  using set_type = std::pair<value_type, int>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using node_type = node<set_type, int>;
  using iterator = typename AVL<set_type, int>::Iterator;
  using const_iterator = typename AVL<set_type, int>::ConstIterator;
  using size_type = size_t;

  Set() : tree_() {}

  Set(std::initializer_list<value_type> const &items) {
    for (auto it : items) {
      std::pair<value_type, int> set_pair(it, 0);
      tree_.insert(set_pair);
    }
  }

  Set(const Set &m) : tree_(m.tree_) {}
  Set(Set &&m) : tree_(std::move(m.tree_)) {}

  Set &operator=(Set &m) {
    tree_ = m.tree_;
    return *this;
  }

  Set &operator=(Set &&m) {
    tree_ = std::move(m.tree_);
    return *this;
  }

  ~Set() {}

  iterator begin() { return iterator(tree_.begin()); }
  iterator end() { return iterator(tree_.end()); }

  bool empty() { return tree_.empty(); }
  size_type size() { return tree_.size(); }
  size_type max_size() { return tree_.max_size(); }

  void clear() { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    bool inserted{};
    std::pair<value_type, int> set_pair(value, 0);
    node_type *tmp = tree_.search(set_pair);
    if (!tmp) {
      inserted = true;
      tmp = tree_.insert(set_pair);
    }
    iterator it(tmp);
    return std::pair<iterator, bool>{it, inserted};
  }

  void erase(iterator pos) { tree_.erase(*pos); }
  void swap(Set &other) { std::swap(tree_, other.tree_); }

  void merge(Set &other) {
    node_type *inserted_node{};
    for (auto it = other.begin(); it != other.end();) {
      std::pair<value_type, int> set_pair((*it).first, 0);
      inserted_node = tree_.search(set_pair);
      if (!inserted_node) {
        tree_.insert(set_pair);
        inserted_node = other.tree_.search(set_pair);
        ++it;
        if (other.size() == 1) it = iterator{nullptr};
        other.erase(iterator{inserted_node});
      } else {
        ++it;
      }
    }
  }

  bool contains(const key_type &key) {
    auto res = tree_.search(set_type{key, 0});
    return res != nullptr;
  }

  iterator find(const Key &key) {
    node_type *res = tree_.search(set_type{key, 0});
    return iterator{res};
  }

  template <class... Args>
  void insert_many(Args &&...args) {
    insert_many_aux(args...);
  }

 private:
  AVL<set_type, int> tree_;

  template <class U>
  void insert_many_aux(U &&arg) {
    insert(arg);
  }

  template <class U, class... Args>
  void insert_many_aux(U &&arg, Args &&...args) {
    insert(arg);
    insert_many_aux(args...);
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_LIB_SET_H