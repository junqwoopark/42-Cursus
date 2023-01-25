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

template <class T, class Alloc = std::allocator<T> >
class Vector_base {
 public:
  typedef Alloc allocator_type;

  Vector_base(const Alloc &) : start(0), finish(0), end_of_storage(0) {}
  Vector_base(size_t n, const Alloc &) : start(0), finish(0), end_of_storage(0) {
    start = allocate(n);
    finish = start;
    end_of_storage = start + n;
  }

  ~Vector_base() { deallocate(start, end_of_storage - start); }

  // allocator_type get_allocator() const { return allocator; }

 protected:
  T *start;
  T *finish;
  T *end_of_storage;
  allocator_type allocator;

  T *allocate(size_t n) { return allocator.allocate(n); }
  void deallocate(T *p, size_t n) { allocator.deallocate(p, n); }
  void construct(T *p, const T &val) { allocator.construct(p, val); }
  template <class ForwardIterator>
  void destroy(ForwardIterator first, ForwardIterator last) {
    for (; first != last; ++first) allocator.destroy(&*first);
  }
  void destroy(T *p) { allocator.destroy(p); }
};

template <class T, class Alloc = std::allocator<T> >
class vector : protected Vector_base<T, Alloc> {
 private:
  typedef Vector_base<T, Alloc> _Base;

  using _Base::allocate;
  using _Base::allocator;
  using _Base::construct;
  using _Base::deallocate;
  using _Base::destroy;
  using _Base::end_of_storage;
  using _Base::finish;
  using _Base::start;

 public:
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef wrap_iterator<pointer> iterator;
  typedef wrap_iterator<const_pointer> const_iterator;

  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 public:
  /*
   * constructor
   */
  explicit vector(const allocator_type &a = allocator_type()) : _Base(a) {}
  explicit vector(size_type n) : _Base(n, allocator_type()) { finish = std::uninitialized_fill_n(start, n, T()); }
  vector(size_type n, const T &value, const allocator_type &a = allocator_type()) : _Base(n, a) {
    finish = std::uninitialized_fill_n(start, n, value);
  }
  vector(const vector &x) : _Base(x.size(), x.get_allocator()) {
    finish = std::uninitialized_copy(x.begin(), x.end(), start);
  }
  template <class InputIterator>
  vector(InputIterator first, InputIterator last, const allocator_type &a = allocator_type(),
         typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
      : _Base(std::distance(first, last), a) {
    finish = std::uninitialized_copy(first, last, start);
  }

  /*
   * destructor
   */
  ~vector() { destroy(start, finish); }

  /*
   * assignment operator
   */
  vector &operator=(const vector &x) {
    if (this != &x) {
      const size_type xlen = x.size();
      pointer tmp = allocate_and_copy(xlen, x.begin(), x.end());
      destroy(start, finish);
      deallocate(start, end_of_storage - start);
      start = tmp;
      end_of_storage = start + xlen;
      finish = start + xlen;
    }
    return *this;
  }

  /*
   * assign
   */
  void assign(size_type n, const T &val) {
    if (n > capacity()) {
      vector tmp(n, val);
      tmp.swap(*this);
    } else if (n >= size()) {
      std::fill(begin(), end(), val);
      finish = std::uninitialized_fill_n(finish, n - size(), val);
    } else {
      erase(std::fill_n(begin(), n, val), end());
    }
  }

  template <class InputIterator>
  void assign(InputIterator first, InputIterator last,
              typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
    size_type len = std::distance(first, last);

    if (len > capacity()) {
      vector tmp(first, last);
      tmp.swap(*this);
    } else if (size() >= len) {
      iterator new_finish(std::copy(first, last, start));
      destroy(new_finish, end());
      finish = new_finish.base();
    } else {
      InputIterator mid = first;
      std::advance(mid, size());
      std::copy(first, mid, start);
      finish = std::uninitialized_copy(mid, last, finish);
    }
  }

  /*
   * get_allocator
   */
  allocator_type get_allocator() const { return allocator; }

  /*
   * iterators
   */
  iterator begin() { return iterator(start); }
  const_iterator begin() const { return const_iterator(start); }
  iterator end() { return iterator(finish); }
  const_iterator end() const { return const_iterator(finish); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

  /*
   * capacity
   */
  size_type size() const { return size_type(end() - begin()); }
  size_type max_size() const { return size_type(-1) / sizeof(T); }
  size_type capacity() const { return size_type(const_iterator(end_of_storage) - begin()); }
  bool empty() const { return begin() == end(); }

  void reserve(size_type n) {
    if (capacity() < n) {
      const size_type old_size = size();
      pointer tmp = allocate_and_copy(n, start, finish);
      destroy(start, finish);
      deallocate(start, end_of_storage - start);
      start = tmp;
      finish = tmp + old_size;
      end_of_storage = start + n;
    }
  }

  /*
   * element accessor
   */
  reference operator[](size_type n) { return *(begin() + n); }
  const_reference operator[](size_type n) const { return *(begin() + n); }

  reference at(size_type n) {
    if (n >= this->size()) throw std::out_of_range("vector");
    return (*this)[n];
  }
  const_reference at(size_type n) const {
    if (n >= this->size()) throw std::out_of_range("vector");
    return (*this)[n];
  }

  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(end() - 1); }
  const_reference back() const { return *(end() - 1); }

  /*
   * modifiers
   */
  void push_back(const T &x) {
    if (size() != capacity()) {
      construct(finish, x);
      ++finish;
    } else
      insert(end(), x);
  }

  void pop_back() {
    --finish;
    destroy(finish);
  }

  iterator insert(iterator position, const T &x) {
    size_type n = position - begin();
    if (size() != capacity() && position == end()) {
      construct(finish, x);
      ++finish;
    } else
      insert_aux(position, x);
    return begin() + n;
  }

  void insert(iterator position, size_type n, const T &x) {
    if (n != 0) {
      if (capacity() - size() >= n) {
        const size_type elems_after = end() - position;
        iterator old_finish = end();
        if (elems_after > n) {
          std::uninitialized_copy(finish - n, finish, finish);
          finish += n;
          std::copy_backward(position, old_finish - n, old_finish);
          std::fill(position, position + n, x);
        } else {
          std::uninitialized_fill_n(finish, n - elems_after, x);
          finish += n - elems_after;
          std::uninitialized_copy(position, old_finish, finish);
          finish += elems_after;
          std::fill(position, old_finish, x);
        }
      } else {
        const size_type old_size = size();
        const size_type len = capacity() != 0 ? std::max(2 * capacity(), old_size + n) : 1;
        iterator new_start(allocate(len));
        iterator new_finish(new_start);
        try {
          new_finish = std::uninitialized_copy(begin(), position, new_start);
          new_finish = std::uninitialized_fill_n(new_finish, n, x);
          new_finish = std::uninitialized_copy(position, end(), new_finish);
        } catch (...) {
          destroy(new_start, new_finish);
          deallocate(new_start.base(), len);
          throw;
        }
        destroy(start, finish);
        deallocate(start, end_of_storage - start);
        start = new_start.base();
        finish = new_finish.base();
        end_of_storage = new_start.base() + len;
      }
    }
  }

  template <class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last,
              typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
    if (first != last) {
      size_type n = std::distance(first, last);
      if (size_type(end_of_storage - finish) >= n) {
        const size_type elems_after = end() - position;
        iterator old_finish(finish);
        if (elems_after > n) {
          std::uninitialized_copy(finish - n, finish, finish);
          finish += n;
          std::copy_backward(position, old_finish - n, old_finish);
          std::copy(first, last, position);
        } else {
          InputIterator mid = first;
          std::advance(mid, elems_after);
          std::uninitialized_copy(mid, last, finish);
          finish += n - elems_after;
          std::uninitialized_copy(position, old_finish, finish);
          finish += elems_after;
          std::copy(first, mid, position);
        }
      } else {
        const size_type old_size = size();
        const size_type len = old_size + std::max(old_size, n);
        iterator new_start(allocate(len));
        iterator new_finish(new_start);
        try {
          new_finish = std::uninitialized_copy(begin(), position, new_start);
          new_finish = std::uninitialized_copy(first, last, new_finish);
          new_finish = std::uninitialized_copy(position, end(), new_finish);
        } catch (...) {
          destroy(new_start, new_finish);
          deallocate(new_start.base(), len);
          throw;
        }
        destroy(start, finish);
        deallocate(start, end_of_storage - start);
        start = new_start.base();
        finish = new_finish.base();
        end_of_storage = new_start.base() + len;
      }
    }
  }

