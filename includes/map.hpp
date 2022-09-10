#pragma once

#include "RBTree.hpp"
#include "ReverseIterator.hpp"


//TODO should use friend class to get access to the data of tree 
namespace ft {

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
>
class map {

	public:
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef ft::pair<const Key, T> 	value_type;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef Compare					key_compare;
		typedef Allocator				allocator_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef typename Allocator::pointer		pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		typedef RBtree<key_type, value_type, Compare>	tree_type;
		typedef RBnode<value_type>						node;
		typedef std::allocator<node>			 		node_allocator;

		typedef RBiter<node>			iterator;
		typedef RBiter<const node>	const_iterator;
		typedef ft::ReverseIterator<iterator>	reverse_iterator;
		typedef ft::ReverseIterator<const_iterator>	const_reverse_iterator;


		class value_compare {

			protected:
				Compare comp;

			public:
				typedef bool		result_type;
				typedef	value_type	first_argument_type;
				typedef value_type	second_argument_type;

				value_compare() {}
				value_compare(Compare c) {
					comp = c;
				}

				bool operator()(const value_type& lhs, const value_type& rhs) const {
					return (comp(lhs.first, rhs.first));
				}
		};

		map() {
			compK = Compare();
			compV = value_compare(compK);
			allocator = Allocator();
			tree = tree_type();
		}
		
		explicit map(const Compare& comp, const Allocator& alloc = Allocator()) { // cppreference(2)
			compK = comp;
			compV = value_compare(compK);
			allocator = alloc;
			tree = tree_type();
		}

		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) { // cppreference(4)
			// Constructs the container with the contents of the range [first, last).
			// If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
			compK = comp;
			compV = value_compare(compK);
			allocator = alloc;
			tree = tree_type();
			while (first != last)
				this->tree.add(*first++);
		}

		map(const map& other) { // cppreference(6)
			// Copy constructor.
			*this = other;
		}

		~map() {}

		map& operator=(const map& other) {
			tree = other.tree;
			compK = other.compK;
			allocator = other.allocator;
			compV = value_compare(other.compV);
			return (*this);
		}

		allocator_type get_allocator() const {
			return (allocator);
		}

		//////////////////////////
		// ** Element access ** //
		//////////////////////////

		T& at(const Key& key) {
			return ((this->find(key))->second);
		}

		const T& at(const Key& key) const {
			return ((this->find(key))->second);
		}

		T& operator[](const Key& key) {
			iterator it = this->find(key); // DES FOIS CA MARCHE PAS
			if (it != this->end())
				return (it->second);
			node* newNode = tree.add(ft::make_pair(key, T()));
			return (newNode->value.second);

		}

		/////////////////////
		// ** Iterators ** //
		/////////////////////

		iterator begin() {
			// Returns an iterator to the first element of the vector.
			// If the vector is empty, the returned iterator will be equal to end().
			return (this->tree.begin());
		}

		const_iterator begin() const {
			return (this->tree.begin());
		}

		iterator end() {
			// Returns an iterator to the element following the last element of the vector.
			// This element acts as a placeholder; attempting to access it results in undefined behavior.
			return (this->tree.end());
		}

		const_iterator end() const {
			return (this->tree.end());
		}

		reverse_iterator rbegin() {
			// Returns a reverse iterator to the first element of the reversed vector.
			// It corresponds to the last element of the non-reversed vector.
			// If the vector is empty, the returned iterator is equal to rend().
			node *r = tree._root;
	
			while (r && r->_right)
				r = r->_left;
			return (reverse_iterator(r));
		}

		const_reverse_iterator rbegin() const {

		}

		reverse_iterator rend() {
			// Returns a reverse iterator to the element following the last element of the reversed vector.
			// It corresponds to the element preceding the first element of the non-reversed vector. 
			// This element acts as a placeholder, attempting to access it results in undefined behavior.
			return (NULL);
		}

		const_reverse_iterator rend() const {
			return (NULL);
		}

		////////////////////
		// ** Capacity ** //
		////////////////////

		bool empty() const {
			return ((tree.getSize()) ? false : true);
		}

		size_type size() const {
			return (tree.getSize());
		}

		size_type max_size() const {
			return (tree.max_size());
		}

		////////////////////
		// ** Modifier ** //
		////////////////////

		void clear() {
			tree.clear();
		}

