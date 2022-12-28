#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft {

/*
** iterator_tag
** iterator의 특성을 나타낸다.
*/
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/*
** iterator
** iterator의 특성을 정의한다.
*/
template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T *, class Reference = T &>
struct iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};

/*
** iterator_traits
** iterator의 특성을 알려준다.
*/
template <class Iterator> struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

template <class T> struct iterator_traits<T *> {
  typedef random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef T *pointer;
  typedef T &reference;
};

template <class T> struct iterator_traits<const T *> {
  typedef random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef const T *pointer;
  typedef const T &reference;
};

/*
** distance
** iterator의 거리를 구한다.
*/
template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
  typename iterator_traits<InputIterator>::difference_type n = 0;
  while (first != last) {
    ++first;
    ++n;
  }
  return n;
}

template <class RandomAccessIterator>
typename iterator_traits<RandomAccessIterator>::difference_type
distance(RandomAccessIterator first, RandomAccessIterator last,
         random_access_iterator_tag) {
  return last - first;
}

template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last, input_iterator_tag) {
  return distance(first, last,
                  typename iterator_traits<InputIterator>::iterator_category());
}

/*
** advance
** iterator을 n만큼 이동시킨다.
*/
template <class InputIterator, class Distance>
void advance(InputIterator &i, Distance n, input_iterator_tag) {
  while (n--)
    ++i;
}

template <class BidirectionalIterator, class Distance>
void advance(BidirectionalIterator &i, Distance n, bidirectional_iterator_tag) {
  if (n >= 0)
    while (n--)
      ++i;
  else
    while (n++)
      --i;
}

template <class RandomAccessIterator, class Distance>
void advance(RandomAccessIterator &i, Distance n, random_access_iterator_tag) {
  i += n;
}

template <class InputIterator, class Distance>
void advance(InputIterator &i, Distance n) {
  advance(i, n, typename iterator_traits<InputIterator>::iterator_category());
}

/*
** reverse_iterator
** iterator를 역순으로 순회하는 iterator이다.
*/
template <class Iterator> class reverse_iterator {
protected:
  Iterator current;

public:
  typedef
      typename iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename iterator_traits<Iterator>::value_type value_type;
  typedef typename iterator_traits<Iterator>::difference_type difference_type;
  typedef typename iterator_traits<Iterator>::pointer pointer;
  typedef typename iterator_traits<Iterator>::reference reference;

  typedef Iterator iterator_type;
  typedef reverse_iterator<Iterator> self;

public:
  reverse_iterator() {}
  explicit reverse_iterator(iterator_type x) : current(x) {}
  reverse_iterator(const self &x) : current(x.current) {}

  iterator_type base() const { return current; }

  reference operator*() const {
    Iterator tmp = current;
    return *--tmp;
  }
  pointer operator->() const { return &(operator*()); }

  self &operator++() {
    --current;
    return *this;
  }
  self operator++(int) {
    self tmp = *this;
    --current;
    return tmp;
  }
  self &operator--() {
    ++current;
    return *this;
  }
  self operator--(int) {
    self tmp = *this;
    ++current;
    return tmp;
  }

  self operator+(difference_type n) const { return self(current - n); }
  self &operator+=(difference_type n) {
    current -= n;
    return *this;
  }
  self operator-(difference_type n) const { return self(current + n); }
  self &operator-=(difference_type n) {
    current += n;
    return *this;
  }

  reference operator[](difference_type n) const { return *(*this + n); }
};

template <class Iterator>
inline bool operator==(const reverse_iterator<Iterator> &x,
                       const reverse_iterator<Iterator> &y) {
  return x.base() == y.base();
}

template <class Iterator>
inline bool operator<(const reverse_iterator<Iterator> &x,
                      const reverse_iterator<Iterator> &y) {
  return y.base() < x.base();
}

template <class Iterator>
inline typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator> &x,
          const reverse_iterator<Iterator> &y) {
  return y.base() - x.base();
}

template <class Iterator>
inline reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n,
          const reverse_iterator<Iterator> &x) {
  return reverse_iterator<Iterator>(x.base() - n);
}

template <class Iterator>
inline bool operator!=(const reverse_iterator<Iterator> &x,
                       const reverse_iterator<Iterator> &y) {
  return !(x == y);
}

template <class Iterator>
inline bool operator>(const reverse_iterator<Iterator> &x,
                      const reverse_iterator<Iterator> &y) {
  return y < x;
}

template <class Iterator>
inline bool operator<=(const reverse_iterator<Iterator> &x,
                       const reverse_iterator<Iterator> &y) {
  return !(y < x);
}

template <class Iterator>
inline bool operator>=(const reverse_iterator<Iterator> &x,
                       const reverse_iterator<Iterator> &y) {
  return !(x < y);
}

} // namespace ft

#endif
