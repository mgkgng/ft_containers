#pragma once

#include <memory>
#include "lib.hpp"
#include "Iterator.hpp"

namespace ft {

template < typename T, typename Allocator = std::allocator<T> >
class vector {
	
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
		typedef typename Allocator::pointer 					pointer;
		typedef typename Allocator::const_pointer 				const_pointer;
		typedef typename ft::RandomAccessIterator<T> 			iterator;
		typedef typename ft::RandomAccessIterator<const T>		const_iterator;
		typedef ft::ReverseIterator<iterator> 					reverse_iterator;
		typedef ft::ReverseIterator<const iterator> 			const_reverse_iterator; 

		////////////////////////
		// ** contstructor ** //
		////////////////////////



		vector(const vector& other) { // cppreference(6)
			// Copy constructor. Constructs the container with the copy of the contents of other.
			*this = other;
		}

		////////////////////////////////////////////////////////
		// ** destructor, operator=, assign, get_allocator ** //
		////////////////////////////////////////////////////////

		~vector() {
			this->clear();
			// _alloc.deallocate(_start, _capacity);
		}

		vector& operator=(const vector& other) {
			// Copy assignment operator. Replaces the contents with a copy of the contents of other.
			_alloc = other._alloc;
			_start = _alloc.allocate(other._capacity);
			for (size_type i = 0; i < other._size; i++)
				_alloc.construct(_start + i, *(other._start + i));
			_end = _start + other._size;
			_size = other._size;
			_capacity = other._capacity;
			return (*this);
		}

		void assign(size_type count, const T& value) { // cppreference (1)
			// Replaces the contents with count copies of value value
			this->clear();
			if (count > _capacity)
				this->getMoreCapacity(count);

			for (size_type i = 0; i < count; i++)
				_alloc.construct(_start + i, value);
		}

		template<class InputIt>
		void assign(InputIt first, InputIt last, 
			typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = false) {
			this->clear();
			difference_type size = ft::distance(first, last);
			if ((size_type) size > _capacity)
				this->getMoreCapacity(size);
			while (first != last)
				_alloc.construct(_start++, *(first++));
			_end += size;
		}

		allocator_type get_allocator() const { return (_alloc); }

		//////////////////////////
		// ** Element access ** //
		//////////////////////////

		reference at(size_type pos) {
			// Returns a reference to the element at specified location pos, with bounds checking.
			// If pos is not within the range of the container, an exception of type std::out_of_range is thrown.
			if (pos >= _capacity)
				throw std::out_of_range("vector error: out of range");
			return (*(_start + pos));
		}

		const_reference at(size_type pos) const {
			return (*(_start + pos));
		}

		reference operator[](size_type pos) { return (*(_start + pos)); }
		const_reference operator[](size_type pos) const { return (*(_start + pos));}
		reference front() { return (*_start); }
		const_reference front() const { return (*_start); }
		reference back() { return (*(_end - 1)); }

		const_reference back() const {
			if (!_size)
				return (*_end);
			return (*(_end - 1));
		}

		T* data() { return (_start); }
		const T* data() const { return (_start); }

		/////////////////////
		// ** Iterators ** //
		/////////////////////

