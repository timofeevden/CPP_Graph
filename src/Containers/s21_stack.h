#ifndef SRC_CONTAINERS_S21_STACK_H_
#define SRC_CONTAINERS_S21_STACK_H_

#include <iostream>

#include "s21_list.h"  // на основе листа

namespace s21 {
template <typename T>
class stack {
 public:
  // *Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // *Stack Member functions*
  stack() : list_() {}

  explicit stack(std::initializer_list<value_type> const &items) : list_() {
    for (const auto &item : items) {
      push(item);
    }
  }

  stack(const stack &s) : list_(s.list_) {}

  stack(stack &&s) noexcept : list_(std::move(s.list_)) {}

  ~stack() { list_.clear(); }

  stack &operator=(const stack &s) {
    list_ = s.list_;
    return *this;
  }

  stack &operator=(stack &&s) noexcept {
    list_ = std::move(s.list_);
    return *this;
  }

  // *Stack Element access*
  const_reference top() const { return list_.front(); }

  // *Stack Capacity*
  bool empty() const noexcept { return (size() == 0); }
  size_type size() const noexcept { return (list_.size()); }

  // *Stack Modifiers*
  void push(const_reference value) { list_.push_front(value); }

  //  void pop() { list_.pop_front(); }

  value_type pop() {
    value_type res = list_.front();
    list_.pop_front();

    return res;
  }

  void swap(stack &other) noexcept { list_.swap(other.list_); }

  // *Bonus
  template <class... Args>
  void insert_many_front(Args &&...args) {
    for (const auto &arg : {args...}) {
      push(arg);
    }
  }

  // *Help function
  void s21_printf_stack() {
    std::cout << "stack: ";
    while (size() > 0) {
      std::cout << "size:" << size() << "value:" << top() << "   ";
      pop();
    }
    std::cout << "\n";
  }

 private:
  list<value_type> list_;
};
}  // namespace s21

#endif  // SRC_CONTAINERS_S21_STACK_H_