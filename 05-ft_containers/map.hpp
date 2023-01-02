#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"
#include "utility.hpp"
#include <__functional_base>
#include <algorithm>
#include <memory>

namespace ft {

template <class Pair>
struct Select1st : public std::unary_function<Pair, typename Pair::first_type> {
  typename Pair::first_type &operator()(Pair &x) const { return x.first; }
  const typename Pair::first_type &operator()(const Pair &x) const {
    return x.first;
  }
};

template <class Key, class Tp, class Compare = std::less<Key>,
          class Alloc = std::allocator<pair<const Key, Tp> > >
class map {
public:
  typedef Key key_type;
  typedef Tp data_type;
  typedef Tp mapped_type;
  typedef pair<const Key, Tp> value_type;
  typedef Compare key_compare;

  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
    friend class map<Key, Tp, Compare, Alloc>;

  protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {}

  public:
    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
  };

private:
  typedef Rb_tree<key_type, value_type, Select1st<value_type>, Compare, Alloc>
      Rep_type;
  Rep_type _M_t;

public:
  typedef typename Rep_type::pointer pointer;
  typedef typename Rep_type::const_pointer const_pointer;
  typedef typename Rep_type::reference reference;
  typedef typename Rep_type::const_reference const_reference;
  typedef typename Rep_type::iterator iterator;
  typedef typename Rep_type::const_iterator const_iterator;
  typedef typename Rep_type::reverse_iterator reverse_iterator;
  typedef typename Rep_type::const_reverse_iterator const_reverse_iterator;
  typedef typename Rep_type::size_type size_type;
  typedef typename Rep_type::difference_type difference_type;
  typedef typename Rep_type::allocator_type allocator_type;

  map() : _M_t(Compare(), allocator_type()) {}
  explicit map(const Compare &comp, const allocator_type &a = allocator_type())
      : _M_t(comp, a) {}

  template <class InputIterator>
  map(InputIterator first, InputIterator last)
      : _M_t(Compare(), allocator_type()) {
    _M_t.insert_unique(first, last);
  }

  template <class InputIterator>
  map(InputIterator first, InputIterator last, const Compare &comp,
      const allocator_type &a = allocator_type())
      : _M_t(comp, a) {
    _M_t.insert_unique(first, last);
  }

  map(const map<Key, Tp, Compare, Alloc> &x) : _M_t(x._M_t) {}

  map<Key, Tp, Compare, Alloc> &
  operator=(const map<Key, Tp, Compare, Alloc> &x) {
    _M_t = x._M_t;
    return (*this);
  }

  key_compare key_comp() const { return _M_t.key_comp(); }
  value_compare value_comp() const { return value_compare(_M_t.key_compare()); }
  allocator_type get_allocator() const { return _M_t.get_allocator(); }

  iterator begin() { return _M_t.begin(); }
  const_iterator begin() const { return _M_t.begin(); }
  iterator end() { return _M_t.end(); }
  const_iterator end() const { return _M_t.end(); }
  reverse_iterator rbegin() { return _M_t.rbegin(); }
  const_reverse_iterator rbegin() const { return _M_t.rbegin(); }
  reverse_iterator rend() { return _M_t.rend(); }
  const_reverse_iterator rend() const { return _M_t.rend(); }
  bool empty() const { return _M_t.empty(); }
  size_type size() const { return _M_t.size(); }
  size_type max_size() const { return _M_t.max_size(); }
  Tp &operator[](const key_type k) {
    iterator i = lower_bound(k);
    if (i == end() || key_comp()(k, (*i).first))
      i = insert(i, value_type(k, Tp()));
    return (*i).second;
  }
  Tp &at(const key_type k) {
    iterator i = lower_bound(k);
    if (i == end() || key_comp()(k, (*i).first))
      i = insert(i, value_type(k, Tp()));
    return (*i).second;
  }
  const Tp &at(const key_type &k) const {
    iterator i = lower_bound(k);
    if (i == end() || key_comp()(k, (*i).first))
      i = insert(i, value_type(k, Tp()));
    return (*i).second;
  }
  void swap(map<Key, Tp, Compare, Alloc> &x) { _M_t.swap(x._M_t); }

  pair<iterator, bool> insert(value_type &x) { return _M_t.insert_unique(x); }
  pair<iterator, bool> insert(const value_type &x) {
    return _M_t.insert_unique(x);
  }

  iterator insert(iterator position, const value_type &x) {
    return _M_t.insert_unique(position, x);
  }

  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    _M_t.insert_unique(first, last);
  }

  void erase(iterator position) { return _M_t.erase(position); }
  size_type erase(const key_type &x) { return _M_t.erase(x); }
  void erase(iterator first, iterator last) { _M_t.erase(first, last); }
  void clear() { _M_t.clear(); }

  iterator find(const key_type &x) { return _M_t.find(x); }
  const_iterator find(const key_type &x) const { return _M_t.find(x); }
  size_type count(const key_type &x) const {
    return _M_t.find(x) == _M_t.end() ? 0 : 1;
  }
  iterator lower_bound(const key_type &x) { return _M_t.lower_bound(x); }
  const_iterator lower_bound(const key_type &x) const {
    return _M_t.lower_bound(x);
  }
  iterator upper_bound(const key_type &x) { return _M_t.upper_bound(x); }
  const_iterator upper_bound(const key_type &x) const {
    return _M_t.upper_bound(x);
  }

  pair<iterator, iterator> equal_range(const key_type &x) {
    return _M_t.equal_range(x);
  }
  pair<const_iterator, const_iterator> equal_range(const key_type &x) const {
    return _M_t.equal_range(x);
  }

  template <class _Key, class _Tp, class _Compare, class _Alloc>
  friend bool operator==(const map<_Key, _Tp, _Compare, _Alloc> &x,
                         const map<_Key, _Tp, _Compare, _Alloc> &y) {
    return x._M_t == y._M_t;
  }

  template <class _Key, class _Tp, class _Compare, class _Alloc>
  friend bool operator<(const map<_Key, _Tp, _Compare, _Alloc> &x,
                        const map<_Key, _Tp, _Compare, _Alloc> &y) {
    return x._M_t < y._M_t;
  }
};

template <class _Key, class _Tp, class _Compare, class _Alloc>
bool operator!=(const map<_Key, _Tp, _Compare, _Alloc> &x,
                const map<_Key, _Tp, _Compare, _Alloc> &y) {
  return !(x == y);
}

template <class _Key, class _Tp, class _Compare, class _Alloc>
bool operator>(const map<_Key, _Tp, _Compare, _Alloc> &x,
               const map<_Key, _Tp, _Compare, _Alloc> &y) {
  return y < x;
}

template <class _Key, class _Tp, class _Compare, class _Alloc>
bool operator<=(const map<_Key, _Tp, _Compare, _Alloc> &x,
                const map<_Key, _Tp, _Compare, _Alloc> &y) {
  return !(y < x);
}

template <class _Key, class _Tp, class _Compare, class _Alloc>
bool operator>=(const map<_Key, _Tp, _Compare, _Alloc> &x,
                const map<_Key, _Tp, _Compare, _Alloc> &y) {
  return !(x < y);
}

template <class _Key, class _Tp, class _Compare, class _Alloc>
void swap(map<_Key, _Tp, _Compare, _Alloc> &x,
          map<_Key, _Tp, _Compare, _Alloc> &y) {
  x.swap(y);
}

} // namespace ft

#endif
