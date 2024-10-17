#ifndef CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H
#define CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H

#include <cmath>
#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T, size_t n>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  Array(){};
  Array(const Array &v) { std::copy(v.begin(), v.end(), data_); };
  Array(Array &&v) noexcept { std::move(v.begin(), v.end(), data_); };
  explicit Array(std::initializer_list<value_type> const &items) {
    if (items.size() > n) {
      throw std::out_of_range("too many initializers for Array");
    }
    std::copy(items.begin(), items.end(), data_);
  };

  Array &operator=(const Array &v) {
    if (this != &v) {
      std::copy(v.begin(), v.end(), data_);
    }
    return *this;
  };
  Array &operator=(Array &&v) noexcept {
    if (this != &v) {
      std::swap(data_, v.data_);
    }
    return *this;
  };

  ~Array() = default;

  reference operator[](size_type pos) { return data_[pos]; };

  reference at(size_type pos) {
    if (pos >= n) {
      throw std::out_of_range("Index is out of range");
    }
    return data_[pos];
  };
  const_reference front() const { return *data_; };
  const_reference back() const { return *(data_ + n - 1); };
  inline iterator data() noexcept { return data_; };
  inline iterator begin() const noexcept { return iterator(data_); };
  inline iterator end() const noexcept { return iterator(data_ + n); };
  inline bool empty() const noexcept { return n == 0; };
  inline size_type size() const noexcept { return n; };
  size_type max_size() const noexcept { return n; };
  void swap(Array &other) noexcept { std::swap(data_, other.data_); };
  void fill(const_reference value) noexcept {
    for (size_type i = 0; i < n; ++i) {
      data_[i] = value;
    }
  };

 private:
  value_type data_[n];
};

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_Array_H
