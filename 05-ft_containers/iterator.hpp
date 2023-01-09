#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "type_traits.hpp"
#include <cstddef>
#include <iterator>

namespace ft {

template <class Iterator> struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

template <class T> struct iterator_traits<T *> {
  typedef std::random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef T *pointer;
  typedef T &reference;
};

template <class T> struct iterator_traits<const T *> {
  typedef std::random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef const T *pointer;
  typedef const T &reference;
};

/*
** reverse_iterator
** iterator를 역순으로 순회하는 iterator이다.
*/
template <class Iterator> class reverse_iterator {
protected:
  Iterator current;

public:
  typedef Iterator iterator_type;
  typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename ft::iterator_traits<Iterator>::value_type value_type;
  typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iterator>::pointer pointer;
  typedef typename ft::iterator_traits<Iterator>::reference reference;

  reverse_iterator() {}

  explicit reverse_iterator(Iterator x) : current(x) {}

  reverse_iterator(const reverse_iterator &x) : current(x.current) {}
  template <class Iter> reverse_iterator(const reverse_iterator<Iter> &x) : current(x.base()) {}

  reference operator*() const {
    Iterator tmp = current;
    return *--tmp;
  }

  pointer operator->() const { return &(operator*()); }

  reference operator[](difference_type n) const { return *(*this + n); }

  reverse_iterator &operator++() {
    --current;
    return *this;
  }

  reverse_iterator operator++(int) {
    reverse_iterator tmp = *this;
    --current;
    return tmp;
  }

  reverse_iterator &operator--() {
    ++current;
    return *this;
  }

  reverse_iterator operator--(int) {
    reverse_iterator tmp = *this;
    ++current;
    return tmp;
  }

  reverse_iterator &operator+=(const difference_type &n) {
    current -= n;
    return *this;
  }

  reverse_iterator operator+(const difference_type &n) const {
    return reverse_iterator(current - n);
  }

  reverse_iterator &operator-=(const difference_type &n) {
    current += n;
    return *this;
  }

  reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); }

  difference_type operator-(const reverse_iterator &i) const {
    return reverse_iterator(current - i.current);
  }

  iterator_type base() const { return current; }
};

/*
** reverse_iterator의 비교 연산자
*/
template <class IteratorL, class IteratorR>
bool operator==(const reverse_iterator<IteratorL> &x, const reverse_iterator<IteratorR> &y) {
  return x.base() == y.base();
}

template <class IteratorL, class IteratorR>
bool operator<(const reverse_iterator<IteratorL> &x, const reverse_iterator<IteratorR> &y) {
  return y.base() < x.base();
}

template <class IteratorL, class IteratorR>
bool operator!=(const reverse_iterator<IteratorL> &x, const reverse_iterator<IteratorR> &y) {
  return !(x == y);
}

template <class IteratorL, class IteratorR>
bool operator>(const reverse_iterator<IteratorL> &x, const reverse_iterator<IteratorR> &y) {
  return y < x;
}

template <class IteratorL, class IteratorR>
bool operator<=(const reverse_iterator<IteratorL> &x, const reverse_iterator<IteratorR> &y) {
  return !(y < x);
}

template <class IteratorL, class IteratorR>
bool operator>=(const reverse_iterator<IteratorL> &x, const reverse_iterator<IteratorR> &y) {
  return !(x < y);
}

template <class IteratorL, class IteratorR>
typename reverse_iterator<IteratorL>::difference_type
operator-(const reverse_iterator<IteratorL> &x, const reverse_iterator<IteratorR> &y) {
  return y.base() - x.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
                                     const reverse_iterator<Iterator> &x) {
  return reverse_iterator<Iterator>(x.base() - n);
}

} // namespace ft

#endif
