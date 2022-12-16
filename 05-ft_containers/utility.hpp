#ifndef FT_UTILITY_HPP
#define FT_UTILITY_HPP

namespace ft {

template <typename T1, typename T2> struct pair {
  typedef T1 first_type;
  typedef T2 second_type;

  T1 first;
  T2 second;

  pair() : first(), second() {}
  pair(T1 const &t1, T2 const &t2) : first(t1), second(t2) {}

  pair(const pair<T1, T2> &p) : first(p.first), second(p.second) {}

  pair &operator=(pair const &p) {
    first = p.first;
    second = p.second;
    return *this;
  }
};

template <typename T1, typename T2>
bool operator==(const pair<T1, T2> &x, const pair<T1, T2> &y) {
  return x.first == y.first && x.second == y.second;
}

template <typename T1, typename T2>
bool operator!=(const pair<T1, T2> &x, const pair<T1, T2> &y) {
  return !(x == y);
}

template <class T1, class T2>
bool operator<(const pair<T1, T2> &__x, const pair<T1, T2> &__y) {
  return __x.first < __y.first ||
         (!(__y.first < __x.first) && __x.second < __y.second);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2> &__x, const pair<T1, T2> &__y) {
  return __y < __x;
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2> &__x, const pair<T1, T2> &__y) {
  return !(__x < __y);
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2> &__x, const pair<T1, T2> &__y) {
  return !(__y < __x);
}

} // namespace ft

#endif
