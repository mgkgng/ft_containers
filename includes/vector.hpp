#pragma once

#include <memory>
#include "lib.hpp"
#include "Iterator.hpp"

namespace ft {

template < typename T, typename Allocator = std::allocator<T> >
class vector {
	
	public:

		////////////////////////////////////////////////////////
		// ** destructor, operator=, assign, get_allocator ** //
		////////////////////////////////////////////////////////

		~vector() {
			this->clear();
			// _alloc.deallocate(_start, _capacity);
		}

		allocator_type get_allocator() const { return (_alloc); }


		T* data() { return (_start); }
		const T* data() const { return (_start); }

	

};