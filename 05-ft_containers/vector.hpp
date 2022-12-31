#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace ft {

template <typename Iterator>
class vector_iterator
    : public std::iterator<
          typename ft::iterator_traits<Iterator>::iterator_category,
          typename ft::iterator_traits<Iterator>::value_type,
          typename ft::iterator_traits<Iterator>::difference_type,
          typename ft::iterator_traits<Iterator>::pointer,
          typename ft::iterator_traits<Iterator>::reference> {

protected:
  Iterator _M_current;

public:
  typedef Iterator iterator_type;
  typedef typename ft::iterator_traits<Iterator>::iterator_category
      iterator_category;
  typedef typename ft::iterator_traits<Iterator>::value_type value_type;
  typedef
      typename ft::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iterator>::pointer pointer;
  typedef typename ft::iterator_traits<Iterator>::reference reference;

  vector_iterator() : _M_current(Iterator()) {}

  explicit vector_iterator(const Iterator &__i) : _M_current(__i) {}

  // Allow iterator to const_iterator conversion
  template <typename _Iter>
  inline vector_iterator(const vector_iterator<_Iter> &__i)
      : _M_current(__i.base()) {}

  // Forward iterator requirements
  reference operator*() const { return *_M_current; }

  pointer operator->() const { return _M_current; }

  iterator_type &operator++() {
    ++_M_current;
    return *this;
  }

  iterator_type operator++(int) { return vector_iterator(_M_current++); }

  // Bidirectional iterator requirements
  iterator_type &operator--() {
    --_M_current;
    return *this;
  }

  iterator_type operator--(int) { return vector_iterator(_M_current--); }

  // Random access iterator requirements
  reference operator[](const difference_type &__n) const {
    return _M_current[__n];
  }

  iterator_type &operator+=(const difference_type &__n) {
    _M_current += __n;
    return *this;
  }

  iterator_type operator+(const difference_type &__n) const {
    return vector_iterator(_M_current + __n);
  }

  iterator_type &operator-=(const difference_type &__n) {
    _M_current -= __n;
    return *this;
  }

  iterator_type operator-(const difference_type &__n) const {
    return vector_iterator(_M_current - __n);
  }

  difference_type operator-(const iterator_type &__i) const {
    return _M_current - __i._M_current;
  }

  const Iterator &base() const { return _M_current; }
};

template <typename _IteratorL, typename _IteratorR>
inline bool operator==(const vector_iterator<_IteratorL> &__lhs,
                       const vector_iterator<_IteratorR> &__rhs) {
  return __lhs.base() == __rhs.base();
}

template <typename _IteratorL, typename _IteratorR>
inline bool operator!=(const vector_iterator<_IteratorL> &__lhs,
                       const vector_iterator<_IteratorR> &__rhs) {
  return !(__lhs == __rhs);
}

// random access iterator requirements

template <typename _IteratorL, typename _IteratorR>
inline bool operator<(const vector_iterator<_IteratorL> &__lhs,
                      const vector_iterator<_IteratorR> &__rhs) {
  return __lhs.base() < __rhs.base();
}

template <typename _IteratorL, typename _IteratorR>
inline bool operator>(const vector_iterator<_IteratorL> &__lhs,
                      const vector_iterator<_IteratorR> &__rhs) {
  return __rhs < __lhs;
}

template <typename _IteratorL, typename _IteratorR>
inline bool operator<=(const vector_iterator<_IteratorL> &__lhs,
                       const vector_iterator<_IteratorR> &__rhs) {
  return !(__rhs < __lhs);
}

template <typename _IteratorL, typename _IteratorR>
inline bool operator>=(const vector_iterator<_IteratorL> &__lhs,
                       const vector_iterator<_IteratorR> &__rhs) {
  return !(__lhs < __rhs);
}

template <typename _Iterator>
inline vector_iterator<_Iterator>
operator+(typename vector_iterator<_Iterator>::difference_type __n,
          const vector_iterator<_Iterator> &__i) {
  return vector_iterator<_Iterator>(__i.base() + __n);
}

template <class T, class _Alloc = std::allocator<T> > class Vector_base {
public:
  typedef _Alloc allocator_type;
  allocator_type get_allocator() const { return allocator; }

  Vector_base(const _Alloc &)
      : _M_start(0), _M_finish(0), _M_end_of_storage(0) {}
  Vector_base(size_t n, const _Alloc &)
      : _M_start(0), _M_finish(0), _M_end_of_storage(0) {
    _M_start = _M_allocate(n);
    _M_finish = _M_start;
    _M_end_of_storage = _M_start + n;
  }

  ~Vector_base() { _M_deallocate(_M_start, _M_end_of_storage - _M_start); }

protected:
  allocator_type allocator;
  T *_M_start;
  T *_M_finish;
  T *_M_end_of_storage;

  T *_M_allocate(size_t n) { return allocator.allocate(n); }
  void _M_deallocate(T *__p, size_t n) { allocator.deallocate(__p, n); }
  void construct(T *p, const T &val) { allocator.construct(p, val); }
  template <class ForwardIterator>
  void destroy(ForwardIterator first, ForwardIterator last) {
    for (; first != last; ++first)
      allocator.destroy(&*first);
  }
  void destroy(T *p) { allocator.destroy(p); }
};

