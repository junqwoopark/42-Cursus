#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <cstddef>
#include <type_traits>

namespace ft {

/*
** enable_if
*/
template <bool B, class T = void> struct enable_if {};
template <class T> struct enable_if<true, T> { typedef T type; };

template <class T> struct is_integral : public std::false_type {};
template <> struct is_integral<bool> : public std::true_type {};
template <> struct is_integral<char> : public std::true_type {};
template <> struct is_integral<signed char> : public std::true_type {};
template <> struct is_integral<unsigned char> : public std::true_type {};
template <> struct is_integral<wchar_t> : public std::true_type {};
template <> struct is_integral<char16_t> : public std::true_type {};
template <> struct is_integral<short> : public std::true_type {};
template <> struct is_integral<unsigned short> : public std::true_type {};
template <> struct is_integral<int> : public std::true_type {};
template <> struct is_integral<unsigned int> : public std::true_type {};
template <> struct is_integral<long> : public std::true_type {};
template <> struct is_integral<unsigned long> : public std::true_type {};
template <> struct is_integral<long long> : public std::true_type {};
template <> struct is_integral<unsigned long long> : public std::true_type {};

} // namespace ft

#endif
