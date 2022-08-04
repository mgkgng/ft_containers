namespace ft {

class BiDirectionalIterator {

// 1. Usability
// 2. Equality / Inequality Comparaison
// 3. Dereferencing
// 4. Incrementable
// 5. Decrementable
// 6. Swappable

	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T& reference;
	typedef T* pointer;

	private:
		pointer ptr;

	public:
		reference operator*() const {
			return (*ptr);
		}

		pointer operator->() {
			return (ptr);
		}

		BiDirectionalIterator& operator++() {
			ptr++;
			return (*this);
		}

		BiDirectionalIterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		BiDirectionalIterator& operator--() {
			ptr--;
			return (*this);
		}

		BiDirectionalIterator operator--(int) {
			BiDirectionalIterator tmp = *this;
			--(*this);
			return (tmp);
		}

		friend bool operator==(const BiDirectionalIterator& lhs, const BiDirectionalIterator& rhs) {
			return (lhs.ptr == rhs.ptr);
		}

		friend bool operator!=(const BiDirectionalIterator& lhs, const BiDirectionalIterator& rhs) {
			return (lhs.ptr != rhs.ptr);
		}
	
   		BiDirectionalIterator operator+(difference_type n) const {
        }

        BiDirectionalIterator operator-(difference_type n) const {
        }

};
};