#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iterator>

#include "type_traits.hpp"

namespace ft {

template <class Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

template <class T>
struct iterator_traits<T *> {
  typedef std::random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef T *pointer;
  typedef T &reference;
};

template <class T>
struct iterator_traits<const T *> {
  typedef std::random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef const T *pointer;
  typedef const T &reference;
};

/*
 * wrap_iterator
 */
template <typename Iterator>
class wrap_iterator {
 protected:
  Iterator current;

 public:
  typedef Iterator iterator_type;
  typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename ft::iterator_traits<Iterator>::value_type value_type;
  typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iterator>::pointer pointer;
  typedef typename ft::iterator_traits<Iterator>::reference reference;

  wrap_iterator() : current(Iterator()) {}

  explicit wrap_iterator(const Iterator &i) : current(i) {}

  template <typename Iter>
  wrap_iterator<Iter>(const wrap_iterator<Iter> &i) : current(i.base()) {}

  reference operator*() const { return *current; }

  pointer operator->() const { return current; }

  wrap_iterator &operator++() {
    ++current;
    return *this;
  }

  wrap_iterator operator++(int) { return wrap_iterator(current++); }

  wrap_iterator &operator--() {
    --current;
    return *this;
  }

  wrap_iterator operator--(int) { return wrap_iterator(current--); }

  reference operator[](const difference_type &n) const { return current[n]; }

  wrap_iterator &operator+=(const difference_type &n) {
    current += n;
    return *this;
  }

  wrap_iterator operator+(const difference_type &n) const { return wrap_iterator(current + n); }

  wrap_iterator &operator-=(const difference_type &n) {
    current -= n;
    return *this;
  }

  wrap_iterator operator-(const difference_type &n) const { return wrap_iterator(current - n); }

  difference_type operator-(const wrap_iterator &i) const { return current - i.current; }

  iterator_type base() const { return current; }
};

template <typename IteratorL, typename IteratorR>
bool operator==(const wrap_iterator<IteratorL> &lhs, const wrap_iterator<IteratorR> &rhs) {
  return lhs.base() == rhs.base();
}

template <typename IteratorL, typename IteratorR>
bool operator!=(const wrap_iterator<IteratorL> &lhs, const wrap_iterator<IteratorR> &rhs) {
  return !(lhs == rhs);
}

template <typename IteratorL, typename IteratorR>
bool operator<(const wrap_iterator<IteratorL> &lhs, const wrap_iterator<IteratorR> &rhs) {
  return lhs.base() < rhs.base();
}

template <typename IteratorL, typename IteratorR>
bool operator>(const wrap_iterator<IteratorL> &lhs, const wrap_iterator<IteratorR> &rhs) {
  return rhs < lhs;
}

template <typename IteratorL, typename IteratorR>
bool operator<=(const wrap_iterator<IteratorL> &lhs, const wrap_iterator<IteratorR> &rhs) {
  return !(rhs < lhs);
}

template <typename IteratorL, typename IteratorR>
bool operator>=(const wrap_iterator<IteratorL> &lhs, const wrap_iterator<IteratorR> &rhs) {
  return !(lhs < rhs);
}

template <typename Iterator>
wrap_iterator<Iterator> operator+(typename wrap_iterator<Iterator>::difference_type n,
                                  const wrap_iterator<Iterator> &i) {
  return wrap_iterator<Iterator>(i.base() + n);
}

/*
** reverse_iterator
** iterator를 역순으로 순회하는 iterator이다.
*/
template <typename Iterator>
class reverse_iterator {
 protected:
  Iterator current;

 public:
  typedef Iterator iterator_type;
  typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename ft::iterator_traits<Iterator>::value_type value_type;
  typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iterator>::pointer pointer;
  typedef typename ft::iterator_traits<Iterator>::reference reference;

  reverse_iterator() : current(Iterator()) {}

  explicit reverse_iterator(const Iterator &i) : current(i) {}

  template <typename Iter>
  reverse_iterator(const reverse_iterator<Iter> &i) : current(i.base()) {}

  reference operator*() const {
    Iterator tmp = current;
    return *--tmp;
  }

  pointer operator->() const { return &(operator*()); }

  reverse_iterator &operator++() {
    --current;
    return *this;
  }

  reverse_iterator operator++(int) { return reverse_iterator(current--); }

  reverse_iterator &operator--() {
    ++current;
    return *this;
  }

  reverse_iterator operator--(int) { return reverse_iterator(current++); }

  reference operator[](const difference_type &n) const { return *(*this + n); }

  reverse_iterator &operator+=(const difference_type &n) {
    current -= n;
    return *this;
  }

  reverse_iterator operator+(const difference_type &n) const { return reverse_iterator(current - n); }

  reverse_iterator &operator-=(const difference_type &n) {
    current += n;
    return *this;
  }

  reverse_iterator operator-(const difference_type &n) const { return reverse_iterator(current + n); }

  difference_type operator-(const reverse_iterator &i) const { return i.current - current; }

  iterator_type base() const { return current; }
};

template <typename IteratorL, typename IteratorR>
bool operator==(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
  return lhs.base() == rhs.base();
}

template <typename IteratorL, typename IteratorR>
bool operator!=(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
  return !(lhs == rhs);
}

template <typename IteratorL, typename IteratorR>
bool operator<(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
  return lhs.base() > rhs.base();
}

template <typename IteratorL, typename IteratorR>
bool operator>(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
  return rhs < lhs;
}

template <typename IteratorL, typename IteratorR>
bool operator<=(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
  return !(rhs < lhs);
}

template <typename IteratorL, typename IteratorR>
bool operator>=(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
  return !(lhs < rhs);
}

template <typename Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
                                     const reverse_iterator<Iterator> &i) {
  return reverse_iterator<Iterator>(i.base() - n);
}

template <typename Iterator>
reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n,
                                     const reverse_iterator<Iterator> &i) {
  return reverse_iterator<Iterator>(i.base() + n);
}

}  // namespace ft

#endif