		ft::pair<iterator, bool> insert(const value_type& value) {
			node *pos = tree.search(value.first, tree.getRoot());
			if (pos)
				return (ft::make_pair<iterator, bool>(iterator(pos), false));
			node *where = tree.add(value);
			return (ft::make_pair<iterator, bool>(iterator(where), true));
		}

		iterator insert(iterator hint, const value_type& value) {
			node *pos = tree.search(value.first, hint.getPtr());
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
			std::cout << "bonjour" << std::endl;
			tree.remove(pos.getPtr());
			std::cout << "au revoir" << std::endl;
		}

		void erase(iterator first, iterator last) {
			while (first != last)
				tree.remove(first++->first);
		}

		size_type erase(const Key& key) {
			tree.remove(key);
		}

		void swap(map &other) {
			tree.swap(other);
			
			key_compare tmp = compK;
			compK = other.compK;
			other.compK = tmp;
			allocator_type tmp2 = allocator;
			allocator = other.allocator;
			other.allocator = tmp2;
			value_compare tmp3 = compV;
			compV = other.compV;
			other.compV = tmp3;
		}

		//////////////////
		// ** Lookup ** //
		//////////////////

		size_type count(const Key& key) const {
			return (tree.search(key, tree.getRoot())) ? 1 : 0;
		}

		iterator find(const Key& key) {
			node *where = tree.search(key, tree.getRoot());
			return (!where) ? this->end() : iterator(where);
		}

		const_iterator find(const Key& key) const {
			node *where = tree.search(key, tree.getRoot());
			return (!where) ? this->end() : const_iterator(where);
		}

		ft::pair<iterator, iterator> equal_range(const Key& key) {
			iterator first = 0, second = 0, begin = this->begin();
			while (compK(begin->key, key)) // un truc comme ca
				begin++;
			first = begin;
			while (compK(key, begin->key))
				begin++;
			second = begin; // un truc comme ca
			return (ft::make_pair<iterator, iterator>(first, second)); 
		}

		ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
			iterator first = 0, second = 0, begin = this->begin();
			while (compK(begin->key, key)) // un truc comme ca
				begin++;
			first = begin;
			while (compK(key, begin->key))
				begin++;
			second = begin; // un truc comme ca
			return (ft::make_pair<iterator, iterator>(first, second)); 
		}

		iterator lower_bound(const Key& key) { // un truc comme ca
			iterator res = 0, begin = this->begin();
			while (compK(begin->key, key))
				begin++;
			return (begin);
		}

		const_iterator lower_bound(const Key& key) const { // un truc comme ca
			iterator begin = this->begin();
			while (compK(begin->key, key))
				begin++;
			return (begin);
		}

		iterator upper_bound(const Key& key) { // un truc comme ca
			iterator begin = this->begin();
			while (compK(key, begin->key))
				begin++;
			return (begin);
		}

		const_iterator upper_bound(const Key& key) const { // un truc commme ca
			iterator begin = this->begin();
			while (compK(key, begin->key))
				begin++;
			return (begin);
		}		

		/////////////////////
		// ** Observers ** //
		/////////////////////

		key_compare key_comp() const {
			return (compK);
		}

		value_compare value_comp() const {
			return (compV);
		}

		friend bool operator==(const map& lhs, const map& rhs) {
			if (lhs.tree._size != rhs.tree._size)
				return (false);
			iterator lbegin = lhs.begin();
			iterator rbegin = rhs.begin();
			while (lbegin)
				if ((lbegin++)->key != (rbegin++)->key || (lbegin++)->value != (rbegin++)->value)
					return (false);
			return (true);
		}
		
		friend bool operator!=(const map& lhs, const map& rhs) {
			return (!(lhs == rhs));
		}

		friend bool operator<(const map& lhs, const map& rhs) {
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

		friend bool operator<=(const map& lhs, const map& rhs) {
			return (!(lhs > rhs));
		}

		friend bool operator>(const map& lhs, const map& rhs) {
			return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));

		}

		friend bool operator>=(const map& lhs, const map& rhs) {
			return (!(lhs < rhs));
		}

		void swap(map& lhs, map& rhs) {
			lhs.swap(rhs);
		}

		tree_type &getTree() { return (this->tree); }

	private:
		tree_type		tree;
		key_compare		compK;
		value_compare	compV;
		allocator_type	allocator;

};
};