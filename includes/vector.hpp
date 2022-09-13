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