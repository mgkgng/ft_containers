#include <memory>
#include "unistd.h"
#include "./lib.hpp"
#include "./Iterator.hpp"

namespace ft {

template < typename T, typename Allocator = std::allocator<T> >
class vector {
	
	public:
        typedef T 			value_type;
        typedef Allocator	allocator_type;
        typedef int 		difference_type;
        typedef size_t 		size_type;
        typedef typename	Allocator::reference 		reference;
        typedef typename 	Allocator::const_reference 	const_reference;
        typedef typename 	Allocator::pointer			pointer;
        typedef typename 	Allocator::const_pointer 	const_pointer;

        typedef typename ft::IterVector<pointer> iterator;
        typedef typename ft::IterVector<const_pointer> const_iterator;
        typedef typename ft::ReverseIter<iterator> reverse_iterator;
        typedef typename ft::ReverseIter<const_iterator> const_reverse_iterator;

		pointer			start;
		allocator_type	alloc;
		size_type		vectorSize;
		size_type		vectorCapacity;

		vector() {
			this->alloc = allocator_type();
			this->start = this->alloc.allocate(1);
			this->vectorSize = 0;
			this->vectorCapacity = 1;
		}

		explicit vector(const Allocator& alloc) { 
			this->alloc = alloc();
			this->start = this->alloc.allocate(1);
			this->vectorSize = 0;
			this->vectorCapacity = 1;
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
			size_type itSize = this->getDistance(first, last);
			this->start = this->alloc.allocate(itSize);
			for (size_type i = 0; i < itSize; i++)
				this->alloc.construct(start + i, *first++);
			this->vectorSize = itSize;
			this->vectorCapacity = itSize;
		}

		vector(vector const & other) { *this = other; }

		vector& operator=(vector const & other) {
			this->alloc = alloc;
			this->start = this->alloc.allocate(other.vectorSize);
			for (size_type i = 0; i < other.vectorSize; i++)
				this->alloc.construct(start + i, other[i]);
			this->vectorSize = other.vectorSize;
			this->vectorCapacity = other.vectorCapacity;
			return (*this);
		}

		void assign(size_type count, const T& value) { // cppreference (1)
			this->reserve(count);
			for (size_type i = 0; i < count; i++)
				*(this->start + i) = value;
			this->vectorSize = count;
		}

