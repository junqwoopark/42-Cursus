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

template <class Value>
struct Rb_tree_iterator {
  typedef Value value_type;
  typedef Value &reference;
  typedef Value *pointer;
  typedef ptrdiff_t difference_type;

  typedef std::bidirectional_iterator_tag iterator_category;

  typedef Rb_tree_node<Value> *link_type;

  link_type node;

 public:
  Rb_tree_iterator() {}
  Rb_tree_iterator(link_type x) { node = x; }
  Rb_tree_iterator(const Rb_tree_iterator<Value> &it) { node = it.node; }

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

  bool operator==(const Rb_tree_iterator<Value> &x) const { return node == x.node; }
  bool operator!=(const Rb_tree_iterator<Value> &x) const { return node != x.node; }

 protected:
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
};

template <class Value>
struct Rb_tree_const_iterator {
  typedef Value value_type;
  typedef const Value &reference;
  typedef const Value *pointer;
  typedef ptrdiff_t difference_type;
  typedef std::bidirectional_iterator_tag iterator_category;

  typedef Rb_tree_node<Value> *link_type;

  link_type node;

  Rb_tree_const_iterator() {}
  Rb_tree_const_iterator(link_type x) { node = x; }
  Rb_tree_const_iterator(const Rb_tree_iterator<Value> &it) { node = it.node; }
  Rb_tree_const_iterator(const Rb_tree_const_iterator<Value> &it) { node = it.node; }

  reference operator*() const { return link_type(node)->value_field; }
  pointer operator->() const { return &operator*(); }

  Rb_tree_const_iterator &operator++() {
    increment();
    return *this;
  }

  Rb_tree_const_iterator operator++(int) {
    Rb_tree_const_iterator tmp = *this;
    increment();
    return tmp;
  }

  Rb_tree_const_iterator &operator--() {
    decrement();
    return *this;
  }

  Rb_tree_const_iterator operator--(int) {
    Rb_tree_const_iterator tmp = *this;
    decrement();
    return tmp;
  }

  bool operator==(const Rb_tree_const_iterator<Value> &x) const { return node == x.node; }
  bool operator!=(const Rb_tree_const_iterator<Value> &x) const { return node != x.node; }

 private:
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
};

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
  Rb_tree_base(const allocator_type &a = allocator_type()) : value_allocator(a) { header = get_node(); }
  ~Rb_tree_base() { put_node(header); }
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc = std::allocator<Value> >
class Rb_tree : protected Rb_tree_base<Value, Alloc> {
  typedef Rb_tree_base<Value, Alloc> Base;
  typedef Rb_tree_node<Value> *link_type;
  typedef Rb_tree_color_type color_type;
  using Base::get_node;
  using Base::header;
  using Base::put_node;
  using Base::value_allocator;

 public:
  typedef Key key_type;
  typedef Value value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef Rb_tree_iterator<Value> iterator;
  typedef Rb_tree_const_iterator<Value> const_iterator;

  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  typedef typename Base::allocator_type allocator_type;
  allocator_type get_allocator() const { return Base::get_allocator(); }

 private:
  size_type node_count;
  Compare key_compare;

