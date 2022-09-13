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

        typedef typename ft::RandomAccessIterator<pointer> iterator;
        typedef typename ft::RandomAccessIterator<const_pointer> const_iterator;
        typedef typename ft::ReverseIterator<iterator> reverse_iterator;
        typedef typename ft::ReverseIterator<const_iterator> const_reverse_iterator;

		pointer			start;
		allocator_type	alloc;
		size_type		vectorSize;
		size_type		vectorCapacity;

		////////////////////////
		// ** contstructor ** //
		////////////////////////

		vector() {
			this->alloc = allocator_type();
			this->start = NULL;
			this->vectorSize = 0;
			this->vectorCapacity = 0;
		}

		explicit vector(const Allocator& alloc) { 
			this->alloc = alloc();
			this->start = NULL;
			this->vectorSize = 0;
			this->vectorCapacity = 0;
		}

		explicit vector(size_type count, const T& value=T(), const Allocator& alloc = Allocator()) {
			this->alloc = alloc;
			this->start = this->alloc.allocate(count);
			for (size_type i = 0; i < count; i++)
				this->alloc.construct(this->start + i, value);
			this->vectorSize = count;
			this->vectorCapacity = count;
		}

		template<class InputIt>
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(),
			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = false) { // cppreference (5)
			this->alloc = alloc;
			size_type itSize = 0;
			for (InputIt it = first; it != last; it++)
				itSize++;
			this->start = this->alloc.allocate(itSize);
			for (size_type i = 0; i < itSize; i++)
				this->alloc.construct(start + i, *(first + i));
			this->vectorSize = itSize;
			this->vectorCapacity = itSize;
		}

		vector(vector const & other, const Allocator& alloc = Allocator()) {
			this->alloc = alloc;
			this->start = this->alloc.allocate(other.vectorSize);
			for (size_type i = 0; i < other.vectorSize; i++)
				this->alloc.construct(start + i, other[i]);
			this->vectorSize = other.vectorSize;
			this->vectorCapacity = other.vectorCapacity;
		}

		vector& operator=(vector const & other) {
			this->alloc = other.alloc;
			this->start = other.start;
			this->vectorSize = other.vectorSize;
			this->vectorCapacity = other.vectorCapacity;
			return (*this);
		}
		void assign(size_type count, const T& value) { // cppreference (1)
			this->resize(count);
			for (size_type i = 0; i < count; i++)
				*(this->start + i) = value;
		}

		template<class InputIt>
		void assign(InputIt first, InputIt last, 
			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = false) {
			size_type itSize = 0;
			for (InputIt it = first; it != last; it++)
				itSize++;
			pointer tmp = this->alloc.allocate(itSize);
			for (size_type i = 0; i < itSize; i++)
				this->alloc.construct(tmp + i, *first++);
			this->alloc.deallocate(this->start, this->vectorSize);
			this->start = tmp;
			this->vectorSize = itSize;
			this->vectorCapacity = itSize;
		}

		reference at(size_type pos) {
			if (pos > this->vectorCapacity)
				throw std::out_of_range("exception!");
			return (this->start[pos]);
		}
		const_reference at( size_type pos ) const {
			if (pos > this->vectorCapacity)
				throw std::out_of_range("exception!");
			return (this->start[pos]);
		}

		void clear() {
			for (size_type i = 0; i < this->vectorSize; i++)
				this->alloc.destroy(this->start + i);
			this->vectorSize = 0;
		}

		void push_back(const T& value) {
			if (this->vectorSize == this->vectorCapacity)
				resize(this->vectorCapacity + 1);
			this->start[this->vectorSize++] = value;
		}

		void pop_back() {
			this->start[this->vectorSize--] = T();
		}

		iterator insert(iterator pos, const T& value) {
			if (this->vectorSize == this->vectorCapacity)
				resize(this->vectorSize + 1);
			for (iterator it = this->end(); it != pos + 1; it--)
				*it = *(it - 1);
			*(pos + 1) = value;
			this->vectorSize++;
			return (pos + 1);
		}

		reference front() { return (*(this->start)); }
		const_reference front() const { return (*(this->start)); }
		reference back() { return (this->start[this->vectorSize - 1]); }
		const_reference back() const { return (this->start[this->vectorSize - 1]); }

		void resize(size_type n) {
			pointer tmp = this->alloc.allocate(n);
			for (size_type i = 0; i < this->vectorSize && i < n; i++)
				this->alloc.construct(tmp + i, *(start + i));
			this->alloc.deallocate(start, this->vectorSize);
			this->start = tmp;
			this->vectorCapacity = n;
		}

		size_type size() const { return (this->vectorSize); }
		size_type capacity() const { return (this->vectorCapacity); }
		size_type max_size() const { return (this->alloc.max_size()); }

		iterator begin() { return (iterator(this->start)); }
		const_iterator begin() const { return (const_iterator(this->start)); }
		iterator end() { return (iterator(this->start + this->vectorSize)); }
		const_iterator end() const { return (const_iterator(this->start + this->vectorSize));}

		reference operator[](size_type pos) { return (*(this->start + pos)); }
		const_reference operator[]( size_type pos ) const { return (*(this->start + pos)); }

};
};