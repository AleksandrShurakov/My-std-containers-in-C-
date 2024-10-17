#ifndef CPP2_S21_CONTAINERS_SRC_S21_AVL_TREE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_AVL_TREE_H_

#include <initializer_list>
#include <limits>

using namespace std;

template <typename Key, typename T>
struct node {
  node() : key_{}, height{}, left{}, right{}, parent{} {}
  node(Key key, int height_)
      : key_{key}, height{height_}, left{}, right{}, parent{} {}
  Key key_;
  int height;
  node *left, *right, *parent;
};

template <typename Key, typename T>
class AVL {
 public:
  class Iterator;
  class ConstIterator;
  using node_type = node<Key, T>;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  // ---------------- Member functions ---------------------

  AVL() : root_(nullptr), size_(0) {}
  ~AVL() { clear(); }

  explicit AVL(std::initializer_list<Key> const &init) : AVL() {
    for (auto i : init) insert(i);
  }

  explicit AVL(const AVL<Key, T> &other) : root_{nullptr}, size_{other.size_} {
    if (other.root_) {
      root_ = new node_type(other.root_->key_, other.root_->height);
      root_->parent = nullptr;
      copy_tree(root_, other.root_);
    }
  }

  AVL(AVL<Key, T> &&other) noexcept : root_(other.root_), size_(other.size_) {
    other.root_ = nullptr;
    other.size_ = 0;
  }

  AVL &operator=(const AVL &other) {
    if (this->root_ != other.root_) {
      clear();
      size_ = other.size_;
      root_ = new node_type(other.root_->key_, other.root_->height);
      copy_tree(root_, other.root_);
    }
    return *this;
  }

  AVL &operator=(AVL &&other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
    other.clear();
    return *this;
  }

  // ---------------- Capacity ---------------------

  bool empty() { return size_ == 0; }

  size_type size() { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }

  // ---------------- Modifiers ---------------------

  void erase(Key key) {
    root_ = erases(root_, key);
    make_parents(root_, nullptr);
    size_--;
  }

  void clear() {
    if (root_) {
      free_tree(root_);
      root_ = nullptr;
      size_ = 0;
    }
  }

  // ---------------- Utilitaty functions ---------------------

  node_type *inserts(Key key, node_type *node) {
    if (node == nullptr) {
      node = new node_type{key, 0};
      size_++;
      node->left = node->right = nullptr;

    } else if (key.first < node->key_.first) {
      node->left = inserts(key, node->left);
    } else if (key.first > node->key_.first) {
      node->right = inserts(key, node->right);
    }
    return balance(node);
  }

  node_type *insert(Key key) {
    root_ = inserts(key, root_);
    make_parents(root_, nullptr);
    return search(key);
  }

  AVL<Key, T> &copy_tree(node_type *node, const node_type *other_node) {
    if (other_node) {
      if (other_node->left) {
        node->left =
            new node_type(other_node->left->key_, other_node->left->height);
        copy_tree(node->left, other_node->left);
      }
      if (other_node->right) {
        node->right =
            new node_type(other_node->right->key_, other_node->right->height);
        copy_tree(node->right, other_node->right);
      }
    }
    return *this;
  }

  void make_parents(node_type *node, node_type *parent) {
    if (node) {
      node->parent = parent;
      make_parents(node->left, node);
      make_parents(node->right, node);
    }
  }

  void free_tree(node_type *node) {
    if (node) {
      if (node->left) {
        free_tree(node->left);
      }
      if (node->right) {
        free_tree(node->right);
      }
      delete node;
    }
  }

  node_type *search_elem(Key key, node_type *node) {
    if (!node) {
      return nullptr;
    }

    if (key.first < node->key_.first) {
      return search_elem(key, node->left);
    } else if (key.first > node->key_.first) {
      return search_elem(key, node->right);
    } else {
      return node;
    }
  }

  node_type *search(Key key) { return search_elem(key, root_); }

  void update_height(node_type *node) {
    node->height =
        std::max(get_height(node->left), get_height(node->right)) + 1;
  }

