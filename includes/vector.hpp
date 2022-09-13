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
		

		

	template<class T, class Alloc>
	void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) {
		lhs.swap(rhs);
	}
};