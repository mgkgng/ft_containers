#include "BiDirectionalIterator.hpp"

namespace ft {

	template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set {
		typedef Key			key_type;
		typedef Key			value_type;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;
		typedef Compare		key_compare;
		typedef Compare		value_compare;
		typedef Allocator	allocator_type;
		typedef value_type&	reference;
		typedef const value_type&							const_reference;
		typedef Allocator::pointer							pointer;
		typedef Allocator::const_pointer					const_pointer;
		typedef ft::BiDirectionalIterator<value_type>		iterator;
		typedef ft::BiDirectionalIterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::const_reverse_iterator<const_iterator>	const_reverse_iterator;
	
	private:

		allocator_type _alloc;
	
	public:

		set() { // cppreference(1)
			// Constructs an empty container
		}

		explicit set(const Compare& comp, const Allocator& alloc = Allocator()) { // cppreference(2)
			// Constructs an empty container

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
			// Returns an iterator to the first element of the vector.
			// If the vector is empty, the returned iterator will be equal to end().
			return (_start);
		}

		const_iterator begin() const {
			return (_start);
		}

		iterator end() {
			// Returns an iterator to the element following the last element of the vector.
			// This element acts as a placeholder; attempting to access it results in undefined behavior.
			return (_end);
		}

		const_iterator end() const {
			return (_end);
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
			return (end() - begin());
		}

		size_type max_size() const {

		}

		////////////////////
		// ** Modifier ** //
		////////////////////

		void clear() {

		}

		ft::pair<iterator, bool> insert(const value_type& value) {

		}

		iterator insert(iterator hint, const value_type& value) {

		}

		template<class InputIt>
		void insert(InputIt first, InputIt last) {

		}

		void erase(iterator pos) {

		}

		void erase(iterator first, iterator last) {

		}

		size_type erase(const Key& key) {

		}

		void swap(set &other) {

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

		value_comapre value_comp() const {

		}
	};
};