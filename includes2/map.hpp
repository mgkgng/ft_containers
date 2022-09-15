#pragma once

#include "./lib.hpp"
#include "./pair.hpp"
#include "./tree.hpp"

namespace ft {

template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {

	public:
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef ft::pair<const Key, T> 	value_type;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef Compare					key_compare;

		class value_compare
		{
			friend class map;

			protected:
				Compare comp;
			public:
				value_compare() {}
				explicit value_compare (Compare c) : comp(c) {}

				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;

				bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
		};

		typedef ft::tree<value_type, value_compare> tree_type;
		typedef ft::treeNode<value_type>			node_type;
		typedef ft::treeNode<const value_type> 		const_node_type;

		typedef ft::IterTree<value_type>			iterator;
		typedef ft::IterTree<const value_type>	const_iterator;
		typedef ft::ReverseIter<iterator> 		reverse_iterator;
		typedef ft::ReverseIter<const_iterator> const_reverse_iterator;

		typedef std::allocator<node_type> 					allocator_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;

		tree_type		tree;
		key_compare		compK;
		value_compare	compV;

		map() {}

		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) {
			(void) alloc;
			this->compK = comp;
			this->compV = value_compare(comp);
			this->tree = tree_type();
			while (first != last)
				this->tree.add(*first++);
		}

		map(map const & other) {
			this->tree = other.tree;
			this->compK = other.compK;
			this->compV = other.compV;
		}

		size_type size() const { return (this->tree.size); }
		size_type max_size() const { return (this->tree.nodeAlloc.max_size()); }
		iterator		begin() { return (iterator(this->tree.min())); }
		const_iterator	begin() const { return (const_iterator(this->tree.min())); }
		iterator		end() { return (iterator()); }
		const_iterator	end() const { return (const_iterator()); }

		void clear() { this->tree.clearTree(); }
};

};