#pragma once

#include "lib.hpp"
#include "RBTree.hpp"
#include "ReverseIterator.hpp"

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
		explicit set(const Compare& comp, const Allocator& alloc = Allocator()) { // cppreference(2)
			// Constructs an empty container
			this->comp = comp;
			this->allocator = alloc;
			this->tree = tree_type();
		}

		template<class InputIt>
		set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) { // cppreference(4)
			// Constructs the container with the contents of the range [first, last).
			// If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
		}

		set(const set& other) { // cppreference(6)
			// Copy constructor.
		}

		~set() {

		}		

		set& operator=(const set& other) {

		}

		allocator_type get_allocator() const {
			return (this->_alloc);
		}

		/////////////////////
		// ** Iterators ** //
		/////////////////////		

		iterator begin() {
			return (this->tree.begin());
		}

		const_iterator begin() const {
			return (this->tree.begin());
		}

		iterator end() {
			return (this->tree.end());
		}

		const_iterator end() const {
			return (this->tree.end());
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
			return ((begin() == end()) ? true : false);
		}

		size_type size() const {
			return (this->tree.getSize());
		}

		size_type max_size() const {
			return (this->tree.max_size());
		}

		////////////////////
		// ** Modifier ** //
		////////////////////

		void clear() {

		}

		ft::pair<iterator, bool> insert(const value_type& value) {
			node *pos = tree.search(value, tree.root);
			if (pos)
				return (ft::make_pair<iterator, bool>(iterator(pos), false));
			node *where = tree.add(value);
			return (ft::make_pair<iterator, bool>(iterator(where), true));
		}

		iterator insert(iterator hint, const value_type& value) {
			node *pos = tree.search(value, hint.getPtr());
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
			tree.remove(pos.getPtr());
			tree.size--;
		}

		void erase(iterator first, iterator last) {
			while (*first != *last) {
				tree.erase(first++->first);
				tree.size--;
			}
		}

		size_type erase(const Key& key) {
			bool res = tree.erase(key);
			if (res)
				tree.size--;
			return (res);
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

		}

		iterator find(const Key& key) {

		}

		const_iterator find(const Key& key) const {

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
};