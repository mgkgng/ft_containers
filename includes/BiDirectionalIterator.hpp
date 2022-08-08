#pragma once

#include "lib.hpp"

namespace ft {

template<class T>
class BiDirectionalIterator {

	public:
		typedef T 			value_type;
		typedef ptrdiff_t	difference_type;
		typedef T&			reference;
		typedef T*			pointer;

		reference operator*() const {
			return (*_ptr);
		}

		pointer operator->() {
			return (_ptr);
		}

		reference operator++() {
			_ptr++;
			return (*this);
		}

		BiDirectionalIterator operator++(int) {
			BiDirectionalIterator tmp = *this;
			++(*this);
			return (tmp);
		}

		BiDirectionalIterator& operator--() {
			_ptr--;
			return (*this);
		}

		BiDirectionalIterator operator--(int) {
			BiDirectionalIterator tmp = *this;
			--(*this);
			return (tmp);
		}

		friend bool operator==(const BiDirectionalIterator& lhs, const BiDirectionalIterator& rhs) {
			return (lhs._ptr == rhs._ptr);
		}

		friend bool operator!=(const BiDirectionalIterator& lhs, const BiDirectionalIterator& rhs) {
			return (!(lhs._ptr == rhs._ptr));
		}

	private:
		pointer _ptr;
};

}