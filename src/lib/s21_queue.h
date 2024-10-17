#ifndef CPP2_S21_CONTAINERS_SRC_QUEUE_H
#define CPP2_S21_CONTAINERS_SRC_QUEUE_H

#include "s21_list.h"

namespace s21 {
template <typename T, typename Container = s21::List<T>>
class Queue {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 protected:
  Container cont;

 public:
  Queue() : cont() {}
  explicit Queue(std::initializer_list<value_type> const &items)
      : cont(items) {}
  Queue(const Queue &q) : cont(q.cont) {}
  Queue(Queue &&q) : cont(std::move(q.cont)) {}
  ~Queue() {}
  Queue &operator=(Queue &&q) {
    this->cont = std::move(q.cont);
    return *this;
  }

  const_reference front() { return cont.front(); }
  const_reference back() { return cont.back(); }

  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }

  void push(const_reference value) { this->cont.push_back(value); }
  void pop() { this->cont.pop_front(); }
  void swap(Queue &other) { this->cont.swap(other.cont); }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    return cont.insert_many_back(args...);
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_QUEUE_H