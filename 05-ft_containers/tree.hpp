#ifndef TREE_H
#define TREE_H

#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace ft {

typedef bool Rb_tree_color_type;
const Rb_tree_color_type Rb_tree_red = false;
const Rb_tree_color_type Rb_tree_black = true;

template <class Value>
struct Rb_tree_node {
  typedef Rb_tree_color_type color_type;
  typedef Rb_tree_node<Value> *link_type;

  Value value_field;
  color_type color;
  link_type parent;
  link_type left;
  link_type right;

  static link_type minimum(link_type x) {
    while (x->left != 0) x = x->left;
    return x;
  }

  static link_type maximum(link_type x) {
    while (x->right != 0) x = x->right;
    return x;
  }
};

template <class Value, class Ref, class Ptr>
struct Rb_tree_iterator {
  typedef Value value_type;
  typedef Ref reference;
  typedef Ptr pointer;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;

  typedef typename Rb_tree_node<Value>::link_type link_type;

  link_type node;

  void increment() {
    if (node->right != 0) {
      node = node->right;
      while (node->left != 0) node = node->left;
    } else {
      link_type y = node->parent;
      while (node == y->right) {
        node = y;
        y = y->parent;
      }
      if (node->right != y) node = y;
    }
  }

  void decrement() {
    if (node->color == Rb_tree_red && node->parent->parent == node)
      node = node->right;
    else if (node->left != 0) {
      link_type y = node->left;
      while (y->right != 0) y = y->right;
      node = y;
    } else {
      link_type y = node->parent;
      while (node == y->left) {
        node = y;
        y = y->parent;
      }
      node = y;
    }
  }

  Rb_tree_iterator() {}
  Rb_tree_iterator(link_type x) { node = x; }
  Rb_tree_iterator(const Rb_tree_iterator<Value, Value &, Value *> &it) { node = it.node; }

  reference operator*() const { return link_type(node)->value_field; }
  pointer operator->() const { return &operator*(); }

  Rb_tree_iterator &operator++() {
    increment();
    return *this;
  }

  Rb_tree_iterator operator++(int) {
    Rb_tree_iterator tmp = *this;
    increment();
    return tmp;
  }

  Rb_tree_iterator &operator--() {
    decrement();
    return *this;
  }

  Rb_tree_iterator operator--(int) {
    Rb_tree_iterator tmp = *this;
    decrement();
    return tmp;
  }
};

template <class Value, class Ref1, class Ptr1, class Ref2, class Ptr2>
bool operator==(const Rb_tree_iterator<Value, Ref1, Ptr1> &x, const Rb_tree_iterator<Value, Ref2, Ptr2> &y) {
  return x.node == y.node;
}

template <class Value, class Ref1, class Ptr1, class Ref2, class Ptr2>
bool operator!=(const Rb_tree_iterator<Value, Ref1, Ptr1> &x, const Rb_tree_iterator<Value, Ref2, Ptr2> &y) {
  return x.node != y.node;
}

