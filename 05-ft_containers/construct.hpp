#ifndef CONSTRUCT_HPP
#define CONSTRUCT_HPP

#include <memory>
#include <new>

namespace ft {
// use std::allocator;
template <class T1, class T2> inline void construct(T1 *p, const T2 &value) {
  std::allocator<T1> alloc;
  alloc.construct(p, value);
}

template <class T> inline void destroy(T *pointer) {
  std::allocator<T> alloc;
  alloc.destroy(pointer);
}

template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
  for (; first != last; ++first) {
    destroy(&*first);
  }
}

} // namespace ft

#endif // CONSTRUCT_HPP
