#pragma once

#include "lib.hpp"

namespace ft {

template<typename T>
class BiDirectionalIterator {

// 1. Usability
// 2. Equality / Inequality Comparaison
// 3. Dereferencing
// 4. Incrementable
// 5. Decrementable
// 6. Swappable

	typedef T 			value_type;
	typedef ptrdiff_t	difference_type;
	typedef T&			reference;
	typedef T*			pointer;

	private:
		pointer _ptr;

	public:
		reference operator*() const {
			return (*_ptr);
		}

		pointer operator->() {
			return (_ptr);
		}

		BiDirectionalIterator& operator++() {
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
			return (lhs._ptr != rhs._ptr);
		}
	

};
};