  int get_height(const node_type *node) const {
    return node ? node->height : -1;
  }

  int get_balance(const node_type *node) const {
    return node ? get_height(node->right) - get_height(node->left) : 0;
  }

  node_type *right_rotate(node_type *node) {
    node_type *buffer = node->left;
    node->left = buffer->right;
    buffer->right = node;
    update_height(node);
    update_height(buffer);
    return buffer;
  }

  node_type *left_rotate(node_type *node) {
    node_type *buffer = node->right;
    node->right = buffer->left;
    buffer->left = node;
    update_height(node);
    update_height(buffer);
    return buffer;
  }

  node_type *balance(node_type *node) {
    update_height(node);
    int balance = get_balance(node);
    if (balance == 2) {
      if (get_balance(node->right) < 0) {
        node->right = right_rotate(node->right);
      }
      return left_rotate(node);
    }
    if (balance == -2) {
      if (get_balance(node->left) > 0) {
        node->left = left_rotate(node->left);
      }
      return right_rotate(node);
    }
    return node;
  }

  static node_type *find_min(node_type *node) {
    return node->left ? find_min(node->left) : node;
  }
  static node_type *find_max(node_type *node) {
    return node->right ? find_max(node->right) : node;
  }

  node_type *erase_min(node_type *node) {
    if (node->left == nullptr) return node->right;
    node->left = erase_min(node->left);
    return balance(node);
  }

  node_type *erases(node_type *node, Key key) {
    if (!node) return 0;
    if (key.first < node->key_.first)
      node->left = erases(node->left, key);
    else if (key.first > node->key_.first)
      node->right = erases(node->right, key);
    else {
      node_type *left_child = node->left;
      node_type *right_child = node->right;
      delete node;
      if (!right_child) return left_child;
      node_type *min = find_min(right_child);
      min->right = erase_min(right_child);
      min->left = left_child;
      return balance(min);
    }
    return balance(node);
  }

  node_type *begin() { return find_min(root_); }

  void set_size(bool sign) {
    if (sign) {
      size_++;
    } else {
      size_--;
    }
  }

  node_type *end() { return root_ ? root_->parent : nullptr; }

  //-------------------------- Iterators ---------------------------
  class Iterator {
   public:
    Iterator() : iterated_node_(nullptr) {}
    explicit Iterator(node_type *node) : iterated_node_(node) {}
    Iterator(const iterator &other) : iterated_node_(other.iterated_node_) {}
    Iterator(iterator &&other) : iterated_node_(other.iterated_node_) {
      other.iterated_node_ = nullptr;
    }
    iterator &operator=(const iterator &other) {
      if (this != &other) {
        iterated_node_ = other.iterated_node_;
      }
      return *this;
    }

    iterator &operator=(iterator &&other) {
      if (this != &other) {
        iterated_node_ = other.iterated_node_;
        other.iterated_node_ = nullptr;
      }
      return *this;
    }

    iterator &operator++() {
      if (iterated_node_) {
        if (iterated_node_->right) {
          node_type *min_iter = find_min(iterated_node_->right);
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

    iterator &operator--() {
      if (iterated_node_) {
        if (iterated_node_->left) {
          node_type *max_iter = find_max(iterated_node_->left);
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

    Key &operator*() {
      if (iterated_node_) return iterated_node_->key_;
      static Key empty_key_{};
      return empty_key_;
    };

    bool operator!=(const iterator &it) {
      return iterated_node_ != it.iterated_node_;
    };

    bool operator==(const iterator &it) {
      return iterated_node_ == it.iterated_node_;
    };

    //  protected:
    node_type *iterated_node_;
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator{} {};
    explicit ConstIterator(node_type *node) : Iterator{node} {};
    ConstIterator(const const_iterator &other) : Iterator{other} {};
    ConstIterator(const iterator &other) : Iterator{other} {};
    ConstIterator(const_iterator &&other) : Iterator{std::move(other)} {};
    const Key &operator*();
  };

 private:
  node_type *root_;
  size_type size_;
};

#endif  // CPP2_S21_CONTAINERS_SRC_S21_AVL_TREE_H_
