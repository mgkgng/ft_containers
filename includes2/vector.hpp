#include <memory>
#include "unistd.h"
#include "./lib.hpp"
#include "./Iterator.hpp"

namespace ft {

template < typename T, typename Allocator = std::allocator<T> >
class vector {
	
	public:
		////////////////////////////
		// ** type definitions ** //
		////////////////////////////
        typedef T 			value_type;
        typedef Allocator	allocator_type;
        typedef int 		difference_type;
        typedef size_t 		size_type;
        typedef typename	Allocator::reference 		reference;
        typedef typename 	Allocator::const_reference 	const_reference;
        typedef typename 	Allocator::pointer			pointer;
        typedef typename 	Allocator::const_pointer 	const_pointer;

        typedef typename ft::RandomAccessIterator<T> iterator;
        typedef typename ft::RandomAccessIterator<const T> const_iterator;
        typedef typename ft::ReverseIterator<iterator> reverse_iterator;
        typedef typename ft::ReverseIterator<const_iterator> const_reverse_iterator;

		pointer			start;
		allocator_type	alloc;
		size_type		vectorSize;
		size_type		capacity;

		////////////////////////
		// ** contstructor ** //
		////////////////////////

		vector() {
			this->alloc = allocator_type();
			this->start = NULL;
			this->vectorSize = 0;
			this->capacity = 0;
		}

		explicit vector(const Allocator& alloc) { 
			this->alloc = alloc();
			this->start = NULL;
			this->vectorSize = 0;
			this->capacity = 0;
		}

		explicit vector(size_type count, const T& value=T(), const Allocator& alloc = Allocator()) {
			this->alloc = alloc;
			this->start = this->alloc.allocate(count);
			for (size_type i = 0; i < count; i++)
				this->alloc.construct(this->start + i, value);
			this->vectorSize = count;
			this->capacity = count;
		}


		void assign(size_type count, const T& value) { // cppreference (1)
			if (!count)
				return ;
			if (count > this->capacity)
				this->resize(count);
			for (size_type i = 0; i < count; i++) {
				*(this->start + i) = value;
			}
		}

		template<class InputIt>
		void assign(InputIt first, InputIt last, 
			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = false) {
			size_type itSize = 0;
			while (first++ != last)
				itSize++;
			if (itSize > this->capacity)
				this->resize(itSize);
			for (size_type i = 0; i < itSize; i++)
				*(this->start + i) = *first++;
		}

		void resize(size_type n) {
			pointer tmp = this->alloc.allocate(n);
			for (size_type i = 0; i < this->vectorSize && i < n; i++)
				this->alloc.construct(tmp + i, *(start + i));
			this->alloc.deallocate(start, this->vectorSize);
			this->start = tmp;
			this->vectorSize = (this->vectorSize > n) ? this->vectorSize : n;
			this->capacity = n;
		}

		size_type size() const { return (this->vectorSize); }
};
};