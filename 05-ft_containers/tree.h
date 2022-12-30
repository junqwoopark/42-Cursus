#ifndef TREE_H
#define TREE_H

#include <cstddef>
#include <iostream>
#include <memory>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace ft {

typedef bool Rb_tree_color_type;
const Rb_tree_color_type Rb_tree_red = false;
const Rb_tree_color_type Rb_tree_black = true;

struct Rb_tree_node_base {
  typedef Rb_tree_color_type color_type;
  typedef Rb_tree_node_base *base_ptr;

  color_type color;
  base_ptr parent;
  base_ptr left;
  base_ptr right;

  static base_ptr minimum(base_ptr x) {
    while (x->left != 0)
      x = x->left;
    return x;
  }

  static base_ptr maximum(base_ptr x) {
    while (x->right != 0)
      x = x->right;
    return x;
  }
};

template <class Value> struct Rb_tree_node : public Rb_tree_node_base {
  typedef Rb_tree_node<Value> *link_type;
  Value value_field;
};

struct Rb_tree_base_iterator {
  typedef Rb_tree_node_base::base_ptr base_ptr;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;

  base_ptr node;

  void increment() {
    if (node->right != 0) {
      node = node->right;
      while (node->left != 0)
        node = node->left;
    } else {
      base_ptr y = node->parent;
      while (node == y->right) {
        node = y;
        y = y->parent;
      }
      if (node->right != y)
        node = y;
    }
  }

  void decrement() {
    if (node->color == Rb_tree_red && node->parent->parent == node)
      node = node->right;
    else if (node->left != 0) {
      base_ptr y = node->left;
      while (y->right != 0)
        y = y->right;
      node = y;
    } else {
      base_ptr y = node->parent;
      while (node == y->left) {
        node = y;
        y = y->parent;
      }
      node = y;
    }
  }
};

template <class Value, class Ref, class Ptr>
struct Rb_tree_iterator : public Rb_tree_base_iterator {
  typedef Value value_type;
  typedef Ref reference;
  typedef Ptr pointer;
  typedef Rb_tree_iterator<Value, Value &, Value *> iterator;
  typedef Rb_tree_iterator<Value, const Value &, const Value *> const_iterator;
  typedef Rb_tree_iterator<Value, Ref, Ptr> self;
  typedef Rb_tree_node<Value> *link_type;

  Rb_tree_iterator() {}
  Rb_tree_iterator(link_type x) { node = x; }
  Rb_tree_iterator(const iterator &it) { node = it.node; }

  reference operator*() const { return link_type(node)->value_field; }

  pointer operator->() const { return &(operator*()); }

  self &operator++() {
    increment();
    return *this;
  }

  self operator++(int) {
    self tmp = *this;
    increment();
    return tmp;
  }

  self &operator--() {
    decrement();
    return *this;
  }

  self operator--(int) {
    self tmp = *this;
    decrement();
    return tmp;
  }
};

bool operator==(const Rb_tree_base_iterator &x,
                const Rb_tree_base_iterator &y) {
  return x.node == y.node;
}

bool operator!=(const Rb_tree_base_iterator &x,
                const Rb_tree_base_iterator &y) {
  return x.node != y.node;
}

