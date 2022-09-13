#pragma once

#include <functional>
#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace ft {

template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
	while (first1 != last1)
		if (*first1++ != *first2++)
			return (false);
	return (true);
}

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {
	while (first1 != last1)
		if (!p(*first1++, *first2++))
			return (false);
	return (true);
}

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
	while (first1 != last1 && first2 != last2 && *first1 == *first2) {
		first1++;
		first2++;
	}
	return (*first2 > *first1) ? true : false;
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
	while (first1 < last1 && first2 < last2 && *first1 == *first2) {
		first1++;
		first2++;
	}
	return (comp(first1, first2));
}

// struct true_type {
// 	typedef true_type	type;
// 	typedef bool		value_type;

// 	operator value_type() const {
// 		return (true);
// 	};
// };

// struct false_type {
// 	typedef false_type	type;
// 	typedef bool		value_type;

// 	operator value_type() const {
// 		return (false);
// 	};
// };

template<class T> struct is_integral : public std::false_type {};
template<> struct is_integral<char> : public std::true_type {};
template<> struct is_integral<bool> : public std::true_type {};
template<> struct is_integral<char16_t> : public std::true_type {};
template<> struct is_integral<char32_t> : public std::true_type {};
template<> struct is_integral<wchar_t> : public std::true_type {};
template<> struct is_integral<signed char> : public std::true_type {};
template<> struct is_integral<short int> : public std::true_type {};
template<> struct is_integral<int> : public std::true_type {};
template<> struct is_integral<long int> : public std::true_type {};
template<> struct is_integral<long long int> : public std::true_type {};
template<> struct is_integral<unsigned char> : public std::true_type {};
template<> struct is_integral<unsigned short int> : public std::true_type {};
template<> struct is_integral<unsigned int> : public std::true_type {};
template<> struct is_integral<unsigned long int> : public std::true_type {};
template<> struct is_integral<unsigned long long int> : public std::true_type {};

struct bidrectional_iterator_tag {};
struct random_access_iterator_tag : public bidrectional_iterator_tag {};

template<class Iter>
struct iterator_traits {
	typedef typename Iter::difference_type		difference_type;
	typedef typename Iter::value_type			value_type;
	typedef typename Iter::pointer				pointer;
	typedef typename Iter::reference			reference;
	typedef typename Iter::iterator_category	iterator_category;
};

template<class T>
struct iterator_traits<T*> {
	typedef ptrdiff_t						difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};

template< class T >
struct iterator_traits<const T*> {
	typedef ptrdiff_t						difference_type;
	typedef T							value_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	typedef ft::random_access_iterator_tag	iterator_category;
};

template< bool B, class T = void >
struct enable_if {};

template<class T>
struct enable_if<true, T> {
	typedef T type;
};

template<class Iterable>
int distance(Iterable first, Iterable last) {
	int res = 0;
	while (first++ != last)
		res++;
	return (res);
}

};