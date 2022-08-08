#pragma once

#include "BiDirectionalIterator.hpp"

namespace ft {

template <class T>
class RandomAccessIterator : public ft::BiDirectionalIterator {

	public:
		
		RandomAccessIterator() {
			_ptr = NULL;
		}

		RandomAccessIterator(const RandomAccessIterator<T> &other) {
			_ptr = other._ptr;
		}

		~RandomAccessIterator() {}

   		RandomAccessIterator operator+(difference_type n) const {
			return (RandomAccessIterator(_ptr + n))
		}

        RandomAccessIterator operator-(difference_type n) const {
        	return (RandomAccessIterator(_ptr - n))

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

};

}