void Rb_tree_rotate_left(Rb_tree_node_base *x, Rb_tree_node_base *&root) {
  Rb_tree_node_base *y = x->right;
  x->right = y->left;
  if (y->left != 0)
    y->left->parent = x;
  y->parent = x->parent;

  if (x == root)
    root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

void Rb_tree_rotate_right(Rb_tree_node_base *x, Rb_tree_node_base *&root) {
  Rb_tree_node_base *y = x->left;
  x->left = y->right;
  if (y->right != 0)
    y->right->parent = x;
  y->parent = x->parent;

  if (x == root)
    root = y;
  else if (x == x->parent->right)
    x->parent->right = y;
  else
    x->parent->left = y;
  y->right = x;
  x->parent = y;
}

void Rb_tree_rebalance(Rb_tree_node_base *x, Rb_tree_node_base *&root) {
  x->color = Rb_tree_red;
  while (x != root && x->parent->color == Rb_tree_red) {
    if (x->parent == x->parent->parent->left) {
      Rb_tree_node_base *y = x->parent->parent->right;
      if (y && y->color == Rb_tree_red) { // case 1
        x->parent->color = Rb_tree_black;
        y->color = Rb_tree_black;
        x->parent->parent->color = Rb_tree_red;
        x = x->parent->parent;
      } else { // case 2
        if (x == x->parent->right) {
          x = x->parent;
          Rb_tree_rotate_left(x, root);
        }
        x->parent->color = Rb_tree_black;
        x->parent->parent->color = Rb_tree_red;
        Rb_tree_rotate_right(x->parent->parent, root);
      }
    } else {
      Rb_tree_node_base *y = x->parent->parent->left;
      if (y && y->color == Rb_tree_red) { // case 3
        x->parent->color = Rb_tree_black;
        y->color = Rb_tree_black;
        x->parent->parent->color = Rb_tree_red;
        x = x->parent->parent;
      } else { // case 4
        if (x == x->parent->left) {
          x = x->parent;
          Rb_tree_rotate_right(x, root);
        }
        x->parent->color = Rb_tree_black;
        x->parent->parent->color = Rb_tree_red;
        Rb_tree_rotate_left(x->parent->parent, root);
      }
    }
  }
  root->color = Rb_tree_black;
}

Rb_tree_node_base *Rb_tree_rebalance_for_erase(Rb_tree_node_base *z,
                                               Rb_tree_node_base *&root,
                                               Rb_tree_node_base *&leftmost,
                                               Rb_tree_node_base *&rightmost) {
  Rb_tree_node_base *y = z;
  Rb_tree_node_base *x = 0;
  Rb_tree_node_base *x_parent = 0;
  if (y->left == 0)
    x = y->right;
  else if (y->right == 0)
    x = y->left;
  else {
    y = y->right;
    while (y->left != 0)
      y = y->left;
    x = y->right;
  }
  if (y != z) {
    z->left->parent = y;
    y->left = z->left;
    if (y != z->right) {
      x_parent = y->parent;
      if (x)
        x->parent = y->parent;
      y->parent->left = x;
      y->right = z->right;
      z->right->parent = y;
    } else
      x_parent = y;
    if (root == z)
      root = y;
    else if (z->parent->left == z)
      z->parent->left = y;
    else
      z->parent->right = y;
    y->parent = z->parent;
    std::swap(y->color, z->color);
    y = z;
  } else {
    x_parent = y->parent;
    if (x)
      x->parent = y->parent;
    if (root == z)
      root = x;
    else if (z->parent->left == z)
      z->parent->left = x;
    else
      z->parent->right = x;
    if (leftmost == z)
      if (z->right == 0)
        leftmost = z->parent;
      else
        leftmost = Rb_tree_node_base::minimum(x);
    if (rightmost == z)
      if (z->left == 0)
        rightmost = z->parent;
      else
        rightmost = Rb_tree_node_base::maximum(x);
  }
  if (y->color != Rb_tree_red) {
    while (x != root && (x == 0 || x->color == Rb_tree_black))
      if (x == x_parent->left) {
        Rb_tree_node_base *w = x_parent->right;
        if (w->color == Rb_tree_red) {
          w->color = Rb_tree_black;
          x_parent->color = Rb_tree_red;
          Rb_tree_rotate_left(x_parent, root);
          w = x_parent->right;
        }
        if ((w->left == 0 || w->left->color == Rb_tree_black) &&
            (w->right == 0 || w->right->color == Rb_tree_black)) {
          w->color = Rb_tree_red;
          x = x_parent;
          x_parent = x_parent->parent;
        } else {
          if (w->right == 0 || w->right->color == Rb_tree_black) {
            if (w->left)
              w->left->color = Rb_tree_black;
            w->color = Rb_tree_red;
            Rb_tree_rotate_right(w, root);
            w = x_parent->right;
          }
          w->color = x_parent->color;
          x_parent->color = Rb_tree_black;
          if (w->right)
            w->right->color = Rb_tree_black;
          Rb_tree_rotate_left(x_parent, root);
          break;
        }
      } else {
        Rb_tree_node_base *w = x_parent->left;
        if (w->color == Rb_tree_red) {
          w->color = Rb_tree_black;
          x_parent->color = Rb_tree_red;
          Rb_tree_rotate_right(x_parent, root);
          w = x_parent->left;
        }
        if ((w->right == 0 || w->right->color == Rb_tree_black) &&
            (w->left == 0 || w->left->color == Rb_tree_black)) {
          w->color = Rb_tree_red;
          x = x_parent;
          x_parent = x_parent->parent;
        } else {
          if (w->left == 0 || w->left->color == Rb_tree_black) {
            if (w->right)
              w->right->color = Rb_tree_black;
            w->color = Rb_tree_red;
            Rb_tree_rotate_left(w, root);
            w = x_parent->left;
          }
          w->color = x_parent->color;
          x_parent->color = Rb_tree_black;
          if (w->left)
            w->left->color = Rb_tree_black;
          Rb_tree_rotate_right(x_parent, root);
          break;
        }
      }
    if (x)
      x->color = Rb_tree_black;
  }
  return y;
}

template <class Key, class Value, class KeyOfValue, class Compare,
          class Alloc = std::allocator<Value> >
class Rb_tree {
protected:
  typedef Rb_tree_node_base *base_ptr;
  typedef Rb_tree_node<Value> Rb_tree_node;
  typedef Rb_tree_color_type color_type;

public:
  typedef Key key_type;
  typedef Value value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef Rb_tree_node *link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef Alloc allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

protected:
  link_type get_node() { return link_type(allocator_type::allocate(1)); }
  link_type header;
  void put_node(link_type p) { allocator_type::deallocate(p, 1); }

  link_type create_node(const value_type &x) {
    link_type tmp = get_node();
    try {
      construct(&tmp->value_field, x);
    } catch (...) {
      put_node(tmp);
      throw;
    }
    return tmp;
  }

  link_type clone_node(link_type x) {
    link_type tmp = create_node(x->value_field);
    tmp->color = x->color;
    tmp->left = 0;
    tmp->right = 0;
    return tmp;
  }

  void destroy_node(link_type p) {
    destroy(&p->value_field);
    put_node(p);
  }

protected:
  size_type node_count;
  Compare key_compare;

  link_type &root() const { return (link_type &)(header->parent); }
  link_type &leftmost() const { return (link_type &)(header->left); }
  link_type &rightmost() const { return (link_type &)(header->right); }

  static link_type &left(link_type x) { return (link_type &)(x->left); }
  static link_type &right(link_type x) { return (link_type &)(x->right); }
  static link_type &parent(link_type x) { return (link_type &)(x->parent); }
  static reference value(link_type x) { return x->value_field; }
  static const Key &key(link_type x) { return KeyOfValue()(value(x)); }
  static color_type &color(link_type x) { return (color_type &)(x->color); }

  static link_type &left(base_ptr x) { return (link_type &)(x->left); }
  static link_type &right(base_ptr x) { return (link_type &)(x->right); }
  static link_type &parent(base_ptr x) { return (link_type &)(x->parent); }
  static reference value(base_ptr x) { return ((link_type)x)->value_field; }
  static const Key &key(base_ptr x) {
    return KeyOfValue()(value(link_type(x)));
  }
  static color_type &color(base_ptr x) {
    return (color_type &)(link_type(x)->color);
  }

  static link_type minimum(link_type x) {
    return (link_type)Rb_tree_node_base::minimum(x);
  }
  static link_type maximum(link_type x) {
    return (link_type)Rb_tree_node_base::maximum(x);
  }

public:
  typedef Rb_tree_iterator<value_type, reference, pointer> iterator;
  typedef Rb_tree_iterator<value_type, const_reference, const_pointer>
      const_iterator;

  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

private:
  iterator insert(base_ptr x_, base_ptr y_, const value_type &v);
  link_type copy(link_type x, link_type p);
  void erase(link_type x);
  void empty_initialize() {
    header = get_node();
    color(header) = Rb_tree_red;
    root() = 0;
    leftmost() = header;
    rightmost() = header;
  }

public:
  Rb_tree() : node_count(0), key_compare(Compare()) { empty_initialize(); }

  Rb_tree(const Compare &comp) : node_count(0), key_compare(comp) {
    empty_initialize();
  }

  Rb_tree(const Compare &comp, const allocator_type &a)
      : node_count(0), key_compare(comp) {
    empty_initialize();
  }

  Rb_tree(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x)
      : node_count(0), key_compare(x.key_compare) {
    if (x.root() == 0) {
      empty_initialize();
    } else {
      root() = copy(x.root(), header);
      leftmost() = minimum(root());
      rightmost() = maximum(root());
    }
    node_count = x.node_count;
  }

  ~Rb_tree() {
    clear();
    put_node(header);
  }

  Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &
  operator=(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x);

public:
  // 접근자
  Compare key_comp() const { return key_compare; }
  iterator begin() { return leftmost(); }
  const_iterator begin() const { return leftmost(); }
  iterator end() { return header; }
  const_iterator end() const { return header; }
  reverse_iterator Rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator Rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
  bool empty() const { return node_count == 0; }
  size_type size() const { return node_count; }
  size_type max_size() const { return size_type(-1); }

  void swap(Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &t) {
    std::swap(header, t.header);
    std::swap(node_count, t.node_count);
    std::swap(key_compare, t.key_compare);
  }

public:
  // 삽입
  ft::pair<iterator, bool> insert_unique(const value_type &x);
  iterator insert_equal(const value_type &x);

  iterator insert_unique(iterator position, const value_type &x);
  iterator insert_equal(iterator position, const value_type &x);

  // #ifdef __STL_MEMBER_TEMPLATES
  // template <class InputIterator>
  // void insert_unique(InputIterator first, InputIterator last);
  // template <class InputIterator>
  // void insert_equal(InputIterator first, InputIterator last);
  // #endif /* __STL_MEMBER_TEMPLATES */

  // 삭제
  void erase(iterator position);
  size_type erase(const key_type &x);
  void erase(iterator first, iterator last);
  void erase(const key_type *first, const key_type *last);
  void clear() {
    if (node_count != 0) {
      erase(begin(), end());
      leftmost() = header;
      root() = 0;
      rightmost() = header;
      node_count = 0;
    }
  }

public:
  iterator find(const key_type &x);
  const_iterator find(const key_type &x) const;
  size_type count(const key_type &x) const;
  iterator lower_bound(const key_type &x);
  const_iterator lower_bound(const key_type &x) const;
  iterator upper_bound(const key_type &x);
  const_iterator upper_bound(const key_type &x) const;
  ft::pair<iterator, iterator> equal_range(const key_type &x);
  ft::pair<const_iterator, const_iterator> equal_range(const key_type &x) const;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
inline bool
operator==(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
           const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
inline bool
operator<(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
          const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
inline bool
operator!=(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
           const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return !(x == y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
inline bool
operator>(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
          const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return y < x;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
inline bool
operator<=(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
           const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return !(y < x);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
inline bool
operator>=(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
           const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return !(x < y);
}

// #ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
// template <class Key, class Value, class KeyOfValue, class Compare, class
// Alloc> inline void swap(Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
//                  Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
//   x.swap(y);
// }
// #endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::operator=(
    const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x) {
  if (this != &x) {
    // Note that Key may be a constant type.
    clear();
    node_count = 0;
    key_compare = x.key_compare;
    if (x.root() == 0) {
      root() = 0;
      leftmost() = header;
      rightmost() = header;
    } else {
      root() = copy(x.root(), header);
      leftmost() = minimum(root());
      rightmost() = maximum(root());
      node_count = x.node_count;
    }
  }
  return *this;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert(base_ptr x_,
                                                        base_ptr y_,
                                                        const Value &v) {
  link_type x = (link_type)x_;
  link_type y = (link_type)y_;
  link_type z;

  if (y == header || x != 0 || key_compare(KeyOfValue()(v), key(y))) {
    z = create_node(v);
    left(y) = z;
    if (y == header) {
      root() = z;
      rightmost() = z;
    } else if (y == leftmost())
      leftmost() = z;
  } else {
    z = create_node(v);
    right(y) = z;
    if (y == rightmost())
      rightmost() = z;
  }
  parent(z) = y;
  left(z) = 0;
  right(z) = 0;
  Rb_tree_rebalance(z, header->parent);
  ++node_count;
  return iterator(z);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const Value &v) {
  link_type y = header;
  link_type x = root();
  bool comp = true;
  while (x != 0) {
    y = x;
    comp = key_compare(KeyOfValue()(v), key(x));
    x = comp ? left(x) : right(x);
  }
  return insert(x, y, v);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
ft::pair<typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator,
         bool>
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(
    const value_type &v) {
  link_type y = header;
  link_type x = root();
  bool comp = true;
  while (x != 0) {
    y = x;
    comp = key_compare(KeyOfValue()(v), key(x));
    x = comp ? left(x) : right(x);
  }
  iterator j = iterator(y);
  if (comp) {
    if (j == begin())
      return ft::pair<iterator, bool>(insert(x, y, v), true);
    else
      --j;
  }
  if (key_compare(key(j.node), KeyOfValue()(v)))
    return ft::pair<iterator, bool>(insert(x, y, v), true);
  return ft::pair<iterator, bool>(j, false);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(
    iterator position, const value_type &v) {
  if (position.node == header->left) {
    if (size() > 0 && key_compare(KeyOfValue()(v), key(position.node)))
      return insert(position.node, position.node, v);
    else
      return insert_unique(v).first;
  } else if (position.node == header) {
    if (key_compare(key(rightmost()), KeyOfValue()(v)))
      return insert(0, rightmost(), v);
    else
      return insert_unique(v).first;
  } else {
    iterator before = position;
    --before;
    if (key_compare(key(before.node), KeyOfValue()(v)) &&
        key_compare(KeyOfValue()(v), key(position.node))) {
      if (right(before.node) == 0)
        return insert(0, before.node, v);
      else
        return insert(position.node, position.node, v);
    } else
      return insert_unique(v).first;
  }
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(
    iterator position, const value_type &v) {
  if (position.node == header->left) {
    if (size() > 0 && key_compare(KeyOfValue()(v), key(position.node)))
      return insert(position.node, position.node, v);
    else
      return insert_equal(v);
  } else if (position.node == header) {
    if (!key_compare(KeyOfValue()(v), key(rightmost())))
      return insert(0, rightmost(), v);
    else
      return insert_equal(v);
  } else {
    iterator before = position;
    --before;
    if (!key_compare(KeyOfValue()(v), key(before.node)) &&
        !key_compare(key(position.node), KeyOfValue()(v))) {
      if (right(before.node) == 0)
        return insert(0, before.node, v);
      else
        return insert(position.node, position.node, v);
    } else
      return insert_equal(v);
  }
}

// #ifdef __STL_MEMBER_TEMPLATES
// template <class Key, class Value, class KeyOfValue, class Compare, class
// Alloc> template <class InputIterator> void Rb_tree<Key, Value, KeyOfValue,
// Compare, Alloc>::insert_equal(
//     InputIterator first, InputIterator last) {
//   for (; first != last; ++first) insert_equal(*first);
// }
//
// template <class Key, class Value, class KeyOfValue, class Compare, class
// Alloc> template <class InputIterator> void Rb_tree<Key, Value, KeyOfValue,
// Compare, Alloc>::insert_unique(
//     InputIterator first, InputIterator last) {
//   for (; first != last; ++first) insert_unique(*first);
// }

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator position) {
  link_type y = (link_type)Rb_tree_rebalance_for_erase(
      (base_ptr)position.node, header->parent, header->left, header->right);
  destroy_node(y);
  --node_count;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::size_type
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(const key_type &x) {
  ft::pair<iterator, iterator> p = equal_range(x);
  size_type n = ft::distance(p.first, p.second);
  erase(p.first, p.second);
  return n;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::link_type
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::copy(link_type x,
                                                      link_type p) {
  // structural copy.  x and p must be non-null.
  link_type top = clone_node(x);
  top->parent = p;

  try {
    if (x->right)
      top->right = copy(right(x), top);
    p = top;
    x = left(x);

    while (x != 0) {
      link_type y = clone_node(x);
      p->left = y;
      y->parent = p;
      if (x->right)
        y->right = copy(right(x), y);
      p = y;
      x = left(x);
    }
  } catch (...) {
    erase(top);
    throw;
  }

  return top;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(link_type x) {
  // erase without rebalancing.
  while (x != 0) {
    erase(right(x));
    link_type y = left(x);
    destroy_node(x);
    x = y;
  }
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator first,
                                                            iterator last) {
  if (first == begin() && last == end())
    clear();
  else
    while (first != last)
      erase(first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(
    const key_type *first, const key_type *last) {
  while (first != last)
    erase(*first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find(const key_type &k) {
  link_type y = header; // Last node which is not less than k.
  link_type x = root(); // Current node.

  while (x != 0)
    if (!key_compare(key(x), k))
      y = x, x = left(x);
    else
      x = right(x);

  iterator j = iterator(y);
  return (j == end() || key_compare(k, key(j.node))) ? end() : j;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find(const key_type &k) const {
  link_type y = header; // Last node which is not less than k.
  link_type x = root(); // Current node.

  while (x != 0)
    if (!key_compare(key(x), k))
      y = x, x = left(x);
    else
      x = right(x);

  const_iterator j = const_iterator(y);
  return (j == end() || key_compare(k, key(j.node))) ? end() : j;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::size_type
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::count(
    const key_type &k) const {
  ft::pair<const_iterator, const_iterator> p = equal_range(k);
  size_type n = 0;
  distance(p.first, p.second, n);
  return n;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(
    const key_type &k) {
  link_type y = header; // Last node which is not less than k.
  link_type x = root(); // Current node.

  while (x != 0)
    if (!key_compare(key(x), k))
      y = x, x = left(x);
    else
      x = right(x);

  return iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(
    const key_type &k) const {
  link_type y = header; // Last node which is not less than k.
  link_type x = root(); // Current node.

  while (x != 0)
    if (!key_compare(key(x), k))
      y = x, x = left(x);
    else
      x = right(x);

  return const_iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::upper_bound(
    const key_type &k) {
  link_type y = header; // Last node which is greater than k.
  link_type x = root(); // Current node.

  while (x != 0)
    if (key_compare(k, key(x)))
      y = x, x = left(x);
    else
      x = right(x);

  return iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::upper_bound(
    const key_type &k) const {
  link_type y = header; // Last node which is greater than k.
  link_type x = root(); // Current node.

  while (x != 0)
    if (key_compare(k, key(x)))
      y = x, x = left(x);
    else
      x = right(x);

  return const_iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
ft::pair<typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator,
         typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator>
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::equal_range(
    const key_type &k) {
  return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
ft::pair<
    typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator,
    typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator>
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::equal_range(
    const key_type &k) const {
  return ft::pair<const_iterator, const_iterator>(lower_bound(k),
                                                  upper_bound(k));
}

} // namespace ft
#endif