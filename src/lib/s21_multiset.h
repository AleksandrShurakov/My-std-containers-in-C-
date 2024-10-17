#ifndef CPP2_S21_CONTAINERS_SRC_LIB_MULTISET_H
#define CPP2_S21_CONTAINERS_SRC_LIB_MULTISET_H

#include "s21_avl_tree.h"

namespace s21 {
template <typename Key>

class Multiset {
 public:
  class MultIterator;
  class MultConstIterator;

  using key_type = Key;
  using value_type = key_type;
  using multiset_type = std::pair<value_type, int>;
  using node_type = node<multiset_type, int>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MultIterator;
  using const_iterator = MultConstIterator;
  using size_type = size_t;

  Multiset() : tree_() {}

  Multiset(std::initializer_list<value_type> const& items) {
    for (auto it : items) {
      insert(it);
    }
  }

  Multiset(const Multiset& m) : tree_(m.tree_) {}
  Multiset(Multiset&& m) : tree_(std::move(m.tree_)) {}

  Multiset& operator=(Multiset& m) {
    tree_ = m.tree_;
    return *this;
  }

  Multiset& operator=(Multiset&& m) {
    tree_ = std::move(m.tree_);
    return *this;
  }

  ~Multiset() {}

  iterator insert(const value_type& value) {
    std::pair<value_type, int> set_pair(value, 1);
    node_type* tmp = tree_.search(set_pair);
    if (!tmp) {
      tmp = tree_.insert(set_pair);
    } else {
      tmp->key_.second++;
      if (!empty()) tree_.set_size(1);
    }
    return iterator{tmp};
  }
  iterator begin() { return iterator(tree_.begin()); }
  iterator end() { return iterator(tree_.end()); }

  bool empty() { return tree_.empty(); }
  size_type size() { return tree_.size(); }
  size_type max_size() { return tree_.max_size(); }

  void clear() { tree_.clear(); }

  void erase(iterator pos) {
    std::pair<value_type, int> set_pair(*(pos),
                                        pos.iterated_node_->key_.second);
    node_type* tmp = tree_.search(set_pair);
    if (tmp) {
      if (pos.iterated_node_->key_.second > 1) {
        pos.count_--;
        tree_.set_size(0);
      } else {
        tree_.erase((pos.iterated_node_->key_));
      }
    }
  }

  void swap(Multiset& other) { std::swap(tree_, other.tree_); }

  void merge(Multiset& other) {
    node_type* inserted_node{};
    for (auto it = other.begin(); it != other.end();) {
      std::pair<value_type, int> Multiset_pair((*it), 0);
      inserted_node = tree_.search(Multiset_pair);
      if (!inserted_node) {
        tree_.insert(Multiset_pair);
        inserted_node = other.tree_.search(Multiset_pair);
        ++it;
        if (other.size() == 1) it = iterator{nullptr};
        other.erase(iterator{inserted_node});
      } else {
        insert(*it);
        ++it;
      }
    }
  }

  bool contains(const key_type& key) {
    std::pair<value_type, int> set_pair(key, 1);
    auto res = tree_.search(set_pair);
    return res != nullptr;
  }

  iterator find(const Key& key) {
    std::pair<value_type, int> set_pair(key, 1);
    node_type* tmp = tree_.search(set_pair);
    return iterator{tmp};
  }

  iterator lower_bound(const Key& key) {
    iterator tmp1 = insert(key);
    iterator tmp2 = tmp1;
    iterator res = ++tmp2;
    erase(tmp1);
    return res;
  }

  iterator upper_bound(const Key& key) {
    iterator tmp1 = insert(key);
    iterator tmp2 = tmp1;
    iterator res = ++tmp2;
    if (*(res)) {
      while (*res && res.iterated_node_->key_.first <= key) {
        ++res;
      }
    }
    erase(tmp1);
    return res;
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    return std::pair<iterator, iterator>(lower_bound(key),
                                         --(upper_bound(key)));
  }

  template <class... Args>
  void insert_many(Args&&... args) {
    insert_many_aux(args...);
  }

  class MultIterator {
   public:
    MultIterator() : iterated_node_(nullptr), count_(0) {}
    explicit MultIterator(node_type* node) : iterated_node_(node), count_(1) {}
    MultIterator(const iterator& other)
        : iterated_node_(other.iterated_node_), count_(other.count_) {}
    MultIterator(iterator&& other)
        : iterated_node_(other.iterated_node_), count_(other.count_) {
      other.iterated_node_ = nullptr;
      count_ = 0;
    }

    iterator& operator=(const iterator& other) {
      if (this != &other) {
        iterated_node_ = other.iterated_node_;
        count_ = other.count_;
      }
      return *this;
    }

    iterator& operator=(iterator&& other) {
      if (this != &other) {
        iterated_node_ = other.iterated_node_;
        count_ = other.count_;
        other.iterated_node_ = nullptr;
        other.count_ = 0;
      }
      return *this;
    }

    iterator& operator++() {
      if (iterated_node_) {
        if (count_ < (iterated_node_->key_).second) {
          count_++;
          return *this;
        }
        if (iterated_node_->right) {
          node_type* min_iter = find_min(iterated_node_->right);
          iterated_node_ = min_iter;
        } else {
          while (iterated_node_->parent != nullptr &&
                 iterated_node_->parent->key_.first <
                     iterated_node_->key_.first) {
            iterated_node_ = iterated_node_->parent;
          }
          iterated_node_ = iterated_node_->parent;
        }
      }
      return *this;
    }

    iterator& operator--() {
      if (iterated_node_) {
        if (count_ > 1) {
          count_--;
          return *this;
        }
        if (iterated_node_->left) {
          node_type* max_iter = find_max(iterated_node_->left);
          iterated_node_ = max_iter;
        } else {
          while (iterated_node_->parent != nullptr &&
                 iterated_node_->parent->key_.first >
                     iterated_node_->key_.first) {
            iterated_node_ = iterated_node_->parent;
          }
          iterated_node_ = iterated_node_->parent;
        }
      }
      return *this;
    }

    static node_type* find_min(node_type* node) {
      return node->left ? find_min(node->left) : node;
    }
    static node_type* find_max(node_type* node) {
      return node->right ? find_max(node->right) : node;
    }

    Key& operator*() {
      if (iterated_node_) return iterated_node_->key_.first;
      static Key empty_key_{};
      return empty_key_;
    }

    bool operator!=(const iterator& it) {
      return iterated_node_ != it.iterated_node_;
    }

    bool operator==(const iterator& it) {
      return iterated_node_ == it.iterated_node_;
    }

    node_type* iterated_node_;
    int count_;
  };

  class MultConstIterator : public MultIterator {
   public:
    MultConstIterator() : MultIterator{} {};
    explicit MultConstIterator(node_type* node) : MultIterator{node} {};
    MultConstIterator(const const_iterator& other) : MultIterator{other} {};
    MultConstIterator(const iterator& other) : MultIterator{other} {};
    MultConstIterator(const_iterator&& other)
        : MultIterator{std::move(other)} {};
    const Key& operator*();
  };

 private:
  AVL<multiset_type, int> tree_;

  template <class U>
  void insert_many_aux(U&& arg) {
    insert(arg);
  }

  template <class U, class... Args>
  void insert_many_aux(U&& arg, Args&&... args) {
    insert(arg);
    insert_many_aux(args...);
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_LIB_MULTISET_H