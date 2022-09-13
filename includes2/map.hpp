#pragma once

#include "./RBTree.hpp"
#include "./lib.hpp"
#include "./pair.hpp"

namespace ft {

template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
	public:
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef ft::pair<const Key, T> 	value_type;
		typedef const value_type		const_value_type;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef Compare					key_compare;
		typedef Allocator				allocator_type;
		typedef typename allocator_type::pointer		pointer;
		typedef typename allocator_type::const_pointer	const_pointer;
		typedef typename allocator_type::reference	reference;
		typedef typename allocator_type::const_reference const_reference;

		class value_compare {
			friend class map;
			protected:
				Compare comp;
			public:
				typedef bool		result_type;
				typedef	value_type	first_argument_type;
				typedef value_type	second_argument_type;
				value_compare() { comp = std::less<Key>(); }
				value_compare(Compare c) : comp(c) {}
				bool operator()(const value_type& lhs, const value_type& rhs) const { return (comp(lhs.first, rhs.first)); }
		};

		typedef RBtree<value_type, value_compare>	tree_type;

		typedef RBnode<value_type>				node;
		typedef RBnode<const_value_type>		const_node;
		typedef std::allocator<node>			node_allocator;

		typedef RBiter<node>				iterator;
		typedef RBiter<const_node>			const_iterator;
		typedef ft::ReverseIter<iterator>	reverse_iterator;
		typedef ft::ReverseIter<const_iterator>	const_reverse_iterator;

		tree_type 		tree;
		key_compare		compKey;
		value_compare	compVal;
		allocator_type	alloc;

		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) {
			this->alloc = alloc;
			this->compKey = comp;
			this->compVal = value_compare(comp);
			this->tree = tree_type();
			while (first != last)
				this->tree.add(*first++);
		}

		iterator begin() { return iterator(this->tree.min()); }
		const_iterator begin() const { return const_iterator(this->tree.min()); }
		iterator end() { return iterator(); }
		const_iterator end() const { return const_iterator(); }
		reverse_iterator rbegin() { return reverse_iterator(this->tree.end()); }
		const_reverse_iterator rbegin() const { return reverse_iterator(this->tree.end()); }
		reverse_iterator rend() { return reverse_iterator(this->tree.begin()); }
		const_reverse_iterator rend() const { return reverse_iterator(this->tree.begin()); }};


};