  link_type create_node(const value_type &x) {
    link_type tmp = get_node();
    try {
      value_allocator.construct(&tmp->value_field, x);
      tmp->left = 0;
      tmp->right = 0;
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

  link_type &root() const { return (link_type &)(header->parent); }
  link_type &leftmost() const { return (link_type &)(header->left); }
  link_type &rightmost() const { return (link_type &)(header->right); }

  static link_type &uncle(link_type x) {
    return is_left_child(x->parent) ? x->parent->parent->right : x->parent->parent->left;
  }
  static link_type &sibling(link_type x) { return is_left_child(x) ? x->parent->right : x->parent->left; }
  static bool is_left_child(link_type x) { return x == x->parent->left; }
  static bool is_right_child(link_type x) { return x == x->parent->right; }
  static bool is_root(link_type x) { return x->parent == 0; }
  static reference value(link_type x) { return x->value_field; }
  static const Key &key(link_type x) { return KeyOfValue()(value(x)); }
  static color_type &color(link_type x) { return (color_type &)(x->color); }

  static link_type minimum(link_type x) { return Rb_tree_node<Value>::minimum(x); }
  static link_type maximum(link_type x) { return Rb_tree_node<Value>::maximum(x); }

 public:
  Rb_tree() : Base(allocator_type()), node_count(0), key_compare(Compare()) { empty_initialize(); }

  Rb_tree(const Compare &comp, const allocator_type &a = allocator_type()) : Base(a), node_count(0), key_compare(comp) {
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

  Rb_tree &operator=(const Rb_tree &x) {
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

  pair<iterator, bool> insert_unique(const value_type &v) {
    link_type y = header;
    link_type x = root();
    bool comp = true;
    while (x != 0) {
      y = x;
      comp = key_compare(KeyOfValue()(v), key(x));
      x = comp ? x->left : x->right;
    }
    iterator j = iterator(y);
    if (comp) {
      if (j == begin())
        return pair<iterator, bool>(insert(y, v), true);
      else
        --j;
    }
    if (key_compare(key(j.node), KeyOfValue()(v))) return pair<iterator, bool>(insert(y, v), true);
    return pair<iterator, bool>(j, false);
  }

  iterator insert_unique(iterator position, const value_type &v) {
    if (position.node == header->left) {
      if (size() > 0 && key_compare(KeyOfValue()(v), key(position.node)))
        return insert(position.node, v);
      else
        return insert_unique(v).first;
    } else if (position.node == header) {
      if (key_compare(key(rightmost()), KeyOfValue()(v)))
        return insert(rightmost(), v);
      else
        return insert_unique(v).first;
    } else {
      iterator before = position;
      --before;
      if (key_compare(key(before.node), KeyOfValue()(v)) && key_compare(KeyOfValue()(v), key(position.node))) {
        if (before.node->right == 0)
          return insert(before.node, v);
        else
          return insert(position.node, v);
      } else
        return insert_unique(v).first;
    }
  }
  template <class InputIterator>
  void insert_unique(InputIterator first, InputIterator last) {
    for (; first != last; ++first) insert_unique(*first);
  };

  // 삭제
  void erase(iterator position) {
    link_type n = Rb_tree_rebalance_for_erase(position.node);
    destroy_node(n);
    --node_count;
  }

  size_type erase(const key_type &x) {
    ft::pair<iterator, iterator> p = equal_range(x);
    size_type n = std::distance(p.first, p.second);
    erase(p.first, p.second);
    return n;
  }

  void erase(iterator first, iterator last) {
    if (first == begin() && last == end())
      clear();
    else
      while (first != last) erase(first++);
  }

  void erase(const key_type *first, const key_type *last) {
    while (first != last) erase(*first++);
  }

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
  iterator find(const key_type &k) {
    link_type y = header;  // Last node which is not less than k.
    link_type x = root();  // Current node.

    while (x != 0)
      if (!key_compare(key(x), k))
        y = x, x = x->left;
      else
        x = x->right;

    iterator j = iterator(y);
    return (j == end() || key_compare(k, key(j.node))) ? end() : j;
  }

  const_iterator find(const key_type &k) const {
    link_type y = header;  // Last node which is not less than k.
    link_type x = root();  // Current node.

    while (x != 0)
      if (!key_compare(key(x), k))
        y = x, x = x->left;
      else
        x = x->right;

    const_iterator j = const_iterator(y);
    return (j == end() || key_compare(k, key(j.node))) ? end() : j;
  }

  size_type count(const key_type &k) const {
    ft::pair<const_iterator, const_iterator> p = equal_range(k);
    size_type n = std::distance(p.first, p.second);
    return n;
  }

  iterator lower_bound(const key_type &k) {
    link_type y = header;  // Last node which is not less than k.
    link_type x = root();  // Current node.

    while (x != 0)
      if (!key_compare(key(x), k))
        y = x, x = x->left;
      else
        x = x->right;

    return iterator(y);
  }

  const_iterator lower_bound(const key_type &k) const {
    link_type y = header;  // Last node which is not less than k.
    link_type x = root();  // Current node.

    while (x != 0)
      if (!key_compare(key(x), k))
        y = x, x = x->left;
      else
        x = x->right;

    return const_iterator(y);
  }

  iterator upper_bound(const key_type &k) {
    link_type y = header;  // Last node which is greater than k.
    link_type x = root();  // Current node.

    while (x != 0)
      if (key_compare(k, key(x)))
        y = x, x = x->left;
      else
        x = x->right;

    return iterator(y);
  }

  const_iterator upper_bound(const key_type &k) const {
    link_type y = header;  // Last node which is greater than k.
    link_type x = root();  // Current node.

    while (x != 0)
      if (key_compare(k, key(x)))
        y = x, x = x->left;
      else
        x = x->right;

    return const_iterator(y);
  }

  ft::pair<iterator, iterator> equal_range(const key_type &k) {
    return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
  }

  ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
    return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
  }

 private:
  void empty_initialize() {
    color(header) = Rb_tree_red;
    root() = 0;
    leftmost() = header;
    rightmost() = header;
  }

  iterator insert(link_type y, const value_type &v) {
    link_type z;

    if (y == header || key_compare(KeyOfValue()(v), key(y))) {
      z = create_node(v);
      y->left = z;
      if (y == header) {
        root() = z;
        rightmost() = z;
      } else if (y == leftmost())
        leftmost() = z;
    } else {
      z = create_node(v);
      y->right = z;
      if (y == rightmost()) rightmost() = z;
    }
    z->parent = y;
    z->left = 0;
    z->right = 0;
    Rb_tree_rebalance_for_insert(z);
    ++node_count;
    return iterator(z);
  }

  link_type copy(link_type x, link_type p) {
    link_type top = clone_node(x);
    top->parent = p;

    try {
      if (x->right) top->right = copy(x->right, top);
      p = top;
      x = x->left;

      while (x != 0) {
        link_type y = clone_node(x);
        p->left = y;
        y->parent = p;
        if (x->right) y->right = copy(x->right, y);
        p = y;
        x = x->left;
      }
    } catch (...) {
      erase(top);
      throw;
    }

    return top;
  }

  void erase(link_type x) {
    // erase without rebalancing.
    while (x != 0) {
      erase(x->right);
      link_type y = x->left;
      destroy_node(x);
      x = y;
    }
  }

  void Rb_tree_rotate_left(link_type x) {
    link_type y = x->right;
    x->right = y->left;
    if (y->left != 0) y->left->parent = x;
    y->parent = x->parent;

    if (x == root())
      root() = y;
    else if (is_left_child(x))
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
  }

  void Rb_tree_rotate_right(link_type x) {
    link_type y = x->left;
    x->left = y->right;
    if (y->right != 0) y->right->parent = x;
    y->parent = x->parent;

    if (x == root())
      root() = y;
    else if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
    y->right = x;
    x->parent = y;
  }

  void Rb_tree_rebalance_for_insert(link_type n) {
    n->color = Rb_tree_red;  // 삽입되는 노드의 색은 RED

  insert_case1:
    if (n == root()) {
      n->color = Rb_tree_black;
      return;
    }
    // insert_case2:
    if (n->parent->color == Rb_tree_black) return;
    // insert_case3:
    link_type u = uncle(n);
    if (u && u->color == Rb_tree_red) {
      n->parent->color = Rb_tree_black;
      u->color = Rb_tree_black;
      n->parent->parent->color = Rb_tree_red;
      n = n->parent->parent;
      goto insert_case1;
    }
    // insert_case4:
    if (n == n->parent->right && n->parent == n->parent->parent->left) {
      Rb_tree_rotate_left(n->parent);
      n = n->left;
    } else if (n == n->parent->left && n->parent == n->parent->parent->right) {
      Rb_tree_rotate_right(n->parent);
      n = n->right;
    }
    // insert_case5:
    n->parent->color = Rb_tree_black;
    n->parent->parent->color = Rb_tree_red;
    if (n == n->parent->left)
      Rb_tree_rotate_right(n->parent->parent);
    else
      Rb_tree_rotate_left(n->parent->parent);
  }

  link_type Rb_tree_rebalance_for_erase(link_type target) {
    link_type successor = target;
    link_type c = 0;
    link_type c_parent = 0;

    if (successor->left == 0)        // target has at most one non-null child. successor == target.
      c = successor->right;          // c might be null.
    else if (successor->right == 0)  // target has exactly one non-null child. successor == target.
      c = successor->left;           // c is not null.
    else {                           // target has two non-null children.
      successor = successor->right;  // Set successor to target's successor. c might be null.
      while (successor->left != 0) successor = successor->left;
      c = successor->right;
    }

    if (successor != target) {  // relink successor in place of target. successor is target's successor
      target->left->parent = successor;
      successor->left = target->left;
      if (successor != target->right) {
        c_parent = successor->parent;
        if (c) c->parent = successor->parent;
        successor->parent->left = c;
        successor->right = target->right;
        target->right->parent = successor;
      } else
        c_parent = successor;
      if (root() == target)
        root() = successor;
      else if (target->parent->left == target)
        target->parent->left = successor;
      else
        target->parent->right = successor;
      successor->parent = target->parent;
      std::swap(successor->color, target->color);
      successor = target;
      // successor now points to node to be actually deleted
    } else {  // successor ==target
      c_parent = successor->parent;
      if (c) c->parent = successor->parent;

      if (root() == target)
        root() = c;
      else if (target->parent->left == target)
        target->parent->left = c;
      else
        target->parent->right = c;

      if (leftmost() == target) {
        if (target->right == 0)  // target->left must be null also
          leftmost() = target->parent;
        // makes leftmost == header if target == root
        else
          leftmost() = Rb_tree_node<Value>::minimum(c);
      }
      if (rightmost() == target) {
        if (target->left == 0)  // target->right must be null also
          rightmost() = target->parent;
        // make s rightmost == header if target == root
        else  // c == target->left
          rightmost() = Rb_tree_node<Value>::maximum(c);
      }
    }

    // simple_case:
    if (successor->color == Rb_tree_black) {
      if (c && c->color == Rb_tree_red) {
        c->color = Rb_tree_black;
        return successor;
      }
    } else {
    delete_case1:
      if (c != root()) return successor;

      // delete_case2:
      link_type s = sibling(c);
      if (s->color == Rb_tree_red) {
        c->parent->color = Rb_tree_red;
        s->color = Rb_tree_black;
        if (is_left_child(c))
          Rb_tree_rotate_left(c->parent);
        else
          Rb_tree_rotate_right(c->parent);
      }
      // delete_case3:
      s = sibling(c);
      if ((c->parent->color == Rb_tree_black) && (s->color == Rb_tree_black) &&
          (s->left == 0 || s->left->color == Rb_tree_black) && (s->right == 0 || s->right->color == Rb_tree_black)) {
        s->color = Rb_tree_red;
        c = c->parent;
        goto delete_case1;
      }

      // delete_case4:
      s = sibling(c);
      if ((c->parent->color == Rb_tree_red) && (s->color == Rb_tree_black) &&
          (s->left == 0 || s->left->color == Rb_tree_black) && (s->right == 0 || s->right->color == Rb_tree_black)) {
        s->color = Rb_tree_red;
        c->parent->color = Rb_tree_black;
        return c;
      }

      // delete_case5:
      s = sibling(c);
      if (s->color == Rb_tree_black) {  // this if statement is trivial,
        // due to case 2 (even though case 2 changed the sibling to a sibling's child,
        // the sibling's child can't be red, since no red parent can have a red child).
        if (is_left_child(c) && (s->right == 0 || s->right->color == Rb_tree_black) &&
            (s->left->color == Rb_tree_red)) {  // this last test is trivial too due to cases 2-4.
          s->color = Rb_tree_red;
          s->left->color = Rb_tree_black;
          Rb_tree_rotate_right(s);
        } else if (is_right_child(c) && (s->left == 0 || s->left->color == Rb_tree_black) &&
                   (s->right->color == Rb_tree_red)) {  // this last test is trivial too due to cases 2-4.
          s->color = Rb_tree_red;
          s->right->color = Rb_tree_black;
          Rb_tree_rotate_left(s);
        }
      }

      // delete_case6:
      s = sibling(c);
      s->color = c->parent->color;
      c->parent->color = Rb_tree_black;
      if (is_left_child(c)) {
        if (s->right) s->right->color = Rb_tree_black;
        Rb_tree_rotate_left(c->parent);
      } else {
        if (s->left) s->left->color = Rb_tree_black;
        Rb_tree_rotate_right(c->parent);
      }
    }

    return successor;
  }
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
bool operator==(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
                const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
bool operator<(const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x,
               const Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &y) {
  return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
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

}  // namespace ft

#endif