template <class Value>
void Rb_tree_rotate_left(Rb_tree_node<Value> *x, Rb_tree_node<Value> *&root) {
  Rb_tree_node<Value> *y = x->right;
  x->right = y->left;
  if (y->left != 0) y->left->parent = x;
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

template <class Value>
void Rb_tree_rotate_right(Rb_tree_node<Value> *x, Rb_tree_node<Value> *&root) {
  Rb_tree_node<Value> *y = x->left;
  x->left = y->right;
  if (y->right != 0) y->right->parent = x;
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

template <class Value>
void Rb_tree_rebalance(Rb_tree_node<Value> *x, Rb_tree_node<Value> *&root) {
  x->color = Rb_tree_red;
  while (x != root && x->parent->color == Rb_tree_red) {
    if (x->parent == x->parent->parent->left) {
      Rb_tree_node<Value> *y = x->parent->parent->right;
      if (y && y->color == Rb_tree_red) {
        x->parent->color = Rb_tree_black;
        y->color = Rb_tree_black;
        x->parent->parent->color = Rb_tree_red;
        x = x->parent->parent;
      } else {
        if (x == x->parent->right) {
          x = x->parent;
          Rb_tree_rotate_left(x, root);
        }
        x->parent->color = Rb_tree_black;
        x->parent->parent->color = Rb_tree_red;
        Rb_tree_rotate_right(x->parent->parent, root);
      }
    } else {
      Rb_tree_node<Value> *y = x->parent->parent->left;
      if (y && y->color == Rb_tree_red) {
        x->parent->color = Rb_tree_black;
        y->color = Rb_tree_black;
        x->parent->parent->color = Rb_tree_red;
        x = x->parent->parent;
      } else {
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
template <class Value>
Rb_tree_node<Value> *Rb_tree_rebalance_for_erase(Rb_tree_node<Value> *z, Rb_tree_node<Value> *&root,
                                                 Rb_tree_node<Value> *&leftmost, Rb_tree_node<Value> *&rightmost) {
  Rb_tree_node<Value> *y = z;
  Rb_tree_node<Value> *x = 0;
  Rb_tree_node<Value> *x_parent = 0;

  if (y->left == 0)        // z has at most one non-null child. y == z.
    x = y->right;          // x might be null.
  else if (y->right == 0)  // z has exactly one non-null child. y == z.
    x = y->left;           // x is not null.
  else {                   // z has two non-null children.
    y = y->right;          // Set y to z's successor. x might be null.
    while (y->left != 0) y = y->left;
    x = y->right;
  }

  if (y != z) {  // relink y in place of z. y is z's successor
    z->left->parent = y;
    y->left = z->left;
    if (y != z->right) {
      x_parent = y->parent;
      if (x) x->parent = y->parent;
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
    // y now points to node to be actually deleted
  } else {  // y == z
    x_parent = y->parent;
    if (x) x->parent = y->parent;

    if (root == z)
      root = x;
    else if (z->parent->left == z)
      z->parent->left = x;
    else
      z->parent->right = x;

    if (leftmost == z) {
      if (z->right == 0)  // z->left must be null also
        leftmost = z->parent;
      // makes leftmost == header if z == root
      else
        leftmost = Rb_tree_node<Value>::minimum(x);
    }
    if (rightmost == z) {
      if (z->left == 0)  // z->right must be null also
        rightmost = z->parent;
      // make s rightmost == header if z == root
      else  // x == z->left
        rightmost = Rb_tree_node<Value>::maximum(x);
    }
  }

  if (y->color != Rb_tree_red) {
    while (x != root && (x == 0 || x->color == Rb_tree_black))
      if (x == x_parent->left) {
        Rb_tree_node<Value> *w = x_parent->right;
        if (w->color == Rb_tree_red) {
          w->color = Rb_tree_black;
          x_parent->color = Rb_tree_red;
          Rb_tree_rotate_left(x_parent, root);
          w = x_parent->right;
        }
        if ((w->left == 0 || w->left->color == Rb_tree_black) && (w->right == 0 || w->right->color == Rb_tree_black)) {
          w->color = Rb_tree_red;
          x = x_parent;
          x_parent = x_parent->parent;
        } else {
          if (w->right == 0 || w->right->color == Rb_tree_black) {
            if (w->left) w->left->color = Rb_tree_black;
            w->color = Rb_tree_red;
            Rb_tree_rotate_right(w, root);
            w = x_parent->right;
          }
          w->color = x_parent->color;
          x_parent->color = Rb_tree_black;
          if (w->right) w->right->color = Rb_tree_black;
          Rb_tree_rotate_left(x_parent, root);
          break;
        }
      } else {  // same as above, with right <-> left
        Rb_tree_node<Value> *w = x_parent->left;
        if (w->color == Rb_tree_red) {
          w->color = Rb_tree_black;
          x_parent->color = Rb_tree_red;
          Rb_tree_rotate_right(x_parent, root);
          w = x_parent->left;
        }
        if ((w->right == 0 || w->right->color == Rb_tree_black) && (w->left == 0 || w->left->color == Rb_tree_black)) {
          w->color = Rb_tree_red;
          x = x_parent;
          x_parent = x_parent->parent;
        } else {
          if (w->left == 0 || w->left->color == Rb_tree_black) {
            if (w->right) w->right->color = Rb_tree_black;
            w->color = Rb_tree_red;
            Rb_tree_rotate_left(w, root);
            w = x_parent->left;
          }
          w->color = x_parent->color;
          x_parent->color = Rb_tree_black;
          if (w->left) w->left->color = Rb_tree_black;
          Rb_tree_rotate_right(x_parent, root);
          break;
        }
      }
    if (x) x->color = Rb_tree_black;
  }
  return y;
}

template <class T, class Alloc>
class Rb_tree_base {
 public:
  typedef Alloc allocator_type;
  typedef typename Alloc::template rebind<Rb_tree_node<T> >::other node_allocator_type;

  allocator_type get_allocator() const { return node_allocator; }

 protected:
  Rb_tree_node<T> *header;
  allocator_type value_allocator;
  node_allocator_type node_allocator;

  Rb_tree_node<T> *get_node() { return node_allocator.allocate(1); }
  void put_node(Rb_tree_node<T> *p) { node_allocator.deallocate(p, 1); }

 public:
  Rb_tree_base(const allocator_type &a) { header = get_node(); }
  ~Rb_tree_base() { put_node(header); }
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc = std::allocator<Value> >
class Rb_tree : protected Rb_tree_base<Value, Alloc> {
  typedef Rb_tree_base<Value, Alloc> Base;

 protected:
  typedef Rb_tree_node<Value> *link_type;
  typedef Rb_tree_color_type color_type;

 public:
  typedef Key key_type;
  typedef Value value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename Base::allocator_type allocator_type;
  allocator_type get_allocator() const { return Base::get_allocator(); }

 protected:
  using Base::get_node;
  using Base::header;
  using Base::put_node;
  using Base::value_allocator;

  link_type create_node(const value_type &x) {
    link_type tmp = get_node();
    try {
      value_allocator.construct(&tmp->value_field, x);
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
    value_allocator.destroy(&p->value_field);
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

  static link_type minimum(link_type x) { return (link_type)Rb_tree_node<Value>::minimum(x); }
  static link_type maximum(link_type x) { return (link_type)Rb_tree_node<Value>::maximum(x); }

 public:
  typedef Rb_tree_iterator<value_type, reference, pointer> iterator;
  typedef Rb_tree_iterator<value_type, const_reference, const_pointer> const_iterator;

  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 private:
  iterator insert(link_type x_, link_type y_, const value_type &v);
  link_type copy(link_type x, link_type p);
  void erase(link_type x);
  void empty_initialize() {
    color(header) = Rb_tree_red;
    root() = 0;
    leftmost() = header;
    rightmost() = header;
  }

 public:
  Rb_tree() : Base(allocator_type()), node_count(0), key_compare(Compare()) { empty_initialize(); }

  Rb_tree(const Compare &comp) : Base(allocator_type()), node_count(0), key_compare(comp) { empty_initialize(); }

  Rb_tree(const Compare &comp, const allocator_type &a) : Base(a), node_count(0), key_compare(comp) {
    empty_initialize();
  }

  Rb_tree(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x)
      : Base(x.get_allocator()), node_count(0), key_compare(x.key_compare) {
    if (x.root() == 0) {
      empty_initialize();
    } else {
      root() = copy(x.root(), header);
      leftmost() = minimum(root());
      rightmost() = maximum(root());
    }
    node_count = x.node_count;
  }

  ~Rb_tree() { clear(); }

  Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &operator=(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x);

 public:
  // 접근자
  Compare key_comp() const { return key_compare; }
  iterator begin() { return leftmost(); }
  const_iterator begin() const { return leftmost(); }
  iterator end() { return header; }
  const_iterator end() const { return header; }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
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
  pair<iterator, bool> insert_unique(const value_type &x);
  iterator insert_unique(iterator position, const value_type &x);
  template <class InputIterator>
  void insert_unique(InputIterator first, InputIterator last);

  // 삭제
  void erase(iterator position);
  size_type erase(const key_type &x);
  void erase(iterator first, iterator last);
  void erase(const key_type *first, const key_type *last);
  void clear() {
    if (node_count != 0) {
      erase(root());
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
bool operator==(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
                const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
bool operator<(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
               const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
bool operator!=(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
                const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return !(x == y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
bool operator>(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
               const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return y < x;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
bool operator<=(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
                const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return !(y < x);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
bool operator>=(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
                const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return !(x < y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::operator=(
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
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert(link_type x_, link_type y_, const Value &v) {
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
    if (y == rightmost()) rightmost() = z;
  }
  parent(z) = y;
  left(z) = 0;
  right(z) = 0;
  Rb_tree_rebalance(z, header->parent);
  ++node_count;
  return iterator(z);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
pair<typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, bool>
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const value_type &v) {
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
      return pair<iterator, bool>(insert(x, y, v), true);
    else
      --j;
  }
  if (key_compare(key(j.node), KeyOfValue()(v))) return pair<iterator, bool>(insert(x, y, v), true);
  return pair<iterator, bool>(j, false);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(iterator position, const value_type &v) {
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
    if (key_compare(key(before.node), KeyOfValue()(v)) && key_compare(KeyOfValue()(v), key(position.node))) {
      if (right(before.node) == 0)
        return insert(0, before.node, v);
      else
        return insert(position.node, position.node, v);
    } else
      return insert_unique(v).first;
  }
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
template <class InputIterator>
void Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(InputIterator first, InputIterator last) {
  for (; first != last; ++first) insert_unique(*first);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator position) {
  link_type y =
      (link_type)Rb_tree_rebalance_for_erase((link_type)position.node, header->parent, header->left, header->right);
  destroy_node(y);
  --node_count;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::size_type
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(const key_type &x) {
  ft::pair<iterator, iterator> p = equal_range(x);
  size_type n = std::distance(p.first, p.second);
  erase(p.first, p.second);
  return n;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::link_type
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::copy(link_type x, link_type p) {
  // structural copy.  x and p must be non-null.
  link_type top = clone_node(x);
  top->parent = p;

  try {
    if (x->right) top->right = copy(right(x), top);
    p = top;
    x = left(x);

    while (x != 0) {
      link_type y = clone_node(x);
      p->left = y;
      y->parent = p;
      if (x->right) y->right = copy(right(x), y);
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
void Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator first, iterator last) {
  if (first == begin() && last == end())
    clear();
  else
    while (first != last) erase(first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(const key_type *first, const key_type *last) {
  while (first != last) erase(*first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find(const key_type &k) {
  link_type y = header;  // Last node which is not less than k.
  link_type x = root();  // Current node.

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
  link_type y = header;  // Last node which is not less than k.
  link_type x = root();  // Current node.

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
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::count(const key_type &k) const {
  ft::pair<const_iterator, const_iterator> p = equal_range(k);
  size_type n = std::distance(p.first, p.second);
  return n;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(const key_type &k) {
  link_type y = header;  // Last node which is not less than k.
  link_type x = root();  // Current node.

  while (x != 0)
    if (!key_compare(key(x), k))
      y = x, x = left(x);
    else
      x = right(x);

  return iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(const key_type &k) const {
  link_type y = header;  // Last node which is not less than k.
  link_type x = root();  // Current node.

  while (x != 0)
    if (!key_compare(key(x), k))
      y = x, x = left(x);
    else
      x = right(x);

  return const_iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::upper_bound(const key_type &k) {
  link_type y = header;  // Last node which is greater than k.
  link_type x = root();  // Current node.

  while (x != 0)
    if (key_compare(k, key(x)))
      y = x, x = left(x);
    else
      x = right(x);

  return iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::upper_bound(const key_type &k) const {
  link_type y = header;  // Last node which is greater than k.
  link_type x = root();  // Current node.

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
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::equal_range(const key_type &k) {
  return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
ft::pair<typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator,
         typename Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator>
Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::equal_range(const key_type &k) const {
  return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
}

}  // namespace ft

#endif
