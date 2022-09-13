#pragma once

#include <memory>

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
		RandomAccessIterator(const RandomAccessIterator<T> &other) { _ptr = other._ptr; }
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

   		RandomAccessIterator operator+(int n) {
			RandomAccessIterator res(*this);
			res += n;
			return (res); 
		}
        RandomAccessIterator operator-(int n) { 
			RandomAccessIterator res(*this);
			res -= n;
			return (res); 
		}

		difference_type operator-(RandomAccessIterator& it) { 
			return (this->_ptr - it._ptr);
		}
		
	    RandomAccessIterator& operator+=(int n) {
            _ptr += n;
            return (*this);
        }
		
        RandomAccessIterator& operator-=(int n) {
            _ptr -= n;
            return (*this);
        }

		reference operator[](difference_type n) const { return _ptr[n]; }
		reference operator*() const { return *_ptr; }

		friend bool operator==(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) { return (lhs._ptr == rhs._ptr); }
		friend bool operator!=(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) { return (!(lhs._ptr == rhs._ptr)); }

	private:
		pointer _ptr;
};

template<typename Iter>
class ReverseIterator {

	public:
		typedef Iter							iterator_type;
		typedef typename Iter::difference_type	difference_type;
		typedef typename Iter::pointer			pointer;
		typedef typename Iter::reference		reference;

		ReverseIterator() : it() {}
		explicit ReverseIterator(iterator_type x) : it(x) {}

		template <class U>
		ReverseIterator(const ReverseIterator<U>& other) { *this = other; }
		template<class U>
		ReverseIterator& operator=(const ReverseIterator<U>& other) {
			it = other.it;
			return (*this);
		}

		iterator_type base() const { return (it); }
		reference operator*() const {
			Iter tmp = it;
			return (*--tmp);
		}
		pointer operator->() { return &operator*(); }

		ReverseIterator& operator++() {
			it--;
			return (*this);
		}

		ReverseIterator operator++(int) {
			ReverseIterator tmp = *this;
			--(*this);
			return (tmp);
		}

		ReverseIterator& operator--() {
			it++;
			return (*this);
		}

		ReverseIterator operator--(int) {
			ReverseIterator tmp = *this;
			++(*this);
			return (tmp);
		}

		ReverseIterator operator+(difference_type n) const;
		ReverseIterator operator-(difference_type n) const;
		ReverseIterator& operator+=(difference_type n);
		ReverseIterator& operator-=(difference_type n);


		friend bool operator==(const ReverseIterator& lhs, const ReverseIterator& rhs) { return (lhs.it == rhs.it); }
		friend bool operator!=(const ReverseIterator& lhs, const ReverseIterator& rhs) { return (lhs.it != rhs.it); }
	
	private:
		iterator_type it;
};
};