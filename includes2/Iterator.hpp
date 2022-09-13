#pragma once

#include <memory>

namespace ft {

template <class T>
class IterVector {
	public:
		typedef ft::iterator_traits<T>						iterator_traits;
		typedef typename iterator_traits::value_type		value_type;
		typedef typename iterator_traits::difference_type	difference_type;
		typedef typename iterator_traits::reference			reference;
		typedef typename iterator_traits::pointer			pointer;
		
    	operator IterVector<value_type const *>() const { return IterVector<value_type const *>(ptr); }

		IterVector() : ptr(NULL) {}
		IterVector(pointer p) : ptr(p) {}
		IterVector(const IterVector<T> &other) { *this = other; }
		~IterVector() {}

		IterVector&  operator++() {
			ptr++;
			return (*this);
		}

		IterVector operator++(int) {
			IterVector tmp = *this;
			++(*this);
			return (tmp);
		}


		IterVector& operator--() {
			ptr--;
			return (*this);
		}

		IterVector operator--(int) {
			IterVector tmp = *this;
			--(*this);
			return (tmp);
		}

   		IterVector operator+(int n) {
			IterVector res(*this);
			res += n;
			return (res); 
		}
        IterVector operator-(int n) { 
			IterVector res(*this);
			res -= n;
			return (res); 
		}

		friend IterVector& operator+(int n, IterVector& it) {
			return (it += n); 
		}

		difference_type operator-(IterVector& it) { 
			return (this->ptr - it.base());
		}

		difference_type operator-(IterVector<value_type const *> it) { 
			return (this->ptr - it.base());
		}
		
	    IterVector& operator+=(int n) {
            ptr += n;
            return (*this);
        }
		
        IterVector& operator-=(int n) {
            ptr -= n;
            return (*this);
        }

		pointer base() const { return (this->ptr); }
		pointer operator->() const { return (this->ptr); }
		reference operator[](difference_type n) const { return ptr[n]; }
		reference operator*() const { return *ptr; }

		friend bool operator==(const IterVector& lhs, const IterVector& rhs) { return (lhs.ptr == rhs.ptr); }
		friend bool operator!=(const IterVector& lhs, const IterVector& rhs) { return (!(lhs.ptr == rhs.ptr)); }

	private:
		pointer ptr;
};

template<typename Iter1, typename Iter2>
bool operator==(const IterVector<Iter1>& lhs, const IterVector<Iter2>& rhs) {
	return ((lhs.base() == rhs.base()) ? true : false);
}
template<typename Iter1, typename Iter2>
bool operator!=(const IterVector<Iter1>& lhs, const IterVector<Iter2>& rhs) {
	return (!(lhs.base() == rhs.base()));
}
template<typename Iter1, typename Iter2>
bool operator<(const IterVector<Iter1>& lhs, const IterVector<Iter2>& rhs) {
	return ((lhs.base() < rhs.base()) ? true : false);
}
template<typename Iter1, typename Iter2>
bool operator>=(const IterVector<Iter1>& lhs, const IterVector<Iter2>& rhs) {
	return (!(lhs.base() < rhs.base()));
}
template<typename Iter1, typename Iter2>
bool operator>(const IterVector<Iter1>& lhs, const IterVector<Iter2>& rhs) {
	return ((lhs.base() > rhs.base()) ? true : false);
}
template<typename Iter1, typename Iter2>
bool operator<=(const IterVector<Iter1>& lhs, const IterVector<Iter2>& rhs) {
	return (!(lhs.base() > rhs.base()));
}


template<typename Iter>
class ReverseIter {

	public:
		typedef Iter										iterator_type;
		typedef typename Iter::iterator_traits				iterator_traits;
		typedef typename iterator_traits::value_type		value_type;
		typedef typename iterator_traits::difference_type	difference_type;
		typedef typename iterator_traits::pointer			pointer;
		typedef typename iterator_traits::reference			reference;

    	// operator Iter<value_type const *>() const { return Iter<value_type const *>(ptr); }

		ReverseIter() : it() {}
		explicit ReverseIter(iterator_type x) : it(x) {}

		template <class U>
		ReverseIter(const ReverseIter<U>& other) { *this = other; }
		template<class U>
		ReverseIter& operator=(const ReverseIter<U>& other) {
			it = other.base();
			return (*this);
		}

		iterator_type base() const { return (this->it); }
		reference operator*() const {
			Iter tmp = this->it;
			return (*--tmp);
		}
		pointer operator->() const { return &operator*(); }
		reference operator[](difference_type n) const { return this->base()[-n - 1]; }


		ReverseIter& operator++() {
			it--;
			return (*this);
		}

		ReverseIter operator++(int) {
			ReverseIter tmp = *this;
			--(*this);
			return (tmp);
		}

		ReverseIter& operator--() {
			it++;
			return (*this);
		}

		ReverseIter operator--(int) {
			ReverseIter tmp = *this;
			++(*this);
			return (tmp);
		}

		ReverseIter operator+(int n) {
			ReverseIter res(*this);
			res -= n;
			return (res); 
		}
        ReverseIter operator-(int n) { 
			ReverseIter res(*this);
			res += n;
			return (res); 
		}

		difference_type operator-(ReverseIter& it) { 
			return (this->it - it.base());
		}

		difference_type operator-(ReverseIter<value_type const *> it) { 
			return (this->it - it.base());
		}

	    ReverseIter& operator+=(int n) {
            it -= n;
            return (*this);
        }
		
        ReverseIter& operator-=(int n) {
            it += n;
            return (*this);
        }

		friend bool operator==(const ReverseIter& lhs, const ReverseIter& rhs) { return (lhs.it == rhs.it); }
		friend bool operator!=(const ReverseIter& lhs, const ReverseIter& rhs) { return (lhs.it != rhs.it); }
	
	private:
		iterator_type it;
};

template<typename Iter1, typename Iter2>
bool operator==(const ReverseIter<Iter1>& lhs, const ReverseIter<Iter2>& rhs) {
	return ((lhs.base() == rhs.base()) ? true : false);
}
template<typename Iter1, typename Iter2>
bool operator!=(const ReverseIter<Iter1>& lhs, const ReverseIter<Iter2>& rhs) {
	return (!(lhs.base() == rhs.base()));
}
template<typename Iter1, typename Iter2>
bool operator<(const ReverseIter<Iter1>& lhs, const ReverseIter<Iter2>& rhs) {
	return ((lhs.base() < rhs.base()) ? true : false);
}
template<typename Iter1, typename Iter2>
bool operator>=(const ReverseIter<Iter1>& lhs, const ReverseIter<Iter2>& rhs) {
	return (!(lhs.base() < rhs.base()));
}
template<typename Iter1, typename Iter2>
bool operator>(const ReverseIter<Iter1>& lhs, const ReverseIter<Iter2>& rhs) {
	return ((lhs.base() > rhs.base()) ? true : false);
}
template<typename Iter1, typename Iter2>
bool operator<=(const ReverseIter<Iter1>& lhs, const ReverseIter<Iter2>& rhs) {
	return (!(lhs.base() > rhs.base()));
}

};