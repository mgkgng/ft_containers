#pragma once

#include "lib.hpp"

namespace ft {

template<typename T1, typename T2>
class pair {
	public:
		typedef T1	first_type;
		typedef T2	second_type;

		T1	first;
		T2	second;

		pair() : first(first_type()), second(second_type()) {}

		pair(const T1& x, const T2& y) : first(x), second(y) {}

		template<class U1, class U2>
		pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

		pair(pair const & other) : first(other.first), second(other.second) {}

		pair& operator=(const pair& other) {
			first = other.first;
			second = other.second;
			return (*this);
		}

		operator pair<const T1, T2>() const { return (pair<const T1, T2>(first, second)); }

		friend bool operator==(pair const & lhs, pair const & rhs) { return ((lhs.first == rhs.first && lhs.second == rhs.second)); }
		friend bool operator!=(pair const & lhs, pair const & rhs) { return (!(lhs == rhs)); }
		friend bool operator<(pair const & lhs, pair const & rhs) { return (lhs.first == rhs.first) ? (lhs.second < rhs.second) : (lhs.first < rhs.first); }
		friend bool operator>(pair const & lhs, pair const & rhs) { return (rhs < lhs); }
		friend bool operator<=(pair const & lhs, pair const & rhs) { return (!(lhs > rhs)); }
		friend bool operator>=(pair const & lhs, pair const & rhs) { return (!(lhs < rhs)); }
};

template<class T1, class T2>
ft::pair<T1, T2> make_pair(T1 t, T2 u) { return (pair<T1, T2>(t, u)); }

};
	
