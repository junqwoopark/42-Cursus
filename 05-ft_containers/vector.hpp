#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>

#include "iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace ft {

template <class T>
class vector_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {
public:
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ptrdiff_t difference_type;
  typedef ft::random_access_iterator_tag iterator_category;

private:
  pointer _ptr;

public:
  vector_iterator() : _ptr(0) {}
  vector_iterator(pointer ptr) : _ptr(ptr) {}
  vector_iterator(const vector_iterator &x) { *this = x; }
  ~vector_iterator() {}

  vector_iterator &operator=(const vector_iterator &x) {
    if (this != &x) {
      _ptr = x._ptr;
    }
    return *this;
  }

  reference operator*() const { return *_ptr; }
  pointer operator->() const { return _ptr; }

  vector_iterator &operator++() {
    ++_ptr;
    return *this;
  }
  vector_iterator operator++(int) {
    vector_iterator tmp(*this);
    ++_ptr;
    return tmp;
  }
  vector_iterator &operator--() {
    --_ptr;
    return *this;
  }
  vector_iterator operator--(int) {
    vector_iterator tmp(*this);
    --_ptr;
    return tmp;
  }

  vector_iterator operator+(difference_type n) const {
    return vector_iterator(_ptr + n);
  }
  vector_iterator operator-(difference_type n) const {
    return vector_iterator(_ptr - n);
  }
  vector_iterator &operator+=(difference_type n) {
    _ptr += n;
    return *this;
  }
  vector_iterator &operator-=(difference_type n) {
    _ptr -= n;
    return *this;
  }

  reference operator[](difference_type n) const { return _ptr[n]; }

  friend bool operator==(const vector_iterator &x, const vector_iterator &y) {
    return x._ptr == y._ptr;
  }
  friend bool operator!=(const vector_iterator &x, const vector_iterator &y) {
    return x._ptr != y._ptr;
  }
  friend bool operator<(const vector_iterator &x, const vector_iterator &y) {
    return x._ptr < y._ptr;
  }
  friend bool operator<=(const vector_iterator &x, const vector_iterator &y) {
    return x._ptr <= y._ptr;
  }
  friend bool operator>(const vector_iterator &x, const vector_iterator &y) {
    return x._ptr > y._ptr;
  }
  friend bool operator>=(const vector_iterator &x, const vector_iterator &y) {
    return x._ptr >= y._ptr;
  }
  friend difference_type operator-(const vector_iterator &x,
                                   const vector_iterator &y) {
    return x._ptr - y._ptr;
  }
};

template <class T, class Alloc = std::allocator<T> > class vector_base {
public:
  typedef Alloc allocator_type;
  typedef typename allocator_type::value_type value_type;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;

  allocator_type get_allocator() const { return allocator_type(); }
  pointer allocate(size_type n) { return get_allocator().allocate(n); }
  void deallocate(pointer p, size_type n) { get_allocator().deallocate(p, n); }
  void construct(pointer p, const value_type &val) {
    get_allocator().construct(p, val);
  }
  void destroy(pointer p) { get_allocator().destroy(p); }
};

template <class T, class Alloc = std::allocator<T> >
class vector : public vector_base<T, Alloc> {
public:
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef vector_iterator<T> iterator;
  typedef vector_iterator<const T> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

private:
  allocator_type _alloc;
  size_type _size;
  size_type _capacity;
  pointer _data;

