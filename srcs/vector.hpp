#pragma once

#include "lib.hpp"

namespace ft {

template < typename T, typename Allocator = std::allocator<T> >
class vector {
	
	private:
		T				*V;
		allocator_type	_alloc; // allocator to use for all memory allocations of this container
		pointer			_start; // the starting address of the container
		pointer			_end; // the ending address of the container
		size_type		_count; // the size of the container
		size_type		_capacity; // the capacity of the container


	public:

		////////////////////////////
		// ** type definitions ** //
		////////////////////////////

		typedef T 												value_type;
		typedef Allocator										allocator_type;
		typedef size_t											size_type;
		typedef ptrdiff_t										difference_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef Allocator::pointer 								pointer;
		typedef Allocator::const_pointer 						const_pointer;
		typedef ft::random_access_iterator<value_type> 			iterator;
		typedef ft::random_access_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator> 					reverse_iterator;
		typedef ft::reverse_iterator<const iterator> 			const_reverse_iterator; 

		////////////////////////
		// ** contstructor ** //
		////////////////////////

		vector() { // cppreference (1)
			// Default constructor. Constructs an empty container with a default-constructed allocator.
			_alloc = allocator_type();
			_start = NULL;
			_end = NULL;
			_count = 0;
			_capacity = 0;
		}


		explicit vector(const Allocator& alloc) { // cppreference (2)
			// Constructs an empty container with the given allocator alloc.
			_alloc = alloc;
			_start = NULL;
			_end = NULL;
			_count = 0;
			_capacity = 0;
		}

		explicit vector(size_type count, const T& value=T(), const Allocator& alloc = Allocator()) { // cppreference (3)
			// Constructs the container with count copies of elements with value value.
			_alloc = alloc;
			_start = _alloc.allocate(count); // allocator allocates automatically n * sizeof(T) bytes of uninitialized storage
			for (int i = 0; i < count; i++)
				_alloc.construct(_start + i, value);
			_end = _start + count;
			_count = count;
			_capacity = count;
		}

		template<class InputIt>
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()) { // cppreference (5)
			// Constructs the container with the contents of the range [first, last).
			_alloc = alloc;
			_count = last - first;
			_start = _alloc.allocate(_count);
			_end = _start;
			_capacity = _count;
		}

		vector(const vector& other) { // cppreference(6)
			// Copy constructor. Constructs the container with the copy of the contents of other.
			*this = other;
		}

		////////////////////////////////////////////////////////
		// ** destructor, operator=, assign, get_allocator ** //
		////////////////////////////////////////////////////////

		~vector() {
			this->clear();
			this->alloc.deallocate(first, SIZE);
		}

		vector& operator=(const vector& other) {
			// Copy assignment operator. Replaces the contents with a copy of the contents of other.
			this->...;
		}

		void assign(size_type count, const T& value) { // cppreference (1)
			// Replaces the contents with count copies of value value
			this->alloc.deallocate(this->start, this->)
		}

		template<class InputIt>
		void assign(InputIt first, InputIt last) { // cppreference (2)
			// Replaces the contents with copies of those in the range [first, last). The behavior is undefined if either argumnet is an iterator into *this.
		}

		allocator_type get_allocator const {
			return (this->alloc);
		}

		//////////////////////////
		// ** Element access ** //
		//////////////////////////

		reference at(size_type pos) {
			// Returns a reference to the element at specified location pos, with bounds checking.
			// If pos is not within the range of the container, an exception of type std::out_of_range is thrown.
		
			if (pos >= this->size)
				throw std::out_of_range;
			return (V[pos]);
		}

		const_reference at(size_type pos) {

		}

		reference operator[](size_type pos) {
			// Returns a reference to the element at specified location pos. No bounds checking is performed.
		}

		const_reference operator[](size_type pos) const {

		}

		reference front() {
			// Returns a reference to the first element in the container.
			// Calling front on an empty container is undefined.
			return (*V);
		}

		const_reference front() const {
			return (*V);
		}

		reference back() {
			// Returns a reference to the last element in the container.
			// Calling back on an empty container is undefined.
			if (!_size)
				return ;
			return (V[_size - 1]);
		}

		const_reference back() const {
			if (!_size)
				return ;
			return (V[_size - 1]);
		}

		T* data() {
			// Returns a pointer to the underlying array serving as element storage. 
			
		}

		const T* data() const {

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
			// Checks if the container has no elements, i.e. whether begin() == end().
			if (this->begin() == this->end())
				return (true);
			return (false);
		}

		size_type size() const {
			// Returns the number of elements in container, i.e. std::distance(begin(), end()).
			std::dista
		}

		size_type max_size() const {
			// Returns the maximum number of elements the container is able to hold due to system or library implementation limitations

		}

		void reserve(size_type new_cap) {

		}

		size_type capacity() const {
			// Returns the number of elements that the container has currently allocated space for.
		}

		/////////////////////
		// ** Modifiers ** //
		/////////////////////

		void clear() {
			for (int i = 0; i < _size; i++)
				_alloc.destroy(&V[i]);
			_size = 0;
		}

		// <insert>
		// Causes reallocation if the new size() is greater than the old capacity(). 
		// If the new size() is greater than capacity(), all iterators and references are invalidated.
		// Otherwise, only the iterators and referecens before the insertion point remain valid.
		// The past-the-end iterator is also invalidated.
		iterator insert(iterator pos, const T& value) { // cppreference(1)
			// inserts value before pos
		}

		void insert(iterator pos, size_type count, const T& value) { // cppreference(3)
			// inserts count copies of the value before pos
		}

		template<class InputIt>
		void insert(iterator pos, InputIt first, InputIt last) { // cppreference(4)
			// inserts elements from range [first, last) before pos
		}

		// <erase>
		// Invalidates iterators and referecens at or after the point of the erase, including the end() iterator.
		// The iterator pos mmust be valid and dereferenceable. Thus the end() iterator cannot be used as a value for pos.
		// The iterator first does not need to be dereferenceable if first==last: erasing an empty range is a no-op.
		iterator erase(iterator pos) {
			// Removes the element at pos
		}

		iterator erase(iterator first, iterator last) {
			// Removes the elements in the range [first, last).
		}
		
		void push_back(const T& value) {
			// Appends the given element value to the end of the container. The new element is initialized as a copy of value.
			// If the new size() is greater than capacity() then all iterators and referecnes are invalidated.
			if (_size == _capacity) {
				this->resize(_capacity * 2);
			}
			
			V[_size++] = value;
			this->_end = V + _size;
		}

		void pop_back() {

		}

		void resize(size_type count, T value = T()) {
			pointer tmp = this->_alloc.allocate(count);
			memcpy(tmp, this->_start, this->_count * sizeof(T));
			for (pointer p = tmp + this->_count; p != tmp + count; p++)
				*p = value;

			for (pointer p = this->_start; p != this->_end; p++)
				p.destroy();
			this->_start.deallocate();

			this->_start = tmp;
			this->_capacity = count;
		}

		void swap(vector & other)

	};

		template<class T, class Alloc>
		bool operator==(const ft::vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {

		}
		
		template<class T, class Alloc>
		bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {

		}

		template<class T, class Alloc>
		bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {

		}

		template<class T, class Alloc>
		bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {

		}

		template<class T, class Alloc>
		bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {

		}

		template<class T, class Alloc>
		bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {

		}

		template<class T, class Alloc>
		void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) {

		}
		
};