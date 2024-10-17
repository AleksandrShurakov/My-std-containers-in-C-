#ifndef CPP2_S21_CONTAINERS_SRC_LIST_H
#define CPP2_S21_CONTAINERS_SRC_LIST_H

#include <limits>

namespace s21 {
template <typename T>
class List {
 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = std::size_t;

 private:
  struct Node {
    Node() : value(value_type{}), next(nullptr), prev(nullptr){};
    explicit Node(value_type val) : Node() { value = val; };
    ~Node(){};

    T value;
    Node *next;
    Node *prev;
  };

 public:
  class ListIterator {
    friend class List<T>;

   public:
    ListIterator() : current_(nullptr){};
    explicit ListIterator(Node *ptr) : current_(ptr){};
    ListIterator(const ListIterator &other) : current_(other.current_){};
    ListIterator(ListIterator &&other) noexcept : current_(other.current_) {
      other.current_ = nullptr;
    }

    iterator &operator=(const iterator &other) {
      if (this != &other) {
        current_ = other.current_;
      }
      return *this;
    }

    iterator &operator++() {
      if (current_) {
        current_ = current_->next;
      }
      return *this;
    }

    iterator &operator--() {
      if (current_ && current_->prev) {
        current_ = current_->prev;
      }
      return *this;
    }

    bool operator==(const iterator &other) const {
      return current_ == other.current_;
    }

    bool operator!=(const iterator &other) const { return !(*this == other); }

    reference operator*() {
      if (current_ == nullptr) {
        throw "tried to dereference an empty iterator";
      }
      return current_->value;
    }

   private:
    Node *current_;
  };

  class ListConstIterator {
    friend class List<T>;

   public:
    ListConstIterator() : current_(nullptr){};
    explicit ListConstIterator(const Node *ptr) : current_(ptr){};
    ListConstIterator(const ListConstIterator &other)
        : current_(other.current_){};
    explicit ListConstIterator(const ListIterator &other)
        : current_(other.current_){};
    ListConstIterator(ListConstIterator &&other) noexcept
        : current_(other.current_) {
      other.current_ = nullptr;
    }

    const_iterator &operator=(const iterator &other) {
      if (this != &other) {
        current_ = other.current_;
      }
      return *this;
    }

    const_iterator &operator++() {
      if (current_) {
        current_ = current_->next;
      }
      return *this;
    }

    const_iterator &operator--() {
      if (current_ && current_->prev) {
        current_ = current_->prev;
      }
      return *this;
    }

    bool operator==(const const_iterator &other) const {
      return current_ == other.current_;
    }

    bool operator!=(const const_iterator &other) const {
      return !(*this == other);
    }

    const_reference operator*() {
      if (current_ == nullptr) {
        throw std::out_of_range("tried to dereference an empty iterator");
      }
      return current_->value;
    }

   private:
    const Node *current_;
  };

  List() : head_(nullptr), tail_(nullptr), size_(0){};

  explicit List(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
    if (n >= max_size()) {
      throw std::out_of_range("Size of list is too large");
    }
    for (size_type i = 0; i < n; ++i) {
      push_back(0);
    }
  };

  explicit List(std::initializer_list<value_type> const &items) : List() {
    for (const_reference item : items) {
      push_back(item);
    }
  }

  List(const List &other) : List() {
    for (const_reference item : other) {
      push_back(item);
    }
  }

  List(List &&other) noexcept
      : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  ~List() {
    Node *node_to_delete = head_;
    for (Node *tmp = head_; tmp != tail_;) {
      tmp = tmp->next;
      delete node_to_delete;
      node_to_delete = tmp;
    }
    delete node_to_delete;
  }

