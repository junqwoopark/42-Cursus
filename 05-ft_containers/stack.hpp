#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack {
 public:
  typedef Container container_type;
  typedef typename Container::value_type value_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;
  typedef typename Container::size_type size_type;

 protected:
  container_type c;

 public:
  stack(const container_type &container = container_type()) : c(container) {}

  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference top() { return c.back(); }
  const_reference top() const { return c.back(); }

  void push(const value_type &val) { c.push_back(val); }
  void pop() { c.pop_back(); }

  void swap(stack &x) { c.swap(x.c); }

  friend bool operator==(const stack &lhs, const stack &rhs) { return lhs.c == rhs.c; }
  friend bool operator<(const stack &lhs, const stack &rhs) { return lhs.c < rhs.c; }
};

template <class T, class Container>
bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
  return !(lhs == rhs);
}

template <class T, class Container>
bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
  return rhs < lhs;
}

template <class T, class Container>
bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
  return !(rhs < lhs);
}

template <class T, class Container>
bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
  return !(lhs < rhs);
}

}  // namespace ft

#endif
