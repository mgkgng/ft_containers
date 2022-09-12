#pragma once

#include "lib.hpp"
#include "RBTree.hpp"
#include "Iterator.hpp"

namespace ft {

template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class set {
	public:
		typedef Key			key_type;
		typedef Key			value_type;
		typedef size_t		size_type;
		typedef Compare		key_compare;
		typedef Compare		value_compare;
		typedef Allocator	allocator_type;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::const_pointer			const_pointer;

		typedef RBtree<key_type, Compare>	tree_type; // la flemme
		typedef RBnode<key_type>					node;
		typedef std::allocator<node>			 	node_allocator;

		typedef RBiter<node>			iterator;
		typedef RBiter<const node>	const_iterator;
		typedef ft::ReverseIterator<iterator>	reverse_iterator;
		typedef ft::ReverseIterator<const_iterator>	const_reverse_iterator;

		allocator_type	allocator;
		Compare			comp;
		tree_type		tree;

		set() {}
		explicit set(const Compare& comp, const Allocator& alloc = Allocator()) {
			this->comp = comp;
			this->allocator = alloc;
			this->tree = tree_type();
		}

		template<class InputIt>
		set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) { // cppreference(4)
			this->comp = comp;
			this->allocator = alloc;
			this->tree = tree_type();
			while (first != last)
				this->tree.add(*first++);
		}

		set(const set& other) { *this = other; }
		~set() {}		

		set& operator=(const set& other) {
			this->tree = other.tree;
			this->comp = other.comp;
			this->allocator = other.allocator;
			return (*this);
		}

		allocator_type get_allocator() const {
			return (this->_alloc);
		}

		/////////////////////
		// ** Iterators ** //
		/////////////////////		

		iterator begin() { return (this->tree.begin()); }
		const_iterator begin() const { return (this->tree.begin()); }
		iterator end() { return (this->tree.end()); }
		const_iterator end() const { return (this->tree.end()); }

		reverse_iterator rbegin() { return;
		}

		const_reverse_iterator rbegin() const {

		}

		reverse_iterator rend() {
		}

		const_reverse_iterator rend() const {

		}

		////////////////////
		// ** Capacity ** //
		////////////////////

		bool empty() const { return ((this->tree.getSize()) ? false : true); }
		size_type size() const { return (this->tree.getSize()); }
		size_type max_size() const { return (this->tree.max_size()); }

		////////////////////
		// ** Modifier ** //
		////////////////////

		void clear() { tree.clear(); }

		ft::pair<iterator, bool> insert(const value_type& value) {
			node *where = tree.add(value);
			return (where) ? ft::make_pair<iterator, bool>(iterator(where), true) : ft::make_pair<iterator, bool>(iterator(where), false); 			
		}

		iterator insert(iterator hint, const value_type& value) {
			node *pos = tree.search(value, hint.getNode());
			if (pos)
				return (iterator(pos)); //TODO LET'S CHECK IT LATER
			node *where = tree.add(value);
			return (iterator(where));
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last) {
			while (first != last)
				tree.add(*first++);
		}

		void erase(iterator pos) {
			tree.remove(pos.getNode());
			tree.size--;
		}

		void erase(iterator first, iterator last) {
			while (*first != *last) {
				tree.erase(first++.getNode());
				tree.size--;
			}
		}

		size_type erase(const Key& key) {
			node *where = tree.getRoot();
			while (1) {
				if (!where)
					return (0);
				if (where->value == key) {
					tree.remove(where);
					tree.size--;
					return (1);
				}
				where = (!comp(where->value, key)) ? where->left : where->right;
			}
		}

		void swap(set &other) {
			tree.swap(other.tree);
			
			Compare tmp = comp;
			comp = other.comp;
			other.comp = tmp;
			allocator_type tmp2 = allocator;
			allocator = other.allocator;
			other.allocator = tmp2;
		}

		//////////////////
		// ** Lookup ** //
		//////////////////

		size_type count(const Key& key) const {
			node *where = tree.root;
			while (1) {
				if (!where)
					return (0);
				if (where->value == key)
					return (1);
				where = (!comp(where->value, key)) ? where->left : where->right;
			}
		}

		iterator find(const Key& key) {
			node *where = tree.root;
			while (1) {
				if (!where || where->value == key)
					return (iterator(where));
				where = (!comp(where->value, key)) ? where->left : where->right;
			}
		}

		const_iterator find(const Key& key) const {
			node *where = tree.root;
			while (1) {
				if (!where || where->value == key)
					return (const_iterator(where));
				where = (!comp(where->value, key)) ? where->left : where->right;
			}
		}

		ft::pair<iterator, iterator> equal_range(const Key& key) {
			return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
			return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
		}

		iterator lower_bound(const Key& key) {
			node *where = this->tree.root;
			node *res = NULL;
			while (where) {
				if (comp(key, where->value))
					where = where->left;
				else {
					res = where;
					where = where->right;
				}
			}
			return ((res) ? iterator(res) : end());
		}

		const_iterator lower_bound(const Key& key) const {
			node *where = this->tree.root;
			node *res = NULL;
			while (where) {
				if (comp(key, where->value))
					where = where->right;
				else {
					res = where;
					where = where->left;
				}
			}
			return ((res) ? const_iterator(res) : end());
		}		
		
		iterator upper_bound(const Key& key) {
			iterator res = lower_bound(key);
			if (res.getNode() && key == *res)
				res++;
			return (res);
		}
	
		const_iterator upper_bound(const Key& key) const {
			const_iterator res = lower_bound(key);
			if (res.getNode() && key == *res)
				res++;
			return (res);
		}

		/////////////////////
		// ** Observers ** //
		/////////////////////

		key_compare key_comp() const { return (this->comp); }
		value_compare value_comp() const { return (this->comp); }
	};
};