template <class T, class Alloc = std::allocator<T> >
class vector : protected Vector_base<T, Alloc> {
private:
  typedef Vector_base<T, Alloc> Base;

public:
  typedef T value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef vector_iterator<pointer> iterator;
  typedef vector_iterator<const_pointer> const_iterator;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename Base::allocator_type allocator_type;
  allocator_type get_allocator() const { return Base::get_allocator(); }

  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;

protected:
  using Base::_M_allocate;
  using Base::_M_deallocate;
  using Base::_M_end_of_storage;
  using Base::_M_finish;
  using Base::_M_start;
  using Base::allocator;
  using Base::construct;
  using Base::destroy;

  void _M_insert_aux(iterator position, const T &x) {
    if (_M_finish != _M_end_of_storage) {
      construct(_M_finish, *(_M_finish - 1));
      ++_M_finish;
      T x_copy = x;
      std::copy_backward(position, iterator(_M_finish - 2),
                         iterator(_M_finish - 1));
      *position = x_copy;
    } else {
      const size_type old_size = size();
      const size_type len = old_size != 0 ? 2 * old_size : 1;
      iterator __new_start(_M_allocate(len));
      iterator __new_finish(__new_start);
      try {
        __new_finish = std::uninitialized_copy(begin(), position, __new_start);
        construct(__new_finish.base(), x);
        ++__new_finish;
        __new_finish = std::uninitialized_copy(position, end(), __new_finish);
      } catch (...) {
        destroy(__new_start, __new_finish);
        _M_deallocate(__new_start.base(), len);
        throw;
      }
      destroy(begin(), end());
      _M_deallocate(_M_start, _M_end_of_storage - _M_start);
      _M_start = __new_start.base();
      _M_finish = __new_finish.base();
      _M_end_of_storage = __new_start.base() + len;
    }
  };

public:
  iterator begin() { return iterator(_M_start); }
  const_iterator begin() const { return const_iterator(_M_start); }
  iterator end() { return iterator(_M_finish); }
  const_iterator end() const { return const_iterator(_M_finish); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

  size_type size() const { return size_type(end() - begin()); }
  size_type max_size() const { return size_type(-1) / sizeof(T); }
  size_type capacity() const {
    return size_type(const_iterator(_M_end_of_storage) - begin());
  }
  bool empty() const { return begin() == end(); }

  reference operator[](size_type n) { return *(begin() + n); }
  const_reference operator[](size_type n) const { return *(begin() + n); }

  void _M_range_check(size_type n) const {
    if (n >= this->size())
      throw std::out_of_range("vector");
  }

  reference at(size_type n) {
    _M_range_check(n);
    return (*this)[n];
  }
  const_reference at(size_type n) const {
    _M_range_check(n);
    return (*this)[n];
  }

  explicit vector(const allocator_type &a = allocator_type()) : Base(a) {}
  vector(size_type n, const T &value,
         const allocator_type &a = allocator_type())
      : Base(n, a) {
    _M_finish = std::uninitialized_fill_n(_M_start, n, value);
  }

  explicit vector(size_type n) : Base(n, allocator_type()) {
    _M_finish = std::uninitialized_fill_n(_M_start, n, T());
  }

  vector(const vector<T, Alloc> &x) : Base(x.size(), x.get_allocator()) {
    _M_finish = std::uninitialized_copy(x.begin(), x.end(), _M_start);
  }

  template <class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type &a = allocator_type(),
         typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type
             * = 0)
      : Base(a) {
    _M_range_initialize(
        first, last,
        typename ft::iterator_traits<InputIterator>::iterator_category());
  }

  ~vector() { destroy(_M_start, _M_finish); }

  vector<T, Alloc> &operator=(const vector<T, Alloc> &x) {
    if (this != &x) {
      const size_type xlen = x.size();
      pointer tmp = _M_allocate_and_copy(xlen, x.begin(), x.end());
      destroy(_M_start, _M_finish);
      _M_deallocate(_M_start, _M_end_of_storage - _M_start);
      _M_start = tmp;
      _M_end_of_storage = _M_start + xlen;
      _M_finish = _M_start + xlen;
    }
    return *this;
  }

