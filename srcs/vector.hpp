#include <cstddef>
#include <iostream>


namespace ft {

template <typename T, class Allocator = allocator<T>>
class vector {

	////////////////////////////
	// ** type definitions ** //
	////////////////////////////

	typedef T value_type;
	typedef Allocator allocator_type;
	typedef size_t	size_type;
	typedef ptrdiff_t difference_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef Allocator::pointer pointer;
	typedef Allocator::const_pointer const_pointer;
	typedef ft::random_access_iterator<value_type> iterator;
	typedef ft::random_access_iterator<const value_type> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const iterator> const_reverse_iterator; 
	
	private:
		T				*V;
		size_type		_currentSize;
		size_type		_capacity;
		allocator_type	_alloc;

	public:
	////////////////////////
	// ** contstructor ** //
	////////////////////////

	vector() {
		
	}

	explicit vector(const Allocator& alloc) {

	}
}