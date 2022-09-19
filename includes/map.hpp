#pragma once

#include "lib.hpp"
#include "pair.hpp"
#include "tree.hpp"

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

		typedef ft::IterTree<value_type>		iterator;
		typedef ft::IterTree<const value_type>	const_iterator;
		typedef ft::ReverseIter<iterator> 		reverse_iterator;
		typedef ft::ReverseIter<const_iterator> const_reverse_iterator;

		typedef std::allocator<node_type> 					allocator_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;

		map() {}

		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) {
			(void) alloc;
			this->compK = comp;
			this->compV = value_compare(comp);
			this->tree = tree_type();
			while (first != last)
				this->insert(*first++);
		}

		map(map const & other) {
			if (this->tree.size)
				this->tree.clearTree();
			*this = other; 
		}

		~map() { this->tree.clearTree(); }

		map& operator=(const map & other) {
			this->tree = other.tree;
			this->compK = other.compK;
			this->compV = other.compV;
			return (*this);
		}

		ft::pair<iterator, bool> insert(const value_type& value) {
			node_type *pos = this->tree.root;
			while (1) {
				if (!pos || pos->value.first == value.first)
					break;
				pos = (!this->compV(pos->value, value)) ? pos->left : pos->right;
			}
			if (pos)
				return (ft::make_pair<iterator, bool>(iterator(pos, this->tree.min(), this->tree.max()), false));
			node_type *where = tree.add(value);
			return (ft::make_pair<iterator, bool>(iterator(where, this->tree.min(), this->tree.max()), true));
		}

		iterator insert(iterator hint, const value_type& value) {
			node_type *pos = hint.getNode();
			while (1) {
				if (!pos || pos->value.first == value.first)
					break;
				pos = (!this->compV(pos->value, value)) ? pos->left : pos->right;
			}
			if (pos)
				return (iterator(pos, this->tree.min(), this->tree.max()));
			node_type *where = this->tree.add(value);
			return (iterator(where, this->tree.min(), this->tree.max()));
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last) {
			while (first != last)
				this->insert(*first++);
		}

		iterator erase(iterator pos) {
			this->tree.erase(pos.getNode());
			return (iterator());
		}

		iterator erase(iterator first, iterator last) {
			while (first != last)
				this->tree.erase((first++).getNode());
			return (iterator());
		}

		size_type erase(const Key& key) {
			node_type *n = this->tree.root;
			while (1) {
				if (!n || n->value.first == key)
					break;
				n = (!this->compK(n->value.first, key)) ? n->left : n->right;
			}
			if (n)
				this->tree.erase(n);
			return ((!n) ? 0 : 1);
		}

		T& at(const Key& key) { return ((this->find(key))->second); }
		const T& at(const Key& key) const { return ((this->find(key))->second); }

		T& operator[](const Key& key) {
			node_type *n = this->tree.root;
			while (1) {
				if (!n || n->value.first == key)
					break;
				n = (!this->compK(n->value.first, key)) ? n->left : n->right;
			}
			if (!n)
				n = this->tree.add(ft::make_pair(key, mapped_type()));
			return (n->value.second);
		}

		iterator find(const Key& key) {
			node_type *pos = this->tree.root;
			while (1) {
				if (!pos || pos->value.first == key)
					break;
				pos = (!this->compK(pos->value.first, key)) ? pos->left : pos->right;
			}
			return (iterator((pos) ? pos : NULL, this->tree.min(), this->tree.max()));
		}

		const_iterator find(const Key& key) const {
			node_type *pos = this->tree.root;
			while (1) {
				if (!pos || pos->value.first == key)
					break;
				pos = (!this->compK(pos->value.first, key)) ? pos->left : pos->right;
			}
			return (const_iterator((pos) ? (const_node_type *) pos : NULL, (const_node_type *) this->tree.min(), (const_node_type *) this->tree.max()));
		}

		size_type count(const Key& key) const {
			node_type *pos = this->tree.root;
			while (1) {
				if (!pos || pos->value.first == key)
					break;
				pos = (!this->compK(pos->value.first, key)) ? pos->left : pos->right;
			}
			return (pos) ? 1 : 0;
		}


		bool empty() const { return ((this->tree.size) ? false : true); }
		size_type size() const { return (this->tree.size); }
		size_type max_size() const { return (this->tree.nodeAlloc.max_size()); }
		key_compare key_comp() const { return (this->compK); }
		value_compare value_comp() const { return (this->compV); }

		iterator		begin() { return (iterator(this->tree.min(), this->tree.min(), this->tree.max())); }
		const_iterator	begin() const { return (const_iterator(this->tree.min(), this->tree.min(), this->tree.max())); }
		iterator		end() { return (iterator(NULL, this->tree.min(), this->tree.max())); }
		const_iterator	end() const { return (const_iterator(NULL, this->tree.min(), this->tree.max())); }

		reverse_iterator		rbegin() { return (reverse_iterator(this->end())); }
		const_reverse_iterator	rbegin() const { return (reverse_iterator(this->end())); }
		reverse_iterator		rend () { return (reverse_iterator(this->begin())); }
		const_reverse_iterator	rend() const { return (reverse_iterator(this->begin())); }

		void clear() { this->tree.clearTree(); }
		
		void swap(map& other) {
			this->tree.swapTree(other.tree);
			
			key_compare tmpCompK = this->compK;
			this->compK = other.compK;
			other.compK = tmpCompK;

			value_compare tmpCompV = this->compV;
			this->compV = other.compV;
			other.compV = tmpCompV;
		}

		ft::pair<iterator, iterator> equal_range(const Key& key) { return (ft::make_pair(this->lower_bound(key), this->upper_bound(key))); }
		ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const { return (ft::make_pair(this->lower_bound(key), this->upper_bound(key))); }

		iterator lower_bound(const Key& key) {
			node_type *where = this->tree.min();
			while (1) {
				if (!where || key <= where->value.first)
					break;
				where = where->next();
			}
			return ((where) ? iterator(where, this->tree.min(), this->tree.max()) : this->end());
		}

		const_iterator lower_bound(const Key& key) const {
			const_node_type *where = this->tree.min();
			while (1) {
				if (!where || key <= where->value.first)
					break;
				where = where->next();
			}
			return ((where) ? const_iterator(where, this->tree.min(), this->tree.max()) : this->end());
		}		
		
		iterator upper_bound(const Key& key) {
			iterator res = this->lower_bound(key);
			if (res.getNode() && key == res->first)
				res++;
			return (res);
		}
	
		const_iterator upper_bound(const Key& key) const {
			const_iterator res = this->lower_bound(key);
			if (res.getNode() && key == res->first)
				res++;
			return (res);
		}

		friend bool operator==(map const & lhs, map const & rhs) { return (lhs.tree.size == rhs.tree.size && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
		friend bool operator!=(map const & lhs, map const & rhs) { return (!(lhs == rhs)); }
		friend bool operator<(map const & lhs, map const & rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
		friend bool operator>=(map const & lhs, map const & rhs) { return (!(lhs < rhs)); }
		friend bool operator>(map const & lhs, map const & rhs) { return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }
		friend bool operator<=(map const & lhs, map const & rhs) { return (!(lhs > rhs)); }

	private:
		tree_type		tree;
		key_compare		compK;
		value_compare	compV;
};

template< class Key, class T, class Compare, class Allocator>
void swap(ft::map<Key, T, Compare, Allocator>& lhs, ft::map<Key, T, Compare, Allocator>& rhs) { lhs.swap(rhs); }

};