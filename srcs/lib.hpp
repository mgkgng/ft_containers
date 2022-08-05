#pragma once

#include <functional>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string.h>

namespace ft {

template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
	while (first1 < last1)
		if (first1++ != first2++)
			return (false);
	return (true);
}

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {

}

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
	while (first1 < last1 && first2 < last2 && *first1 == *first2) {
		first1++;
		first2++;
	}
	return (*first2 - *first1 > 0) ? true : false;
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
	while (first1 < last1 && first2 < last2 && *first1 == *first2) {
		first1++;
		first2++;
	}
	return (comp(first1, first2));
}

template<class T>
bool is_integral(T value) {
	// bool, char, char16_t, char32_t, wchar_t, signed char, 
	// short int, int, long int, long long int
	// unsigned char, unsigned short int, unsigned int, unsigned logn int, unsigned long long int

}

struct bidrectional_iterator_tag {};
struct random_access_iterator_tag : public bidrectional_iterator_tag {};

template<class Iter>
struct iterator_traits {
	typedef Iter::difference_type	difference_type;
	typedef Iter::value_type		value_type;
	typedef Iter::pointer			pointer;
	typedef Iter::reference			reference;
	typedef Iter::iterator_category	iterator_category;
};

template<class T>
struct iterator_traits<T*> {
	typedef ptrdiff_t	difference_type;
	typedef T			value_type
	typedef pointer		const T*;
	typedef reference	const T&;
	typedef ft::random_access_iterator_tag	iterator_category;
};

template< bool B, class T = void >
struct enable_if {
	typedef T type;
};

template<class InputIt1, class InputIt2>
bool greater(InputIt1 it1, InputIt2 it2) {
	return (*it1 > *it2);
}

};