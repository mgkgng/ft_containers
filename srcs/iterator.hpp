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
		RandomAccessIterator() {

		}

		RandomAccessIterator(const RandomAccessIterator<T> &other) {

		}

		~RandomAccessIterator() {}

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

		RandomAccessIterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		RandomAccessIterator& operator--() {
			ptr--;
			return (*this);
		}

		RandomAccessIterator operator--(int) {
			RandomAccessIterator tmp = *this;
			--(*this);
			return (tmp);
		}

		friend bool operator==(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) {
			return (lhs.ptr == rhs.ptr);
		}

		friend bool operator!=(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) {
			return (lhs.ptr != rhs.ptr);
		}
	
        RandomAccessIterator operator+(difference_type n) const {
        }

        RandomAccessIterator operator-(difference_type n) const {
        }

        RandomAccessIterator& operator+=(difference_type n) {
            ptr += n;
            return (*this);
        }
		
        RandomAccessIterator& operator-=(difference_type n) {
            ptr -= n;
            return (*this);
        }
};

};