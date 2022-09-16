#pragma once

#include "./vector.hpp"

namespace ft {

template<class T, class Container = ft::vector<T> >
class stack {

	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;
		
		Container c;

		stack() {}

		explicit stack(const Container& cont) : c(cont) {}

		stack(stack const & other) { *this = other; }

		stack& operator=(stack const & other) {
			if (*this == other)
				return (*this);
			this->c = other.c;
			return (*this);
		}
	
		~stack() {}

		reference top() { return (c.back()); }
		const_reference top() const { return (c.back()); }
		bool empty() const { return (c.empty()); }
		size_type size() const { return (c.size()); }

		void push(const value_type& value) { c.push_back(value); }
		void pop() { c.pop_back(); }
};

template<class T, class Container>
bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return (lhs.c == rhs.c); }
template<class T, class Container>
bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return (lhs.c != rhs.c); }
template<class T, class Container>
bool operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return (lhs.c < rhs.c); }
template<class T, class Container>
bool operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return (lhs.c <= rhs.c); }
template<class T, class Container>
bool operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return (lhs.c > rhs.c); }
template<class T, class Container>
bool operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) { return (lhs.c >= rhs.c); }
};