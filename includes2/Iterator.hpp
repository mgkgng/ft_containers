#pragma once

#include <memory>

namespace ft {

template <class T>
class IterVector {
	public:
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef T&								reference;
		typedef T*								pointer;
		typedef std::random_access_iterator_tag	iterator_category;
		
    	operator IterVector<const T>() const { return (this->ptr); }

		IterVector() : ptr(NULL) {}
		IterVector(pointer p) : ptr(p) {}
		IterVector(IterVector const &other) { *this = other; }
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

		friend IterVector& operator+(int n, IterVector& it) { return (it += n); }

		difference_type operator-(IterVector& it) { return (this->ptr - it.base()); }
		difference_type operator-(IterVector<const value_type> it) { return (this->ptr - it.base()); }
		
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
	return (lhs.base() == rhs.base());
}
template<typename Iter1, typename Iter2>
bool operator!=(const IterVector<Iter1>& lhs, const IterVector<Iter2>& rhs) {
	return (lhs.base() != rhs.base());
}
template<typename Iter1, typename Iter2>
bool operator<(const IterVector<Iter1>& lhs, const IterVector<Iter2>& rhs) {
	return (lhs.base() < rhs.base());
}
template<typename Iter1, typename Iter2>
bool operator>=(const IterVector<Iter1>& lhs, const IterVector<Iter2>& rhs) {
	return (!(lhs.base() < rhs.base()));
}
template<typename Iter1, typename Iter2>
bool operator>(const IterVector<Iter1>& lhs, const IterVector<Iter2>& rhs) {
	return (lhs.base() > rhs.base());
}
template<typename Iter1, typename Iter2>
bool operator<=(const IterVector<Iter1>& lhs, const IterVector<Iter2>& rhs) {
	return (!(lhs.base() > rhs.base()));
}

template<typename Iter>
class ReverseIter {

	public:
		typedef Iter							iterator_type;
		typedef ft::iterator_traits<Iter> 		iterator_traits;
		typedef typename iterator_traits::value_type		value_type;
		typedef typename iterator_traits::difference_type	difference_type;
		typedef typename iterator_traits::pointer			pointer;
		typedef typename iterator_traits::reference			reference;
		typedef typename iterator_traits::iterator_category	iterator_category;

    	// operator ReverseIter<Iter const>() const { return ReverseIter<Iter const>(*it); }
    	// operator ReverseIter<const Iter>() const { return (ReverseIter< const Iter >(it)); }
		ReverseIter() : it() {}
		explicit ReverseIter(iterator_type x) : it(x) {}

		template <class U>
		ReverseIter(const ReverseIter<U>& other) : it(other.base()) {}
		
		operator ReverseIter<const Iter>() const { return this->it; }

		ReverseIter& operator=(const ReverseIter& other) {
			this->it = other.base();
			return (*this);
		}

		iterator_type base() const { return (this->it); }
		reference operator*() const {
			return (*--iterator_type(it));
		}

		pointer operator->() const { return &operator*(); }
		reference operator[](difference_type n) const { return this->base()[-n-1]; }


		ReverseIter& operator++() {
			--it;
			return (*this);
		}

		ReverseIter operator++(int) {
			ReverseIter tmp = *this;
			--(this->it);
			return (tmp);
		}

		ReverseIter& operator--() {
			++it;
			return (*this);
		}

		ReverseIter operator--(int) {
			ReverseIter tmp = *this;
			++(this->it);
			return (tmp);
		}

		ReverseIter operator+(int n) {
			return (ReverseIter(this->it - n));
		}
       
		ReverseIter operator-(int n) { 
			return (ReverseIter(this->it + n));

		}

		template<typename It>
		friend ReverseIter operator+(int n, ReverseIter<It>& it) {
			return ReverseIter(it.base() - n);
		}

		template<typename It>
		friend ReverseIter operator-(int n, ReverseIter<It>& it) {
			return ReverseIter(it.base() + n); 
		}

	    ReverseIter& operator+=(int n) {
            it -= n;
            return (*this);
        }
		
        ReverseIter& operator-=(int n) {
            it += n;
            return (*this);
        }

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
	return (lhs.base() > rhs.base());
}
template<typename Iter1, typename Iter2>
bool operator>=(const ReverseIter<Iter1>& lhs, const ReverseIter<Iter2>& rhs) {
	return (lhs.base() <= rhs.base());
}
template<typename Iter1, typename Iter2>
bool operator>(const ReverseIter<Iter1>& lhs, const ReverseIter<Iter2>& rhs) {
	return (lhs.base() < rhs.base());
}
template<typename Iter1, typename Iter2>
bool operator<=(const ReverseIter<Iter1>& lhs, const ReverseIter<Iter2>& rhs) {
	return (lhs.base() >= rhs.base());
}

template <class Iter1, class Iter2>
ptrdiff_t operator-(const ft::ReverseIter<Iter1>& lhs, const ft::ReverseIter<Iter2>& rhs) {
    return (rhs.base() - lhs.base());
}


};