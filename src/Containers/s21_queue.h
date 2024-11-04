#ifndef SRC_CONTAINERS_S21_QUEUE_H_
#define SRC_CONTAINERS_S21_QUEUE_H_

#include <iostream>

#include "s21_list.h"  // на основе листа

namespace s21 {
template <typename T>
class queue {
 public:
  // *Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // *Queue Member functions*
  queue() : list_() {}

  explicit queue(std::initializer_list<value_type> const &items)
      : list_(items) {}

  queue(const queue &s) : list_(s.list_) {}

  queue(queue &&s) noexcept : list_(std::move(s.list_)) {}

  ~queue() { list_.clear(); }

  queue &operator=(const queue &s) {
    list_ = s.list_;
    return *this;
  }

  queue &operator=(queue &&s) noexcept {
    list_ = std::move(s.list_);
    return *this;
  }

  // *Queue Element access*
  const_reference front() const { return list_.front(); }
  const_reference back() const { return list_.back(); }

  // *Queue Capacity*
  bool empty() const noexcept { return (size() == 0); }
  size_type size() const noexcept { return (list_.size()); }

  // *Queue Modifiers*
  void push(const_reference value) { list_.push_back(value); }

  value_type pop() {
    value_type res = list_.front();
    list_.pop_front();

    return res;
  }

  void swap(queue &other) noexcept { list_.swap(other.list_); }

  // *Bonus
  template <class... Args>
  void insert_many_back(Args &&...args) {
    list_.insert_many_back(std::forward<Args>(args)...);
  }

  // *Help function
  void s21_printf_queue() {
    std::cout << "queue: ";
    while (size() > 0) {
      std::cout << "size:" << size() << "value:" << front() << "   ";
      pop();
    }
    std::cout << "\n";
  }

 private:
  list<value_type> list_;
};
}  // namespace s21

#endif  // SRC_CONTAINERS_S21_QUEUE_H_