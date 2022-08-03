namespace ft {

template <typename T>
class RandomAccessIterator {

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

		RandomAccessIterator& operator++() {
			ptr++;
			return (*this);
		}

		RandomAccessIterator operator++(value_type) {
			Iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		friend bool operator==(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) {
			return (lhs.ptr == rhs.ptr);
		}

		friend bool operator!=(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) {
			return (lhs.ptr != rhs.ptr);
		}
};

};