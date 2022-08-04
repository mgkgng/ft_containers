namespace ft {

	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		while (first1 < last1)
			if (first1++ != first2++)
				return (false);
		return (true);
	}

	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {

	}

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
		while (first1 < last1 && first2 < last2 && *first1 == *first2) {
			first1++;
			first2++;
		}
		return (first2 - first1 > 0) ? true : false;
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
		while (first1 < last1 && first2 < last2 && *first1 == *first2) {
			first1++;
			first2++;
		}
		return (comp(first1, first2));
	}

	template<class T>
	bool is_integral(T value) {
		// bool, char, char16_t, char32_t, wchar_t, signed char, 
		// short int, int, long int, long long int
		// unsigned char, unsigned short int, unsigned int, unsigned logn int, unsigned long long int

	}
};