  List &operator=(List &&other) {
    if (this != &other) {
      clear();

      head_ = other.head_;
      tail_ = other.tail_;
      size_ = other.size_;

      other.head_ = nullptr;
      other.tail_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  iterator begin() { return iterator(head_); }

  iterator end() { return iterator(); }

  const_iterator begin() const { return const_iterator(head_); }

  const_iterator end() const { return const_iterator(); }

  const_reference front() {
    if (head_ == nullptr) {
      throw std::out_of_range("Head does not exist");
    }
    return head_->value;
  }

  const_reference back() {
    if (tail_ == nullptr) {
      throw std::out_of_range("Tail does not exist");
    }
    return tail_->value;
  }

  bool empty() { return size_ == 0 ? 1 : 0; }

  size_type size() { return size_; }

  size_type max_size() { return std::numeric_limits<size_type>::max(); }

  void clear() {
    while (head_ != nullptr) {
      Node *temp = head_->next;
      delete head_;
      head_ = temp;
    }

    head_ = tail_ = nullptr;
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    if (pos == begin()) {
      push_front(value);
      return begin();
    }

    if (pos == end()) {
      push_back(value);
      return end();
    }

    Node *newNode = new Node(value);
    newNode->prev = pos.current_->prev;
    newNode->next = pos.current_;

    pos.current_->prev->next = newNode;
    pos.current_->prev = newNode;

    iterator newIterator = iterator(newNode);
    ++size_;
    return newIterator;
  }

  void erase(iterator pos) {
    if (pos == begin()) {
      pop_front();
      return;
    }

    if (pos == end()) {
      pop_back();
      return;
    }
    Node *node_to_delete = pos.current_;
    node_to_delete->prev->next = node_to_delete->next;
    node_to_delete->next->prev = node_to_delete->prev;

    delete node_to_delete;
    --size_;
  }

  void push_back(const_reference value) {
    Node *newNode = new Node(value);
    if (!head_) {
      head_ = tail_ = newNode;
    } else {
      tail_->next = newNode;
      newNode->prev = tail_;
      newNode->next = nullptr;
      tail_ = newNode;
    }
    ++size_;
  }

  void pop_back() {
    if (empty()) {
      throw std::runtime_error("pop_back() called on an empty list");
    }

    if (size_ == 1) {
      delete tail_;
      head_ = tail_ = nullptr;
    } else {
      Node *newTail = tail_->prev;
      newTail->next = nullptr;
      delete tail_;
      tail_ = newTail;
    }
    --size_;
  }

  void push_front(const_reference value) {
    Node *newNode = new Node(value);
    if (!head_) {
      head_ = tail_ = newNode;

    } else {
      head_->prev = newNode;
      newNode->prev = nullptr;
      newNode->next = head_;
      head_ = newNode;
    }
    ++size_;
  }

  void pop_front() {
    if (empty()) {
      throw std::runtime_error("pop_front() called on an empty list");
    }

    if (size_ == 1) {
      delete tail_;
      head_ = tail_ = nullptr;
    } else {
      Node *newHead = head_->next;
      newHead->prev = nullptr;
      delete head_;
      head_ = newHead;
    }
    --size_;
  }

  void swap(List &other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  void merge(List &other) {
    sort();
    other.sort();

    List mergedList;

    s21::List<int>::iterator itThis(begin());
    iterator itOther(other.begin());

    while (itThis != end() && itOther != other.end()) {
      if (*itThis < *itOther) {
        mergedList.push_back(*itThis);
        ++itThis;
      } else {
        mergedList.push_back(*itOther);
        ++itOther;
      }
    }

    while (itThis != end()) {
      mergedList.push_back(*itThis);
      ++itThis;
    }
    while (itOther != other.end()) {
      mergedList.push_back(*itOther);
      ++itOther;
    }

    *this = std::move(mergedList);
    other.clear();
  }

  void splice(const_iterator pos, List &other) {
    if (other.empty()) {
      return;
    }

    iterator temp_it = iterator(const_cast<Node *>(pos.current_));

    if (pos.current_ == nullptr || pos.current_->prev->next != pos.current_) {
      throw std::runtime_error("Invalid position for splice");
    }

    Node *other_head = other.head_;
    Node *other_tail = other.tail_;

    if (other_head) {
      other_head->prev = nullptr;
      other_tail->next = nullptr;
      other.head_ = other.tail_ = nullptr;
      other.size_ = 0;
    }

    if (pos.current_->prev) {
      pos.current_->prev->next = other_head;
    } else {
      head_ = other.head_;
    }

    if (other_head) {
      other_tail->next = temp_it.current_;
      temp_it.current_->prev = other.tail_;
    }

    size_ += other.size_;
    other.size_ = 0;
  }

  void reverse() {
    if (size_ <= 1) {
      return;
    }

    Node *current = head_;
    Node *prev = nullptr;

    while (current) {
      Node *next = current->next;
      current->next = prev;
      current->prev = next;

      prev = current;
      current = next;
    }

    std::swap(head_, tail_);
  }

  void unique() {
    if (size_ <= 1) {
      return;
    }
    Node *current = head_;
    while (current && current->next) {
      if (current->value == current->next->value) {
        Node *to_remove = current;
        current = current->next;
        s21::List<int>::ListIterator it(to_remove);
        erase(it);
      } else {
        current = current->next;
      }
    }
  }

  void sort() {
    if (size_ <= 1) {
      return;
    }
    quickSort(head_, tail_);
  }

  template <class... Args>
  iterator insert_many(iterator pos, Args &&...args) {
    return (insert_many_aux(pos, args...));
  }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    insert_many_aux(end(), args...);
  }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    insert_many_aux(begin(), args...);
  }

 private:
  Node *head_;
  Node *tail_;

  size_type size_;

  void quickSort(Node *low, Node *high) {
    if (low != nullptr && high != nullptr && low != high && low != high->next) {
      Node *pivot = partition(low, high);
      quickSort(low, pivot->prev);
      quickSort(pivot->next, high);
    }
  }

  Node *partition(Node *low, Node *high) {
    value_type pivotValue = high->value;
    Node *i = low->prev;

    for (Node *j = low; j != high; j = j->next) {
      if (j->value <= pivotValue) {
        i = (i != nullptr) ? i->next : low;
        std::swap(i->value, j->value);
      }
    }
    i = (i != nullptr) ? i->next : low;
    std::swap(i->value, high->value);
    return i;
  }

  iterator insert_many_aux(iterator pos) { return pos; }

  template <class U>
  iterator insert_many_aux(iterator pos, U &&arg) {
    pos = insert(pos, arg);
    return pos;
  }

  template <class U, class... Args>
  iterator insert_many_aux(iterator pos, U &&arg, Args &&...args) {
    pos = insert(pos, arg);
    ++pos;
    pos = insert_many_aux(pos, args...);
    return pos;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_LIST_H