		iterator begin() { return (iterator(_start)); }
		const_iterator begin() const { return (const_iterator(_start)); }
		iterator end() { return (iterator(_end)); }
		const_iterator end() const { return (const_iterator(_end)); }
		reverse_iterator rbegin() { return (reverse_iterator(this->end())); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->end())); }
		reverse_iterator rend() { return (reverse_iterator(this->start())); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(this->start())); }

		////////////////////
		// ** Capacity ** //
		////////////////////

		bool empty() const {
			// Checks if the container has no elements, i.e. whether begin() == end().
			if (this->begin() == this->end())
				return (true);
			return (false);
		}

		size_type size() const { return (_size); }

		size_type max_size() const { return (_alloc.max_size()); }

		void reserve(size_type new_cap) {
			if (new_cap <= _capacity)
				return ;
			if (new_cap > this->max_size())
				throw std::length_error("vector error: length");
	
			this->recapacity(new_cap); //TO_DO CHECK IT
		}

		size_type capacity() const { return (_capacity); }

		/////////////////////
		// ** Modifiers ** //
		/////////////////////

		void clear() {
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_start + i);
			_size = 0;
		}

		iterator insert(iterator pos, const T& value) {
		
			for (iterator it = _end; it != _start + diff; it--)
			 	*it = *(it - 1);
			*(_start + diff) = value;
			return (_start + diff);
		}

		void insert(iterator pos, size_type count, const T& value) {
			difference_type diff = &*pos - &*_start;
			if (_size + count > _capacity)
				this->getMoreCapacity(_size + count);
			_end += count;
			_size += count;
		
			for (iterator it = _end; it != _start + diff + count; it--)
				*it = *(it - count);
			for (iterator it = _start + diff; it != _start + diff + count; it++)
				*it = value;
		}

		template<class InputIt>
		void insert(iterator pos, InputIt first, InputIt last) {
			difference_type diff = &*pos - &*_start;
			difference_type count = &*last - &*first;
			if ((size_type) diff > _size) {
				_size = diff;
				_end = _start + _size;
			}
			if (_size + count > _capacity)
				this->getMoreCapacity(_size + count);
			_end += count;
			_size += count;

			for (iterator it = _end; it != _start + diff; it--)
				*it = *(it - count);
			for (iterator it = _start + diff; it != _start + diff + count; it++)
				*it = *first++;
		}

		iterator erase(iterator pos) {
			for (iterator it = pos; it != _end - 1; it++)
				*it = *(it + 1);
			_alloc.destroy(_end - 1);
			_end--;
			_size--;
			return (pos);
		}

		iterator erase(iterator first, iterator last) {
			difference_type count = &*last - &*first;

			iterator it;
			for (it = first; it != _end - count; it++)
				*it = *(it + count);
			while (it != _end)
				_alloc.destroy(&*it++);
			_end -= count;
			_size -= count;
			return (first);
		}
		
		void push_back(const T& value) {
			if (_size >= _capacity)
				this->getMoreCapacity(_size + 1);
			*(_start + _size++) = value;
			_end++;
		}

		void pop_back() {
			_alloc.destroy(_end-- - 1);
			_size--;
		}

		void resize(size_type count, T value = T()) {
			this->recapacity(count);
			if (_size == count)
				return ;
			for (int i = 0; _size + i < count; i++)
				_alloc.construct(_end + i, value);
			this->_size = count;
			this->_end = _start + count;
		}

		void swap(vector& other) {
			allocator_type	tmp = _alloc;
			_alloc = other._alloc;
			other._alloc = tmp;
			
			pointer	tmp2 = _start;
			_start = other._start;
			other._start = tmp2;

			pointer tmp3 = _end;
			_end = other._end;
			other._end = tmp3;

			size_type tmp4 = _size;
			_size = other._size;
			other._size = tmp4;

			size_type tmp5 = _capacity;
			_capacity = other._capacity;
			other._capacity = tmp5;
		}

	protected:
		void getMoreCapacity(size_type n) {
			if (!_capacity) {
				this->recapacity(n);
				return ;
			}
			while (n > _capacity)
				this->recapacity(_capacity * 2);
		}

		void recapacity(size_type count) {
			pointer tmp = this->_alloc.allocate(count);
			if (count == 1)
				return ;
			size_type i = 0;
			for (iterator it = _start; i < count && it != this->_end; it++)
				_alloc.construct(tmp + i++, *it);

			this->clear();
			_alloc.deallocate(_start, _capacity);

			this->_start = tmp;
			this->_capacity = count;
			this->_size = i;
			this->_end = _start + i;
		}

	private:
		allocator_type	_alloc; // allocator to use for all memory allocations of this container
		pointer			_start; // the starting address of the container
		pointer			_end; // the ending address of the container
		size_type		_size; // the size of the container
		size_type		_capacity; // the capacity of the container

	};

	template<class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		if (lhs._size != rhs._size)
			return (false);
		for (int i = 0; i < lhs._size; i++)
			if (lhs._start + i != rhs._start + i)
				return (false);
		return (true);
	}
		
	template<class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template<class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs._start, lhs._end, rhs._start, rhs._end));
	}

	template<class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (ft::lexicographical_compare(rhs._start, rhs._end, lhs._start, lhs._end));
	}

	template<class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (!(lhs > rhs));
	}

	template<class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (!(lhs < rhs));
	}

	template<class T, class Alloc>
	void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) {
		lhs.swap(rhs);
	}
};