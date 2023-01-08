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
  typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename iterator_traits<Iterator>::value_type value_type;
  typedef typename iterator_traits<Iterator>::difference_type difference_type;
  typedef typename iterator_traits<Iterator>::pointer pointer;
  typedef typename iterator_traits<Iterator>::reference reference;

  typedef Iterator iterator_type;

public:
  reverse_iterator() {}
  explicit reverse_iterator(iterator_type x) : current(x) {}

  reverse_iterator(const reverse_iterator &x) : current(x.current) {}
  template <class _Iter> reverse_iterator(const reverse_iterator<_Iter> &x) : current(x.base()) {}

  iterator_type base() const { return current; }
  reference operator*() const {
    Iterator tmp = current;
    return *--tmp;
  }
  pointer operator->() const { return &(operator*()); }

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

  reverse_iterator operator+(difference_type n) const { return reverse_iterator(current - n); }
  reverse_iterator &operator+=(difference_type n) {
    current -= n;
    return *this;
  }
  reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); }
  reverse_iterator &operator-=(difference_type n) {
    current += n;
    return *this;
  }
  reference operator[](difference_type n) const { return *(*this + n); }
};

/*
** reverse_iterator의 비교 연산자
*/
template <class Iterator>
bool operator==(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
  return x.base() == y.base();
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
  return y.base() < x.base();
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
  return !(x == y);
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
  return y < x;
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
  return !(y < x);
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
  return !(x < y);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator> &x, const reverse_iterator<Iterator> &y) {
  return y.base() - x.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
                                     const reverse_iterator<Iterator> &x) {
  return reverse_iterator<Iterator>(x.base() - n);
}

} // namespace ft

#endif
