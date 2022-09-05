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

		reference operator++() {
			_ptr++;
			return (*this);
		}

		RandomAccessIterator operator++(int) {
			RandomAccessIterator tmp = *this;
			++(*this);
			return (tmp);
		}

		RandomAccessIterator& operator--() {
			_ptr--;
			return (*this);
		}

		RandomAccessIterator operator--(int) {
			RandomAccessIterator tmp = *this;
			--(*this);
			return (tmp);
		}

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

		reference operator*() const {
			return *_ptr;
		}



	private:
		pointer _ptr;


};

}