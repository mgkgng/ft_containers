#pragma once

#include "lib.hpp"

namespace ft {

template<typename Iter>
class ReverseIterator {

	protected:
		typedef ft::iterator_traits<Iter>		traits_type;

	public:
		typedef Iter									iterator_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::pointer			pointer;
		typedef typename traits_type::reference			reference;

		ReverseIterator() : _it() {}

		explicit ReverseIterator(iterator_type x) : _it(x) {}

		template <class U>
		ReverseIterator(const ReverseIterator<U>& other) {
			*this = other;
		}

		template<class U>
		ReverseIterator& operator=(const ReverseIterator<U>& other) {
			_it = other._it;
			return (*this);
		}

		iterator_type base() const {
			// Returns the underlying base iterator.
			// The base iterator referes to the element that is next to the element the reverse_iterator is currently pointing to.
			return (_it);
		}

		reference operator*() const {
			return (*_it);
		}

		pointer operator->() {
			return (_it);
		}

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

		friend bool operator==(const ReverseIterator& lhs, const ReverseIterator& rhs) {
			return (lhs._it == rhs._it);
		}

		friend bool operator!=(const ReverseIterator& lhs, const ReverseIterator& rhs) {
			return (lhs._it != rhs._it);
		}
	
	private:
		iterator_type _it;
};

};