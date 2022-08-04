#include "BiDirectionalIterator.hpp"

namespace ft {

template <typename T>
class RandomAccessIterator : public ft::BiDirectionalIterator {

	public:
		RandomAccessIterator() {

		}

		RandomAccessIterator(const RandomAccessIterator<T> &other) {

		}

		~RandomAccessIterator() {}

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