  using vector_base<T, Alloc>::allocate;
  using vector_base<T, Alloc>::deallocate;
  using vector_base<T, Alloc>::construct;
  using vector_base<T, Alloc>::destroy;

public:
  // constructors
  // (1) empty container constructor (default constructor)
  explicit vector(const allocator_type &alloc = allocator_type())
      : _alloc(alloc), _size(0), _capacity(0), _data(0) {}
  // (2) fill constructor
  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type())
      : _alloc(alloc), _size(n), _capacity(n), _data(allocate(n)) {
    for (size_type i = 0; i < n; ++i) {
      construct(_data + i, val);
    }
  }
  // (3) range constructor
  template <class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type &alloc = allocator_type(),
         typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type
             * = 0)
      : _alloc(alloc), _size(0), _capacity(0), _data(0) {
    assign(first, last);
  }
  // (4) copy constructor
  vector(const vector &x) {
    _alloc = x._alloc;
    _size = x._size;
    _capacity = x._capacity;
    _data = allocate(_capacity);
    for (size_type i = 0; i < _size; ++i) {
      construct(_data + i, x._data[i]);
    }
  }

  // destructor
  ~vector() {
    clear();
    deallocate(_data, _capacity);
  }

  // operator=
  vector &operator=(const vector &x) {
    if (this != &x) {
      clear();
      deallocate(_data, _capacity);
      _alloc = x._alloc;
      _size = x._size;
      _capacity = x._capacity;
      _data = allocate(_capacity);
      for (size_type i = 0; i < _size; ++i) {
        construct(_data + i, x._data[i]);
      }
    }
    return *this;
  }

  // iterators
  iterator begin() { return iterator(_data); }
  iterator end() { return iterator(_data + _size); }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_iterator cbegin() const { return const_iterator(_data); }
  const_iterator cend() const { return const_iterator(_data + _size); }
  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(begin());
  }

  // capacity
  size_type size() const { return _size; }
  size_type max_size() const { return get_allocator().max_size(); }
  void resize(size_type n, value_type val = value_type()) {
    if (n > _size) {
      if (n > _capacity) {
        reserve(std::max(_capacity * 2, n));
      }
      for (size_type i = _size; i < n; ++i) {
        construct(_data + i, val);
      }
    } else if (n < _size) {
      for (size_type i = n; i < _size; ++i) {
        destroy(_data + i);
      }
    }
    _size = n;
  }
  size_type capacity() const { return _capacity; }
  bool empty() const { return _size == 0; }
  void reserve(size_type n) {
    if (n > _capacity) {
      pointer tmp = allocate(n);
      for (size_type i = 0; i < _size; ++i) {
        construct(tmp + i, _data[i]);
        destroy(_data + i);
      }
      deallocate(_data, _capacity);
      _data = tmp;
      _capacity = n;
    }
  }
  void shrink_to_fit() {
    if (_size < _capacity) {
      pointer tmp = allocate(_size);
      for (size_type i = 0; i < _size; ++i) {
        construct(tmp + i, _data[i]);
        destroy(_data + i);
      }
      deallocate(_data, _capacity);
      _data = tmp;
      _capacity = _size;
    }
  }

  // element access
  reference operator[](size_type n) { return _data[n]; }
  const_reference operator[](size_type n) const { return _data[n]; }
  reference at(size_type n) {
    if (n >= _size) {
      throw std::out_of_range("vector");
    }
    return _data[n];
  }
  const_reference at(size_type n) const {
    if (n >= _size) {
      throw std::out_of_range("vector");
    }
    return _data[n];
  }
  reference front() { return _data[0]; }
  const_reference front() const { return _data[0]; }
  reference back() { return _data[_size - 1]; }
  const_reference back() const { return _data[_size - 1]; }
  pointer data() { return _data; }

  // modifiers
  template <class InputIterator>
  void assign(
      InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
          0) {
    clear();
    if (last - first > _capacity) {
      reserve(last - first);
    }
    while (first != last) {
      push_back(*first);
      ++first;
    }
  }
  void assign(size_type n, const value_type &val) {
    clear();
    if (n > _capacity) {
      reserve(n);
    }
    for (size_type i = 0; i < n; ++i) {
      push_back(val);
    }
  }
  void push_back(const value_type &val) {
    if (_size == _capacity) {
      reserve(_capacity == 0 ? 1 : _capacity * 2);
    }
    construct(_data + _size, val);
    ++_size;
  }
  void pop_back() {
    if (_size > 0) {
      destroy(_data + _size - 1);
      --_size;
    }
  }
  iterator insert(iterator position, const value_type &val) {
    size_type pos = position - begin();
    if (_size == _capacity) {
      reserve(std::max(_size + 1, _capacity * 2));
    }
    for (size_type i = _size; i > pos; --i) {
      construct(_data + i, _data[i - 1]);
      destroy(_data + i - 1);
    }
    construct(_data + pos, val);
    ++_size;
    return begin() + pos;
  }
  void insert(iterator position, size_type n, const value_type &val) {
    size_type pos = position - begin();
    if (_size + n > _capacity) {
      reserve(std::max(_size + n, _capacity * 2));
    }
    for (size_type i = _size; i > pos; --i) {
      construct(_data + i + n - 1, _data[i - 1]);
      destroy(_data + i - 1);
    }
    for (size_type i = 0; i < n; ++i) {
      construct(_data + pos + i, val);
    }
    _size += n;
  }

  template <class InputIterator>
  void insert(
      iterator position, InputIterator first, InputIterator last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
          0) {
    try {
      size_type pos = position - begin();
      size_type n = last - first;
      if (_size + n > _capacity) {
        reserve(std::max(_size + n, _capacity * 2));
      }
      for (size_type i = _size; i > pos; --i) {
        construct(_data + i + n - 1, _data[i - 1]);
        destroy(_data + i - 1);
      }
      for (size_type i = 0; i < n; ++i) {
        construct(_data + pos + i, *first);
        ++first;
      }
      _size += n;
    } catch (...) {
      clear();
      shrink_to_fit();
      throw;
    }
  }

  iterator erase(iterator position) {
    size_type pos = position - begin();
    for (size_type i = pos; i < _size - 1; ++i) {
      construct(_data + i, _data[i + 1]);
      destroy(_data + i + 1);
    }
    destroy(_data + _size - 1);
    --_size;
    return begin() + pos;
  }
  iterator erase(iterator first, iterator last) {
    size_type pos = first - begin();
    size_type n = last - first;
    for (size_type i = pos; i < _size - n; ++i) {
      construct(_data + i, _data[i + n]);
      destroy(_data + i + n);
    }
    for (size_type i = 0; i < n; ++i) {
      destroy(_data + _size - 1 - i);
    }
    _size -= n;
    return begin() + pos;
  }
  void swap(vector &x) {
    std::swap(_data, x._data);
    std::swap(_size, x._size);
    std::swap(_capacity, x._capacity);
  }
  void clear() {
    for (size_type i = 0; i < _size; ++i) {
      destroy(_data + i);
    }
    _size = 0;
  }

  // allocator
  allocator_type get_allocator() const { return _alloc; }
};

template <class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (size_t i = 0; i < lhs.size(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  size_t i = 0;
  while (i < lhs.size() && i < rhs.size()) {
    if (lhs[i] < rhs[i]) {
      return true;
    } else if (lhs[i] > rhs[i]) {
      return false;
    }
    ++i;
  }
  return lhs.size() < rhs.size();
}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return rhs < lhs;
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
  return !(lhs < rhs);
}

template <class T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
  x.swap(y);
}

} // namespace ft
#endif
