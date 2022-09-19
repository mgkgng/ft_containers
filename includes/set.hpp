#pragma once

#include "lib.hpp"
#include "tree.hpp"
#include "Iterator.hpp"
#include "pair.hpp"

namespace ft {

template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
class set {

	public:
		typedef Key			key_type;
		typedef Key			value_type;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef Compare		key_compare;
		typedef Compare		value_compare;

		typedef ft::tree<value_type, value_compare> tree_type;
		typedef ft::treeNode<value_type>			node_type;
		typedef ft::treeNode<const value_type> 		const_node_type;

		typedef ft::IterTree<const value_type>		iterator;
		typedef ft::IterTree<const value_type>	const_iterator;
		typedef ft::ReverseIter<iterator> 		reverse_iterator;
		typedef ft::ReverseIter<const_iterator> const_reverse_iterator;

		typedef std::allocator<node_type> 					allocator_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
	
		set() {}

		explicit set(const Compare& comp, const Allocator& alloc = Allocator()) {
			(void) alloc;
			this->comp = comp;
			this->tree = tree_type();
		}

		template<class InputIt>
		set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) { // cppreference(4)
			(void) alloc;
			this->comp = comp;
			this->tree = tree_type();
			while (first != last)
				this->insert(*first++);
		}

		set(const set& other) { *this = other; }

		~set() { this->tree.clearTree(); }		

		set& operator=(const set& other) {
			this->tree.clearTree();
			if (*this == other)
				return (*this);
			this->tree = other.tree;
			this->comp = other.comp;
			return (*this);
		}

		allocator_type get_allocator() const { return (this->tree.nodeAlloc); }

		iterator		begin() { return (iterator((const_node_type *) this->tree.min(), (const_node_type *) this->tree.min(), (const_node_type *) this->tree.max())); }
		const_iterator	begin() const { return (const_iterator(this->tree.min(), this->tree.min(), this->tree.max())); }
		iterator		end() { return (iterator(NULL, (const_node_type *) this->tree.min(), (const_node_type *) this->tree.max())); }
		const_iterator	end() const { return (const_iterator(NULL, this->tree.min(), this->tree.max())); }

		reverse_iterator		rbegin() { return (reverse_iterator(this->end())); }
		const_reverse_iterator	rbegin() const { return (reverse_iterator(this->end())); }
		reverse_iterator		rend () { return (reverse_iterator(this->begin())); }
		const_reverse_iterator	rend() const { return (reverse_iterator(this->begin())); }

		bool empty() const { return ((this->tree.size) ? false : true); }
		size_type size() const { return (this->tree.size); }
		size_type max_size() const { return (this->tree.nodeAlloc.max_size()); }

		void clear() { this->tree.clearTree(); }

		ft::pair<iterator, bool> insert(const value_type& value) {
			node_type *pos = this->tree.root;
			while (1) {
				if (!pos || pos->value == value)
					break;
				pos = (!this->comp(pos->value, value)) ? pos->left : pos->right;
			}
			if (pos)
				return (ft::make_pair<iterator, bool>(iterator((const_node_type *) pos, (const_node_type *) this->tree.min(), (const_node_type *) this->tree.max()), false));
			node_type *where = tree.add(value);
			return (ft::make_pair<iterator, bool>(iterator((const_node_type *) where, (const_node_type *)this->tree.min(), (const_node_type *) this->tree.max()), true));
		}

		iterator insert(iterator hint, const value_type& value) {
			node_type *pos = (node_type *) hint.getNode();
			while (1) {
				if (!pos || pos->value == value)
					break;
				pos = (!this->comp(pos->value, value)) ? pos->left : pos->right;
			}
			if (pos)
				return (iterator((const_node_type *) pos, (const_node_type *) this->tree.min(), (const_node_type *) this->tree.max()));
			node_type *where = this->tree.add(value);
			return (iterator((const_node_type *) where, (const_node_type *) this->tree.min(), (const_node_type *) this->tree.max()));
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last) {
			while (first != last)
				this->insert(*first++);
		}

