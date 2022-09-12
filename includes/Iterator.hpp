#pragma once

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

   		RandomAccessIterator operator+(difference_type n) const { return (RandomAccessIterator(_ptr + n)); }
        RandomAccessIterator operator-(difference_type n) const { return (RandomAccessIterator(_ptr - n)); }
	
	    RandomAccessIterator& operator+=(difference_type n) {
            _ptr += n;
            return (*this);
        }
		
        RandomAccessIterator& operator-=(difference_type n) {
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

		ReverseIterator() : _it() {}
		explicit ReverseIterator(iterator_type x) : _it(x) {}

		template <class U>
		ReverseIterator(const ReverseIterator<U>& other) { *this = other; }

		template<class U>
		ReverseIterator& operator=(const ReverseIterator<U>& other) {
			_it = other._it;
			return (*this);
		}

		iterator_type base() const { return (_it); }
		reference operator*() const { return (*_it); }
		pointer operator->() { return (_it); }

		ReverseIterator& operator++() {
			_it--;
			return (*this);
		}

		ReverseIterator operator++(int) {
			ReverseIterator tmp = *this;
			--(*this);
			return (tmp);
		}

		ReverseIterator& operator--() {
			_it++;
			return (*this);
		}

		ReverseIterator operator--(int) {
			ReverseIterator tmp = *this;
			++(*this);
			return (tmp);
		}

		friend bool operator==(const ReverseIterator& lhs, const ReverseIterator& rhs) { return (lhs._it == rhs._it); }
		friend bool operator!=(const ReverseIterator& lhs, const ReverseIterator& rhs) { return (lhs._it != rhs._it); }
	
	private:
		iterator_type _it;
};
};