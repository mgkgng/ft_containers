#pragma once

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

		pair& operator=(const pair& other) {
			first = other.first;
			second = other.second;
			return (*this);
		}
};

	template<class T1, class T2>
	pair<T1, T2> make_pair(T1 t, T2 u) {
		return (pair<T1, T2>(t, u));
	}

	template<class T1, class T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return ((lhs.first == rhs.first && lhs.second == rhs.second) ? true : false);
	}
	
	template<class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return ((lhs == rhs) ? false : true);
	}

	template<class T1, class T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (lhs.first == rhs.first) ? ft::lexicographical_compare(lhs.second, rhs.second)
			: ft::lexicographical_compare(lhs.first, rhs.first);
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (!(lhs > rhs));
	}

	template<class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (lhs.first == rhs.first) ? ft::lexicographical_compare(rhs.second, lhs.second)
			: ft::lexicographical_compare(rhs.first, lhs.first);
	}

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (!(lhs < rhs));
	}

};