		iterator erase(iterator pos) {
			this->tree.erase((node_type *) pos.getNode());
			return (iterator());
		}

		iterator erase(iterator first, iterator last) {
			while (first != last)
				this->tree.erase((node_type *) (first++).getNode());
			return (iterator());
		}

		size_type erase(const Key& key) {
			node_type *n = this->tree.root;
			while (1) {
				if (!n || n->value == key)
					break;
				n = (!this->comp(n->value, key)) ? n->left : n->right;
			}
			if (n)
				this->tree.erase(n);
			return ((!n) ? 0 : 1);
		}

		void swap(set& other) {
			this->tree.swapTree(other.tree);
			
			key_compare tmpComp = this->comp;
			this->comp = other.comp;
			other.comp = tmpComp;
		}

		size_type count(const Key& key) const {
			node_type *pos = this->tree.root;
			while (1) {
				if (!pos || pos->value == key)
					break;
				pos = (!this->comp(pos->value, key)) ? pos->left : pos->right;
			}
			return (pos) ? 1 : 0;
		}

		iterator find(const Key& key) {
			node_type *pos = this->tree.root;
			while (1) {
				if (!pos || pos->value == key)
					break;
				pos = (!this->comp(pos->value, key)) ? pos->left : pos->right;
			}
			return (iterator((pos) ? (const_node_type *) pos : NULL, (const_node_type *) this->tree.min(), (const_node_type *) this->tree.max()));
		}

		const_iterator find(const Key& key) const {
			node_type *pos = this->tree.root;
			while (1) {
				if (!pos || pos->value == key)
					break;
				pos = (!this->comp(pos->value, key)) ? pos->left : pos->right;
			}
			return (const_iterator((pos) ? (const_node_type *) pos : NULL, (const_node_type *) this->tree.min(), (const_node_type *) this->tree.max()));
		}

		ft::pair<iterator, iterator> equal_range(const Key& key) { return (ft::make_pair(this->lower_bound(key), this->upper_bound(key))); }
		ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const { return (ft::make_pair(this->lower_bound(key), this->upper_bound(key))); }

		iterator lower_bound(const Key& key) {
			node_type *where = this->tree.min();
			while (1) {
				if (!where || key <= where->value)
					break;
				where = where->next();
			}
			return ((where) ? iterator((const_node_type *) where, (const_node_type *) this->tree.min(), (const_node_type *) this->tree.max()) : this->end());
		}

		const_iterator lower_bound(const Key& key) const {
			const_node_type *where = this->tree.min();
			while (1) {
				if (!where || key <= where->value)
					break;
				where = where->next();
			}
			return ((where) ? const_iterator(where, this->tree.min(), this->tree.max()) : this->end());
		}		
		
		iterator upper_bound(const Key& key) {
			iterator res = this->lower_bound(key);
			if (res.getNode() && key == *res)
				res++;
			return (res);
		}
	
		const_iterator upper_bound(const Key& key) const {
			const_iterator res = this->lower_bound(key);
			if (res.getNode() && key == *res)
				res++;
			return (res);
		}

		key_compare key_comp() const { return (this->comp); }
		value_compare value_comp() const { return (this->comp); }

		friend bool operator==(set const & lhs, set const & rhs) { return (lhs.tree.size == rhs.tree.size && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
		friend bool operator!=(set const & lhs, set const & rhs) { return (!(lhs == rhs)); }
		friend bool operator<(set const & lhs, set const & rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
		friend bool operator>=(set const & lhs, set const & rhs) { return (!(lhs < rhs)); }
		friend bool operator>(set const & lhs, set const & rhs) { return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }
		friend bool operator<=(set const & lhs, set const & rhs) { return (!(lhs > rhs)); }
	
	private:
		tree_type		tree;
		key_compare		comp;
};

};