  void reserve(size_type n) {
    if (capacity() < n) {
      const size_type old_size = size();
      pointer tmp = _M_allocate_and_copy(n, _M_start, _M_finish);
      destroy(_M_start, _M_finish);
      _M_deallocate(_M_start, _M_end_of_storage - _M_start);
      _M_start = tmp;
      _M_finish = tmp + old_size;
      _M_end_of_storage = _M_start + n;
    }
  }

  void assign(size_type n, const T &val) {
    if (n > capacity()) {
      vector<T, Alloc> tmp(n, val, get_allocator());
      tmp.swap(*this);
    } else if (n > size()) {
      std::fill(begin(), end(), val);
      _M_finish = std::uninitialized_fill_n(_M_finish, n - size(), val);
    } else {
      erase(std::fill_n(begin(), n, val), end());
    }
  }

  template <class InputIterator>
  void assign(
      InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
          0) {
    _M_assign_aux(
        first, last,
        typename ft::iterator_traits<InputIterator>::iterator_category());
  }

  template <class InputIterator>
  void _M_assign_aux(InputIterator first, InputIterator last,
                     std::input_iterator_tag);

  template <class ForwardIterator>
  void _M_assign_aux(ForwardIterator first, ForwardIterator last,
                     std::forward_iterator_tag);

  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(end() - 1); }
  const_reference back() const { return *(end() - 1); }

  void push_back(const T &x) {
    if (_M_finish != _M_end_of_storage) {
      construct(_M_finish, x);
      ++_M_finish;
    } else
      _M_insert_aux(end(), x);
  }

  void swap(vector<T, Alloc> &x) {
    std::swap(_M_start, x._M_start);
    std::swap(_M_finish, x._M_finish);
    std::swap(_M_end_of_storage, x._M_end_of_storage);
  }

  iterator insert(iterator position, const T &x) {
    size_type n = position - begin();
    if (_M_finish != _M_end_of_storage && position == end()) {
      construct(_M_finish, x);
      ++_M_finish;
    } else
      _M_insert_aux(position, x);
    return begin() + n;
  }

  void insert(iterator position, size_type n, const T &x) {
    if (n != 0) {
      if (size_type(_M_end_of_storage - _M_finish) >= n) {
        T x_copy = x;
        const size_type elems_after = end() - position;
        iterator old_finish = end();
        if (elems_after > n) {
          std::uninitialized_copy(_M_finish - n, _M_finish, _M_finish);
          _M_finish += n;
          std::copy_backward(position, old_finish - n, old_finish);
          std::fill(position, position + n, x_copy);
        } else {
          std::uninitialized_fill_n(_M_finish, n - elems_after, x_copy);
          _M_finish += n - elems_after;
          std::uninitialized_copy(position, old_finish, _M_finish);
          _M_finish += elems_after;
          std::fill(position, old_finish, x_copy);
        }
      } else {
        const size_type old_size = size();
        const size_type len =
            capacity() != 0 ? std::max(2 * capacity(), old_size + n) : 1;
        iterator new_start(_M_allocate(len));
        iterator new_finish(new_start);
        try {
          new_finish = std::uninitialized_copy(begin(), position, new_start);
          new_finish = std::uninitialized_fill_n(new_finish, n, x);
          new_finish = std::uninitialized_copy(position, end(), new_finish);
        } catch (...) {
          destroy(new_start, new_finish);
          _M_deallocate(new_start.base(), len);
          throw;
        }
        destroy(_M_start, _M_finish);
        _M_deallocate(_M_start, _M_end_of_storage - _M_start);
        _M_start = new_start.base();
        _M_finish = new_finish.base();
        _M_end_of_storage = new_start.base() + len;
      }
    }
  }

  template <class InputIterator>
  void insert(
      iterator position, InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
          0) {
    _M_range_insert(
        position, first, last,
        typename ft::iterator_traits<InputIterator>::iterator_category());
  }

  void pop_back() {
    --_M_finish;
    destroy(_M_finish);
  }
  iterator erase(iterator position) {
    if (position + 1 != end())
      std::copy(position + 1, end(), position);
    --_M_finish;
    allocator.destroy(_M_finish);

    return position;
  }
  iterator erase(iterator first, iterator last) {
    if (first != last) {
      if (last != end()) {
        iterator i = std::copy(last, end(), first);
        destroy(i, end());
      }
    }
    _M_finish = _M_finish - (last - first);
    return first;
  }

  void resize(size_type new_size, const T &x) {
    if (new_size < size()) {
      erase(begin() + new_size, end());
    } else {
      insert(end(), new_size - size(), x);
    }
  }

  void resize(size_type new_size) { resize(new_size, T()); }
  void clear() { erase(begin(), end()); }

