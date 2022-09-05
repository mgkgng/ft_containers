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
		
		RandomAccessIterator() : _ptr(NULL) {}

		RandomAccessIterator(pointer p) : _ptr(p) {}

		RandomAccessIterator(const RandomAccessIterator<T> &other) {
			_ptr = other._ptr;
		}

		~RandomAccessIterator() {}

		RandomAccessIterator&  operator++() {
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

		friend bool operator==(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) {
			return (lhs._ptr == rhs._ptr);
		}

		friend bool operator!=(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) {
			return (!(lhs._ptr == rhs._ptr));
		}

	private:
		pointer _ptr;
};

};