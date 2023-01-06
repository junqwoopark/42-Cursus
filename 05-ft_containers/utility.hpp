#ifndef FT_UTILITY_HPP
#define FT_UTILITY_HPP

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
namespace ft {

template <typename T1, typename T2> struct pair {
  typedef T1 first_type;
  typedef T2 second_type;

  T1 first;
  T2 second;

  pair() : first(), second() {}
  pair(T1 const &t1, T2 const &t2) : first(t1), second(t2) {}

  template <class U1, class U2> pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}

  pair &operator=(pair const &p) {
    first = p.first;
    second = p.second;
    return *this;
  }
};

template <typename T1, typename T2> bool operator==(const pair<T1, T2> &x, const pair<T1, T2> &y) {
  return x.first == y.first && x.second == y.second;
}

template <typename T1, typename T2> bool operator!=(const pair<T1, T2> &x, const pair<T1, T2> &y) {
  return !(x == y);
}

template <class T1, class T2> bool operator<(const pair<T1, T2> &x, const pair<T1, T2> &y) {
  return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
}

template <class T1, class T2> bool operator>(const pair<T1, T2> &x, const pair<T1, T2> &y) {
  return y < x;
}

template <class T1, class T2> bool operator>=(const pair<T1, T2> &x, const pair<T1, T2> &y) {
  return !(x < y);
}

template <class T1, class T2> bool operator<=(const pair<T1, T2> &x, const pair<T1, T2> &y) {
  return !(y < x);
}

template <class T1, class T2> pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }

} // namespace ft

#endif
