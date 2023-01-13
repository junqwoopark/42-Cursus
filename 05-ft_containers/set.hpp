#ifndef SET_H
#define SET_H

#include <memory>

#include "tree.hpp"
// #include "type_traits.hpp"
// #include "utility.hpp"

namespace ft {

template <class Value>
struct Identity : public std::unary_function<Value, Value> {
  const Value &operator()(const Value &x) const { return x; }
};

template <class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
class set {
 public:
  typedef Key key_type;
  typedef Key value_type;
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef Alloc allocator_type;

 private:
  typedef Rb_tree<key_type, value_type, Identity<value_type>, key_compare, Alloc> _Rep_type;
  _Rep_type t;

 public:
  typedef typename _Rep_type::const_pointer pointer;
  typedef typename _Rep_type::const_pointer const_pointer;
  typedef typename _Rep_type::const_reference reference;
  typedef typename _Rep_type::const_reference const_reference;

  typedef typename _Rep_type::const_iterator iterator;
  typedef typename _Rep_type::const_iterator const_iterator;
  typedef typename _Rep_type::const_reverse_iterator reverse_iterator;
  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;

  typedef typename _Rep_type::size_type size_type;
  typedef typename _Rep_type::difference_type difference_type;

  // construct/copy/destroy:
  set() : t(Compare(), allocator_type()) {}
  explicit set(const Compare &comp, const allocator_type &a = allocator_type()) : t(comp, a) {}

  template <class InputIterator>
  set(InputIterator first, InputIterator last) : t(Compare(), allocator_type()) {
    t.insert_unique(first, last);
  }
  template <class InputIterator>
  set(InputIterator first, InputIterator last, const Compare &comp, const allocator_type &a = allocator_type())
      : t(comp, a) {
    t.insert_unique(first, last);
  }
  set(const set &x) : t(x.t) {}
  ~set() {}

  set &operator=(const set &x) {
    t = x.t;
    return *this;
  }

  /*
   * iterator
   */
  iterator begin() { return t.begin(); }
  const_iterator begin() const { return t.begin(); }
  iterator end() { return t.end(); }
  const_iterator end() const { return t.end(); }

  reverse_iterator rbegin() { return t.rbegin(); }
  const_reverse_iterator rbegin() const { return t.rbegin(); }
  reverse_iterator rend() { return t.rend(); }
  const_reverse_iterator rend() const { return t.rend(); }

  /*
   * capacity
   */
  bool empty() const { return t.empty(); }
  size_type size() const { return t.size(); }
  size_type max_size() const { return t.max_size(); }

  void swap(set<Key, Compare, Alloc> &x) { t.swap(x.t); }

  /*
   * modifiers
   */
  pair<iterator, bool> insert(const value_type &x) { return t.insert_unique(x); }
  iterator insert(const_iterator position, const value_type &x) {
    typedef typename _Rep_type::iterator _Rep_iterator;
    return t.insert_unique((_Rep_iterator &)position, x);
  }
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    t.insert_unique(first, last);
  }

  void erase(const_iterator position) {
    typedef typename _Rep_type::iterator _Rep_iterator;
    t.erase((_Rep_iterator &)position);
  }
  size_type erase(const key_type &x) { return t.erase(x); }
  void erase(iterator first, iterator last) {
    typedef typename _Rep_type::iterator _Rep_iterator;
    t.erase((_Rep_iterator &)first, (_Rep_iterator &)last);
  }
  void clear() { t.clear(); }

  /*
   * observers
   */
  allocator_type get_allocator() const { return t.get_allocator(); }
  key_compare key_comp() const { return t.key_comp(); }
  value_compare value_comp() const { return t.key_comp(); }

  // set operations
  iterator find(const key_type &x) { return t.find(x); }
  const_iterator find(const key_type &x) const { return t.find(x); }
  size_type count(const key_type &x) const { return t.count(x); }
  iterator lower_bound(const key_type &x) { return t.lower_bound(x); }
  const_iterator lower_bound(const key_type &x) const { return t.lower_bound(x); }
  iterator upper_bound(const key_type &x) { return t.upper_bound(x); }
  const_iterator upper_bound(const key_type &x) const { return t.upper_bound(x); }
  pair<iterator, iterator> equal_range(const key_type &x) { return t.equal_range(x); }
  pair<const_iterator, const_iterator> equal_range(const key_type &x) const { return t.equal_range(x); }

  friend bool operator==(const set &x, const set &y) { return x.t == y.t; }
  friend bool operator<(const set &x, const set &y) { return x.t < y.t; }
};

template <class Key, class Compare, class Alloc>
bool operator!=(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y) {
  return !(x == y);
}

template <class Key, class Compare, class Alloc>
bool operator>(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y) {
  return y < x;
}

template <class Key, class Compare, class Alloc>
bool operator<=(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y) {
  return !(y < x);
}

template <class Key, class Compare, class Alloc>
bool operator>=(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y) {
  return !(x < y);
}

template <class Key, class Compare, class Alloc>
void swap(set<Key, Compare, Alloc> &x, set<Key, Compare, Alloc> &y) {
  x.swap(y);
}

}  // namespace ft

#endif
