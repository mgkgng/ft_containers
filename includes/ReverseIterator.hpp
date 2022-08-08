#pragma once

#include "lib.hpp"

namespace ft {

template< class Iter >
class ReverseIterator {

	private:
		pointer _ptr;

	public:
		typedef Iter											iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;

		ReverseIterator() {

		}

		explicit ReverseIterator(iterator_type x) {

		}

		template <class U>
		ReverseIterator(const ReverseIterator<U>& other) {

		}

		template<class U>
		ReverseIterator& operator=(const ReverseIterator<U>& other) {
			_ptr = other._ptr;
		}

		iterator_type base() const {
			// Returns the underlying base iterator.
			// The base iterator referes to the element that is next to the element the reverse_iterator is currently pointing to.
			return (_ptr);
		}

		reference operator*() const {
			return (*_ptr);
		}

		pointer operator->() {
			return (_ptr);
		}

		ReverseIterator& operator++() {
			_ptr++;
			return (*this);
		}

		ReverseIterator operator++(int) {
			ReverseIterator tmp = *this;
			++(*this);
			return (tmp);
		}

		ReverseIterator& operator--() {
			_ptr--;
			return (*this);
		}

		ReverseIterator operator--(int) {
			ReverseIterator tmp = *this;
			--(*this);
			return (tmp);
		}

		friend bool operator==(const ReverseIterator& lhs, const ReverseIterator& rhs) {
			return (lhs._ptr == rhs._ptr);
		}

		friend bool operator!=(const ReverseIterator& lhs, const ReverseIterator& rhs) {
			return (lhs._ptr != rhs._ptr);
		}
	


};

};