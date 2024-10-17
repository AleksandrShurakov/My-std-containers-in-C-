#ifndef CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H
#define CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H

#include <cmath>
#include <initializer_list>

namespace s21 {
template <typename T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  Vector() : size_(0), capacity_(0), data_(nullptr){};

  explicit Vector(size_type n)
      : size_(n), capacity_(n), data_(n ? new value_type[n] : nullptr){};

  explicit Vector(std::initializer_list<value_type> const &items)
      : size_(items.size()),
        capacity_(items.size()),
        data_(new value_type[capacity_]) {
    std::copy(items.begin(), items.end(), data_);
  };

  Vector(const Vector &v)
      : size_(v.size_),
        capacity_(v.capacity_),
        data_(new value_type[capacity_]) {
    for (size_type i = 0; i < size_; ++i) {
      data_[i] = v.data_[i];
    }
  };

  Vector(Vector &&v) noexcept
      : size_(v.size_), capacity_(v.capacity_), data_(v.data_) {
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  };

  Vector &operator=(const Vector &v) {
    if (this != &v) {
      delete[] data_;
      size_ = v.size_;
      capacity_ = v.capacity_;
      data_ = new value_type[capacity_];
      for (size_type i = 0; i < size_; ++i) {
        data_[i] = v.data_[i];
      }
    }
    return *this;
  };

  Vector &operator=(Vector &&v) noexcept {
    if (this != &v) {
      std::swap(size_, v.size_);
      std::swap(capacity_, v.capacity_);
      std::swap(data_, v.data_);
    }
    return *this;
  };

  ~Vector() {
    if (data_) {
      delete[] data_;
      data_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  };

  reference operator[](size_type pos) const { return data_[pos]; };

  reference at(size_type pos) const {
    if (pos >= size()) {
      throw std ::out_of_range("Index is out of range");
    }
    return data_[pos];
  };

  const_reference front() const { return *data_; };
  const_reference back() const { return *(data_ + size_ - 1); };
  inline iterator data() const noexcept { return data_; };
  inline iterator begin() const noexcept { return iterator(data_); };
  inline iterator end() const noexcept { return iterator(data_ + size_); };
  inline bool empty() const noexcept { return size_ == 0; };
  inline size_type size() const noexcept { return size_; };

  size_type max_size() const noexcept {
    int bits = sizeof(void *) == 4 ? 31 : 63;
    return static_cast<size_type>(pow(2, bits)) / sizeof(value_type) - 1;
  };

  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::length_error("Size is too large");
    }
    if (size > size_) {
      allocate(size);
    }
  };

  inline size_type capacity() const noexcept { return capacity_; };

  void shrink_to_fit() {
    if (size_ < capacity_) {
      allocate(size_);
    }
  };

  inline void clear() noexcept { size_ = 0; };

  iterator insert(const_iterator pos, const_reference value) {
    size_type position = pos - data_;
    if (position > size_) {
      throw std::out_of_range("Index is out ot range");
    }
    if (size_ + 1 > capacity_) {
      allocate(size_ + 1);
    }
    size_++;
    value_type tmp = data_[position];
    data_[position] = value;
    for (size_type i = position + 1; i < size_; ++i) {
      value_type next_elem = data_[i];
      data_[i] = tmp;
      tmp = next_elem;
    }
    return data_ + position;
  };

  void erase(const_iterator pos) {
    size_type position = pos - data_;
    if (position > size_) {
      throw std::out_of_range("Index is out ot range");
    }
    size_--;
    for (size_type i = position; i < size_; ++i) {
      data_[i] = data_[i + 1];
    }
  };

  void push_back(value_type v) {
    if (size_ == capacity_) {
      allocate(size_ + size_ + 1);
    }
    data_[size_++] = v;
  };

  void pop_back() noexcept {
    if (size_ > 0) {
      size_--;
    }
  };
  void swap(Vector &other) noexcept {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
  };

  void allocate(size_type size) {
    value_type *buff = new value_type[size];
    for (size_type i = 0; i < size_; ++i) {
      buff[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = buff;
    capacity_ = size;
  };

  template <class... Args>
  iterator insert_many(iterator pos, Args &&...args) {
    return (insert_many_aux(pos, args...));
  }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    insert_many_aux(end(), args...);
  }

 private:
  size_t size_;
  size_t capacity_;
  T *data_;

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

#endif  // CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H
