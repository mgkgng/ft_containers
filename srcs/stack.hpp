#pragma once

#include "vector.hpp"

namespace ft {

template<class T, class Container = ft::vector<T> >
class stack {
		
	typedef Container container_type;
	typedef Container::value_type value_type;
	typedef Container::size_type size_type;
	typedef Container::reference reference;
	typedef Container::const_reference const_reference;

	private:
		Container c;

	public:
		explicit stack(const Container& cont = Container()) {
			this->c = cont;
		}

		stack(const stack& other) {
			*this = other;
		}

		~stack() {}

		stack& operator=(const stack& other) {
			this->c = other.c;
			return (*this);
		}

		reference top() {
			return (c.back());
		}

		const_reference top() {
			return (c.back());
		}

		bool empty() const {
			return (c.empty());
		}
		
		size_type size() const {
			return (c.size());
		}

		void push(const value_type& value) {
			c.push_back(value);
		}

		void pop() {
			c.pop_back();
		}
};

};