		template<class InputIt>
		void assign(InputIt first, InputIt last, 
			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = false) {
			size_type itSize = this->getDistance(first, last);
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

		bool empty() const { return ((this->vectorSize) ? false : true); }

		void push_back(const T& value) {
			if (this->vectorSize == this->vectorCapacity)
				reserve(this->vectorCapacity + 1);
			this->start[this->vectorSize++] = value;
		}

		void pop_back() {
			this->start[this->vectorSize--] = T();
		}

		iterator insert(iterator pos, const T& value) {
			size_type dist = this->getDistance(this->begin(), pos);
			if (this->vectorSize == this->vectorCapacity)
				reserve(this->vectorSize + 1);
			for (iterator it = this->end(); it != this->begin() + dist; it--)
				*it = *(it - 1);
			*(this->begin() + dist) = value;
			this->vectorSize++;
			return (this->begin() + dist);
		}

		iterator insert(iterator pos, size_type count, const T& value) {
			if (!count)
				return (pos);
			size_type dist = this->getDistance(this->begin(), pos);
			if (this->vectorSize + count > this->vectorCapacity)
				reserve(this->vectorSize + count);
			for (iterator it = this->end() + count; it != this->begin() + dist + count - 1; it--)
				*it = *(it - count);
			for (size_type i = 0; i < count; i++)
				*(this->start + dist + i) = value;
			this->vectorSize += count;
			return (this->begin() + dist - count + 1);
		}

		template<class InputIt>
		iterator insert(iterator pos, InputIt first, InputIt last, 
			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = false) {
			if (first == last)
				return (pos);
			size_type dist = this->getDistance(this->begin(), pos);
			size_type itSize = this->getDistance(first, last);
			if (this->vectorSize + itSize > this->vectorCapacity)
				reserve(this->vectorSize + itSize);
			for (iterator it = this->end() + itSize; it != this->begin() + dist + itSize - 1; it--)
				*it = *(it - itSize);
			for (size_type i = 0; i < itSize; i++)
				*(this->start + dist + i) = *first++;
			this->vectorSize += itSize;
			return (this->begin() + dist - itSize + 1);
		}
		
		reference front() { return (*(this->start)); }
		const_reference front() const { return (*(this->start)); }
		reference back() { return (this->start[this->vectorSize - 1]); }
		const_reference back() const { return (this->start[this->vectorSize - 1]); }

		void reserve(size_type new_cap) {
			if (new_cap <= this->vectorCapacity)
				return ;
			if (new_cap > this->max_size())
				throw std::length_error("exception!");
			pointer tmp = this->alloc.allocate(new_cap);
			size_type i;
			for (i = 0; i < new_cap && i < this->vectorSize; i++)
				this->alloc.construct(tmp + i, *(start + i));
			this->alloc.deallocate(this->start, this->vectorCapacity);
			this->vectorSize = i;
			this->start = tmp;
			this->vectorCapacity = new_cap;
		}

		void resize(size_type count, T value = T()) {
			pointer tmp = this->alloc.allocate(count);
			size_type i;
			for (i = 0; i < count && i < this->vectorSize; i++)
				this->alloc.construct(tmp + i, *(this->start + i));
			while (i < count)
				this->alloc.construct(tmp + i++, value);
			this->alloc.deallocate(start, this->vectorCapacity);
			this->start = tmp;
			this->vectorSize = count;
			this->vectorCapacity = count;
		}

		iterator erase(iterator pos) {
			size_type dist = this->getDistance(this->begin(), pos);
			if (dist == this->vectorSize) {
				this->vectorSize--;
				return (this->end());
			}
			for (iterator it = this->begin() + dist; it != this->end() - 1; it++)
				*it = *(it + 1);
			this->vectorSize--;
			return (this->begin() + dist);
		}

		iterator erase(iterator first, iterator last) {
			if (first == last)
				return (last);
			iterator tmpEnd = this->end();
			size_type dist = this->getDistance(this->begin(), first);
			size_type itSize = this->getDistance(first, last);
			iterator it;
			for (iterator it = this->begin() + dist; it != this->end() - itSize + 1; it++)
				*it = *(it + itSize);
			this->vectorSize -= itSize;
			if (this->begin() + dist + itSize == tmpEnd)
				return (this->end());
			return (this->begin() + dist);
		}

		size_type size() const { return (this->vectorSize); }
		size_type capacity() const { return (this->vectorCapacity); }
		size_type max_size() const { return (this->alloc.max_size()); }

		iterator begin() { return (iterator(this->start)); }
		const_iterator begin() const { return (const_iterator(this->start)); }
		iterator end() { return (iterator(this->start + this->vectorSize)); }
		const_iterator end() const { return (const_iterator(this->start + this->vectorSize));}
		reverse_iterator rbegin() { return (reverse_iterator(this->end())); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }
		reverse_iterator rend() { return (reverse_iterator(this->begin())); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(this->begin())); }


		reference operator[](size_type pos) { return (*(this->start + pos)); }
		const_reference operator[]( size_type pos ) const { return (*(this->start + pos)); }

		void swap(vector& other) {
			allocator_type	tmpAlloc = this->alloc;
			this->alloc = other.alloc;
			other.alloc = tmpAlloc;
			
			pointer	tmpStart = this->start;
			this->start = other.start;
			other.start = tmpStart;

			size_type tmpSize = this->vectorSize;
			this->vectorSize = other.vectorSize;
			other.vectorSize = tmpSize;

			size_type tmpCapacity = this->vectorCapacity;
			this->vectorCapacity = other.vectorCapacity;
			other.vectorCapacity = tmpCapacity;
		}

		template <typename Iter>
		size_type getDistance(Iter first, Iter last) {
			size_type res = 0;
			for (Iter it = first; it != last; it++)
				res++;
			return (res);
		}
};
template<class T, class Alloc>
bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
	if (lhs.size() != rhs.size())
		return (false);
	for (size_t i = 0; i < lhs.size(); i++)
		if (lhs.start[i] != rhs.start[i])
			return (false);
	return (true);
}

template<class T, class Alloc>
bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
	return (!(lhs == rhs));
}

template<class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	return (!(lhs < rhs));
}

template<class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template<class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
	return (!(lhs > rhs));
}

template<class T, class Alloc>
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) { lhs.swap(rhs); }

};