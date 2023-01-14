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
  typedef Rb_tree<key_type, value_type, Identity<value_type>, key_compare, Alloc> _Tree_type;
  _Tree_type _tree;

 public:
  typedef typename _Tree_type::const_pointer pointer;
  typedef typename _Tree_type::const_pointer const_pointer;
  typedef typename _Tree_type::const_reference reference;
  typedef typename _Tree_type::const_reference const_reference;

  typedef typename _Tree_type::const_iterator iterator;
  typedef typename _Tree_type::const_iterator const_iterator;
  typedef typename _Tree_type::const_reverse_iterator reverse_iterator;
  typedef typename _Tree_type::const_reverse_iterator const_reverse_iterator;

  typedef typename _Tree_type::size_type size_type;
  typedef typename _Tree_type::difference_type difference_type;

  /*
   * constructor
   */
  set() : _tree(Compare(), allocator_type()) {}
  explicit set(const Compare &comp, const allocator_type &a = allocator_type()) : _tree(comp, a) {}

  template <class InputIterator>
  set(InputIterator first, InputIterator last) : _tree(Compare(), allocator_type()) {
    _tree.insert_unique(first, last);
  }
  template <class InputIterator>
  set(InputIterator first, InputIterator last, const Compare &comp, const allocator_type &a = allocator_type())
      : _tree(comp, a) {
    _tree.insert_unique(first, last);
  }
  set(const set &x) : _tree(x._tree) {}

  /*
   * assignment operator
   */
  set &operator=(const set &x) {
    _tree = x._tree;
    return *this;
  }

  /*
   * destructor
   */
  ~set() {}

  /*
   * iterators
   */
  iterator begin() { return _tree.begin(); }
  const_iterator begin() const { return _tree.begin(); }
  iterator end() { return _tree.end(); }
  const_iterator end() const { return _tree.end(); }

  reverse_iterator rbegin() { return _tree.rbegin(); }
  const_reverse_iterator rbegin() const { return _tree.rbegin(); }
  reverse_iterator rend() { return _tree.rend(); }
  const_reverse_iterator rend() const { return _tree.rend(); }

  /*
   * capacity
   */
  bool empty() const { return _tree.empty(); }
  size_type size() const { return _tree.size(); }
  size_type max_size() const { return _tree.max_size(); }

  void swap(set<Key, Compare, Alloc> &x) { _tree.swap(x._tree); }

  /*
   * modifiers
   */
  pair<iterator, bool> insert(const value_type &x) { return _tree.insert_unique(x); }
  iterator insert(const_iterator position, const value_type &x) {
    typedef typename _Tree_type::iterator _Rep_iterator;
    return _tree.insert_unique((_Rep_iterator &)position, x);
  }
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    _tree.insert_unique(first, last);
  }

  void erase(const_iterator position) {
    typedef typename _Tree_type::iterator _Rep_iterator;
    _tree.erase((_Rep_iterator &)position);
  }
  size_type erase(const key_type &x) { return _tree.erase(x); }
  void erase(iterator first, iterator last) {
    typedef typename _Tree_type::iterator _Rep_iterator;
    _tree.erase((_Rep_iterator &)first, (_Rep_iterator &)last);
  }
  void clear() { _tree.clear(); }

  /*
   * observers
   */
  allocator_type get_allocator() const { return _tree.get_allocator(); }
  key_compare key_comp() const { return _tree.key_comp(); }
  value_compare value_comp() const { return _tree.key_comp(); }

  /*
   * lookup
   */
  iterator find(const key_type &x) { return _tree.find(x); }
  const_iterator find(const key_type &x) const { return _tree.find(x); }
  size_type count(const key_type &x) const { return _tree.count(x); }
  iterator lower_bound(const key_type &x) { return _tree.lower_bound(x); }
  const_iterator lower_bound(const key_type &x) const { return _tree.lower_bound(x); }
  iterator upper_bound(const key_type &x) { return _tree.upper_bound(x); }
  const_iterator upper_bound(const key_type &x) const { return _tree.upper_bound(x); }
  pair<iterator, iterator> equal_range(const key_type &x) { return _tree.equal_range(x); }
  pair<const_iterator, const_iterator> equal_range(const key_type &x) const { return _tree.equal_range(x); }

  friend bool operator==(const set &x, const set &y) { return x._tree == y._tree; }
  friend bool operator<(const set &x, const set &y) { return x._tree < y._tree; }
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