protected:
  template <class ForwardIterator>
  pointer _M_allocate_and_copy(size_type n, ForwardIterator first,
                               ForwardIterator last) {
    pointer result = _M_allocate(n);
    try {
      std::uninitialized_copy(first, last, result);
      return result;
    } catch (...) {
      _M_deallocate(result, n);
      throw;
    }
  }

  template <class InputIterator>
  void _M_range_initialize(InputIterator first, InputIterator last,
                           std::input_iterator_tag) {
    for (; first != last; ++first)
      push_back(*first);
  }

  template <class ForwardIterator>
  void _M_range_initialize(ForwardIterator first, ForwardIterator last,
                           std::forward_iterator_tag) {
    size_type n = 0;
    n = std::distance(first, last);
    _M_start = _M_allocate(n);
    _M_end_of_storage = _M_start + n;
    _M_finish = std::uninitialized_copy(first, last, _M_start);
  }

  template <class InputIterator>
  void _M_range_insert(iterator pos, InputIterator first, InputIterator last,
                       std::input_iterator_tag) {
    for (; first != last; ++first) {
      pos = insert(pos, *first);
      ++pos;
    }
  }

  template <class ForwardIterator>
  void _M_range_insert(iterator pos, ForwardIterator first,
                       ForwardIterator last, std::forward_iterator_tag) {
    if (first != last) {
      size_type n = 0;
      n = std::distance(first, last);
      if (size_type(_M_end_of_storage - _M_finish) >= n) {
        const size_type elems_after = end() - pos;
        iterator old_finish(_M_finish);
        if (elems_after > n) {
          std::uninitialized_copy(_M_finish - n, _M_finish, _M_finish);
          _M_finish += n;
          std::copy_backward(pos, old_finish - n, old_finish);
          std::copy(first, last, pos);
        } else {
          ForwardIterator mid = first;
          std::advance(mid, elems_after);
          std::uninitialized_copy(mid, last, _M_finish);
          _M_finish += n - elems_after;
          std::uninitialized_copy(pos, old_finish, _M_finish);
          _M_finish += elems_after;
          std::copy(first, mid, pos);
        }
      } else {
        const size_type old_size = size();
        const size_type len = old_size + std::max(old_size, n);
        iterator new_start(_M_allocate(len));
        iterator new_finish(new_start);
        try {
          new_finish = std::uninitialized_copy(begin(), pos, new_start);
          new_finish = std::uninitialized_copy(first, last, new_finish);
          new_finish = std::uninitialized_copy(pos, end(), new_finish);
        } catch (...) {
          destroy(new_start, new_finish);
          _M_deallocate(new_start.base(), len);
          throw;
        }
        destroy(_M_start, _M_finish);
        _M_deallocate(_M_start, _M_end_of_storage - _M_start);
        _M_start = new_start.base();
        _M_finish = new_finish.base();
        _M_end_of_storage = new_start.base() + len;
      }
    }
  }
};

template <class T, class Alloc>
bool operator==(const vector<T, Alloc> &x, const vector<T, Alloc> &y) {
  return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}
template <class T, class Alloc>
bool operator<(const vector<T, Alloc> &x, const vector<T, Alloc> &y) {
  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}
template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> &x, const vector<T, Alloc> &y) {
  return !(x == y);
}
template <class T, class Alloc>
bool operator>(const vector<T, Alloc> &x, const vector<T, Alloc> &y) {
  return y < x;
}
template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> &x, const vector<T, Alloc> &y) {
  return !(x < y);
}
template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> &x, const vector<T, Alloc> &y) {
  return !(y < x);
}

template <class T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
  x.swap(y);
}

template <class T, class Alloc>
template <class InputIterator>
void vector<T, Alloc>::_M_assign_aux(InputIterator first, InputIterator last,
                                     std::input_iterator_tag) {
  iterator cur = begin();
  for (; first != last && cur != end(); ++cur, ++first)
    *cur = *first;
  if (first == last)
    erase(cur, end());
  else
    insert(end(), first, last);
}

template <class T, class Alloc>
template <class ForwardIterator>
void vector<T, Alloc>::_M_assign_aux(ForwardIterator first,
                                     ForwardIterator last,
                                     std::forward_iterator_tag) {
  size_type len = std::distance(first, last);

  if (len > capacity()) {
    pointer __tmp = _M_allocate_and_copy(len, first, last);
    destroy(_M_start, _M_finish);
    _M_deallocate(_M_start, _M_end_of_storage - _M_start);
    _M_start = __tmp;
    _M_end_of_storage = _M_finish = _M_start + len;
  } else if (size() >= len) {
    iterator new_finish(std::copy(first, last, _M_start));
    destroy(new_finish, end());
    _M_finish = new_finish.base();
  } else {
    ForwardIterator mid = first;
    std::advance(mid, size());
    std::copy(first, mid, _M_start);
    _M_finish = std::uninitialized_copy(mid, last, _M_finish);
  }
}

} // namespace ft
#endif
