#ifndef CPP2_S21_CONTAINERS_SRC_MAP_H
#define CPP2_S21_CONTAINERS_SRC_MAP_H

#include "s21_avl_tree.h"

namespace s21 {
template <typename T, typename V>
class Map {
 public:
  using key_type = T;
  using mapped_type = V;
  using default_value = mapped_type &;
  using value_type = std::pair<const key_type, mapped_type>;
  using node_type = node<value_type, mapped_type>;
  using iterator = typename AVL<value_type, mapped_type>::Iterator;
  using const_iterator = typename AVL<value_type, mapped_type>::ConstIterator;
  using size_type = size_t;

  Map() : tree_() {}
  Map(std::initializer_list<value_type> const &items) {
    for (auto it : items) {
      tree_.insert(it);
    }
  }

  Map(const Map &m) : tree_(m.tree_) {}
  Map(Map &&m) : tree_(std::move(m.tree_)) {}

  Map &operator=(Map &m) {
    tree_ = m.tree_;
    return *this;
  }

  Map &operator=(Map &&m) {
    tree_ = std::move(m.tree_);
    return *this;
  }

  ~Map() {}

  mapped_type &at(const key_type &key) {
    node_type *res = tree_.search(value_type{key, mapped_type{}});
    if (res) {
      return res->key_.second;
    } else {
      throw std::out_of_range("Key does not exist!");
    }
  }

  mapped_type &operator[](const key_type &key) {
    node_type *res = tree_.search(value_type{key, mapped_type{}});
    if (res) {
      return res->key_.second;
    } else {
      auto returned = tree_.insert(value_type{key, mapped_type{}});
      return returned->key_.second;
    }
  }

  iterator begin() { return iterator(tree_.begin()); }
  iterator end() { return iterator(tree_.end()); }

  bool empty() { return tree_.empty(); }
  size_type size() { return tree_.size(); }
  size_type max_size() { return tree_.max_size(); }

  void clear() { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    bool inserted{};
    node_type *tmp = tree_.search(value_type{value.first, mapped_type{}});
    if (!tmp) {
      inserted = true;
      tmp = tree_.insert(value);
    }
    iterator it(tmp);
    return std::pair<iterator, bool>{it, inserted};
  }

  std::pair<iterator, bool> insert(const key_type &key, const T &obj) {
    bool inserted{};
    node_type *tmp = tree_.search(value_type{key, mapped_type{}});
    if (!tmp) {
      inserted = true;
      tmp = tree_.insert(value_type{key, obj});
    }
    iterator it(tmp);
    return std::pair<iterator, bool>{it, inserted};
  }

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const T &obj) {
    bool inserted{};
    node_type *tmp = tree_.search(value_type{key, mapped_type{}});
    if (tmp) {
      tmp->key_.second = obj;
    } else {
      inserted = true;
      tmp = tree_.insert(value_type{key, obj});
    }
    iterator it(tmp);
    return std::pair<iterator, bool>{it, inserted};
  }

  void erase(iterator pos) { tree_.erase(*pos); }
  void swap(Map &other) { std::swap(tree_, other.tree_); }

  void merge(Map &other) {
    node_type *inserted_node{};
    for (auto it = other.begin(); it != other.end();) {
      inserted_node = tree_.search(value_type{(*it).first, mapped_type{}});
      if (!inserted_node) {
        insert(*it);
        inserted_node =
            other.tree_.search(value_type{(*it).first, mapped_type{}});
        ++it;
        if (other.size() == 1) it = iterator{nullptr};
        other.erase(iterator{inserted_node});
      } else {
        ++it;
      }
    }
  }

  bool contains(const key_type &key) {
    auto res = tree_.search(value_type{key, mapped_type{}});
    return res != nullptr;
  }

  template <class... Args>
  void insert_many(Args &&...args) {
    insert_many_aux(args...);
  }

 private:
  AVL<value_type, mapped_type> tree_;

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

#endif