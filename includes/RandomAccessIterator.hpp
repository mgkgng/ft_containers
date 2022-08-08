#pragma once

#include "BiDirectionalIterator.hpp"

namespace ft {

template <class T>
class RandomAccessIterator {

	public:
		typedef T			value_type;
		typedef ptrdiff_t	difference_type;
		typedef T&			reference;
		typedef T*			pointer;
		
		RandomAccessIterator() {
			_ptr = NULL;
		}

		RandomAccessIterator(const RandomAccessIterator<T> &other) {
			_ptr = other._ptr;
		}

		~RandomAccessIterator() {}

   		RandomAccessIterator operator+(difference_type n) const {
			return (RandomAccessIterator(_ptr + n));
		}

        RandomAccessIterator operator-(difference_type n) const {
        	return (RandomAccessIterator(_ptr - n));

		}
	
	    RandomAccessIterator& operator+=(difference_type n) {
            _ptr += n;
            return (*this);
        }
		
        RandomAccessIterator& operator-=(difference_type n) {
            _ptr -= n;
            return (*this);
        }

		reference operator[](difference_type n) const {
			return _ptr[n];
		}

	private:
		pointer _ptr;


};

}