  iterator erase(iterator position) {
    if (position + 1 != end()) std::copy(position + 1, end(), position);
    --finish;
    allocator.destroy(finish);
    return position;
  }
  iterator erase(iterator first, iterator last) {
    if (first != last && last != end()) {
      iterator i = std::copy(last, end(), first);
      destroy(i, end());
    }
    finish = finish - (last - first);
    return first;
  }

  void clear() { erase(begin(), end()); }
  void resize(size_type new_size) { resize(new_size, T()); }
  void resize(size_type new_size, const T &x) {
    if (new_size < size()) {
      erase(begin() + new_size, end());
    } else {
      insert(end(), new_size - size(), x);
    }
  }
  void swap(vector &x) {
    std::swap(start, x.start);
    std::swap(finish, x.finish);
    std::swap(end_of_storage, x.end_of_storage);
  }

 protected:
  template <class InputIterator>
  pointer allocate_and_copy(size_type n, InputIterator first, InputIterator last) {
    pointer result = allocate(n);
    try {
      std::uninitialized_copy(first, last, result);
      return result;
    } catch (...) {
      deallocate(result, n);
      throw;
    }
  }

  void insert_aux(iterator position, const T &x) {
    if (finish != end_of_storage) {
      construct(finish, *(finish - 1));
      ++finish;
      std::copy_backward(position, iterator(finish - 2), iterator(finish - 1));
      *position = x;
    } else {
      const size_type old_size = size();
      const size_type len = old_size != 0 ? 2 * old_size : 1;
      iterator new_start(allocate(len));
      iterator new_finish(new_start);
      try {
        new_finish = std::uninitialized_copy(begin(), position, new_start);
        construct(new_finish.base(), x);
        ++new_finish;
        new_finish = std::uninitialized_copy(position, end(), new_finish);
      } catch (...) {
        destroy(new_start, new_finish);
        deallocate(new_start.base(), len);
        throw;
      }
      destroy(begin(), end());
      deallocate(start, end_of_storage - start);
      start = new_start.base();
      finish = new_finish.base();
      end_of_storage = new_start.base() + len;
    }
  };
};

template <class T, class Alloc>
bool operator==(const vector<T, Alloc> &x, const vector<T, Alloc> &y) {
  return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}
template <class T, class Alloc>
bool operator<(const vector<T, Alloc> &x, const vector<T, Alloc> &y) {
  return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
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

}  // namespace ft
#endif
