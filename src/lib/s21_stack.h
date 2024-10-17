#ifndef CPP2_S21_CONTAINERS_SRC_STACK_H
#define CPP2_S21_CONTAINERS_SRC_STACK_H

#include "s21_list.h"

namespace s21 {
template <typename T, typename Container = s21::List<T>>
class Stack {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 protected:
  Container cont;

 public:
  Stack() : cont() {}
  explicit Stack(std::initializer_list<value_type> const &items)
      : cont(items) {}
  Stack(const Stack &q) : cont(q.cont) {}
  Stack(Stack &&q) : cont(std::move(q.cont)) {}
  ~Stack() {}
  Stack &operator=(Stack &&q) {
    this->cont = std::move(q.cont);
    return *this;
  }

  const_reference top() { return cont.back(); }

  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }

  void push(const_reference value) { this->cont.push_back(value); }
  void pop() { this->cont.pop_back(); }
  void swap(Stack &other) { this->cont.swap(other.cont); }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    return cont.insert_many_back(args...);
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_STACK_H