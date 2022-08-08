#pragma once

#include "RBTree.hpp"

namespace ft {

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
>
class map {

	private:
		tree_type		_tree;
		key_compare		_comp;
		allocator_type	_alloc;

	public:
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef std::pair<const Key, T> value_type;
		typedef RBtree<value_type, Compare>	tree_type;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef Compare					key_compare;
		typedef Allocator				allocator_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef Allocator::pointer		pointer;
		typedef Allocator::const_pointer	const_pointer;
		typedef ft::RBiter<value_type>			iterator;
		typedef ft::RBiter<const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>	reverse_iterator;
		typedef ft::const_reverse_iterator<const_iterator>	const_reverse_iterator;

		class value_compare {
			typedef bool		result_type;
			typedef	value_type	first_argument_type;
			typedef value_type	second_argument_type;

			protected:
				Compare comp;
				value_compare(Compare c) {
					comp = c;
				}

			public:
				bool operator()(const value_type& lhs, const value_type& rhs) const {
					return (comp(lhs.first, rhs.first));
				}
		};

		explicit map(const Compare& comp, const Allocator& alloc = Allocator()) { // cppreference(2)
			_tree = tree_type(comp);
			_comp = comp;
			_alloc = alloc;
		}

		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) { // cppreference(4)
			// Constructs the container with the contents of the range [first, last).
			// If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
			map(comp, alloc);
			this->insert(first, last);
		}

		map(const map& other) { // cppreference(6)
			// Copy constructor.
			*this = other;
		}

		~map() {
			this->clear();
		}

		map& operator=(const map& other) {
			_tree = other._tree;
			_comp = other._comp;
			_alloc = other._alloc;
			return (*this);
		}

		allocator_type get_allocator() const {
			return (_alloc);
		}

		//////////////////////////
		// ** Element access ** //
		//////////////////////////

		T& at(const Key& key) {
			return ((this->find(key))->value);
		}

		const T& at(const Key& key) const {
			return ((this->find(key))->value);
		}

		T& operator[](const Key& key) {
			return ((this->find(key))->value);
		}

		/////////////////////
		// ** Iterators ** //
		/////////////////////

		iterator begin() {
			// Returns an iterator to the first element of the vector.
			// If the vector is empty, the returned iterator will be equal to end().

			node_pointer l = _root;
	
			while (l && l->_left)
				l = l->_left;
			return iterator(l);
		}

		const_iterator begin() const {
			return (begin());
		}

		iterator end() {
			// Returns an iterator to the element following the last element of the vector.
			// This element acts as a placeholder; attempting to access it results in undefined behavior.
			return (0);
		}

		const_iterator end() const {
			return (0);
		}

		reverse_iterator rbegin() {
			// Returns a reverse iterator to the first element of the reversed vector.
			// It corresponds to the last element of the non-reversed vector.
			// If the vector is empty, the returned iterator is equal to rend().
		}

		const_reverse_iterator rbegin() const {

		}

		reverse_iterator rend() {
			// Returns a reverse iterator to the element following the last element of the reversed vector.
			// It corresponds to the element preceding the first element of the non-reversed vector. 
			// This element acts as a placeholder, attempting to access it results in undefined behavior.
		}

		const_reverse_iterator rend() const {

		}

		////////////////////
		// ** Capacity ** //
		////////////////////

		bool empty() const {
			return (_tree._size) ? false : true;
		}

		size_type size() const {
			return (_tree._size);
		}

		size_type max_size() const {
			return (_tree._nodeAlloc.max_size());
		}

		////////////////////
		// ** Modifier ** //
		////////////////////

		void clear() {
			_tree.eraseAll();
		}

		ft::pair<iterator, bool> insert(const value_type& value) {

		}

		iterator insert(iterator hint, const value_type& value) {

		}

		template<class InputIt>
		void insert(InputIt first, InputIt last) {
			while (first != last)
				_tree.add(*first++);
		}

		void erase(iterator pos) {
			_tree.remove(pos->first);
		}

		void erase(iterator first, iterator last) {
			while (first != last)
				_tree.remove(first->first);
		}

		size_type erase(const Key& key) {
			_tree.remove(key);
		}

		void swap(map &other) {
			_tree.swap(other);
		}

		//////////////////
		// ** Lookup ** //
		//////////////////

		size_type count(const Key& key) const {
			return (_tree.searchKey(_tree._root, key)) ? 1 : 0;
		}

		iterator find(const Key& key) {
			iterator res = _tree.searchKey(_tree._root, key);
			return (res) ? res : this->end();
		}

		const_iterator find(const Key& key) const {
			iterator res = _tree.searchKey(_tree._root, key);
			return (res) ? res : this->end();
		}

		ft::pair<iterator, iterator> equal_range(const Key& key) {

		}

		ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {

		}

		iterator lower_bound(const Key& key) {

		}

		const_iterator lower_bound(const Key& key) const {

		}

		iterator upper_bound(const Key& key) {

		}

		const_iterator upper_bound(const Key& key) const {

		}		

		/////////////////////
		// ** Observers ** //
		/////////////////////

		key_compare key_comp() const {

		}

		value_compare value_comp() const {

		}
};

	template<class T, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {

	}
	
	template<class T, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {

	}

	template<class T, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {

	}

	template<class T, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {

	}

	template<class T, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {

	}

	template<class T, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {

	}

	template<class T, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs) {

	}

};