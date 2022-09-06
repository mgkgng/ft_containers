#include "tests.hpp"

#include "vector.hpp"
#include <vector>

template<class T>
void printMyVector(ft::vector<T> vec) {
	int	i = 1;

	typename ft::vector<T>::iterator it = vec.begin();
	while (it != vec.end())
		std::cout << i++ << ": " << *it++ << std::endl;
	std::cout << "actual size: " << vec.size() << " capacity: " << vec.capacity() << std::endl;
}

template<class T>
void printRealVector(std::vector<T> vec) {
	int	i = 1;

	typename std::vector<T>::iterator it = vec.begin();
	while (it != vec.end())
		std::cout << "--" << i++ << ": " << *it++ << std::endl;
	std::cout << "actual size: " << vec.size() << " capacity: " << vec.capacity() << std::endl;	
}

template<class T>
void compareVectors(ft::vector<T> myVec, std::vector<T> realVec) {
	typename ft::vector<T>::iterator myIt = myVec.begin();
	typename std::vector<T>::iterator realIt = realVec.begin();

	
}

int testVector() {
	ft::vector<int>		myVector;
	std::vector<int>	realVector;
	clock_t				begin, end;
	float				realRes, myRes;
	int					resClock = 0, count = 0;

	ANNOUNCE1("CONSTRUCTOR TEST");
	
	ANNOUNCE2("Vector Constructor Type 1: Default Constructor");

	START_CLOCK;
	realVector = std::vector<int>();
	END_CLOCK_REAL;
	START_CLOCK;
	myVector = ft::vector<int>();
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("Vector Constructor Type 2: Constructor with allocator");
	
	START_CLOCK;
	realVector = std::vector<int>(std::allocator<int>());
	END_CLOCK_REAL;
	START_CLOCK;
	myVector = ft::vector<int>(std::allocator<int>());
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("Vector Constructor Type 3-1: Constructor with count copies of elements with value (small size value)");
	size_t n = 10;

	START_CLOCK;
	realVector = std::vector<int>(n, 15, std::allocator<int>());
	END_CLOCK_REAL;
	START_CLOCK;
	myVector = ft::vector<int>(n, 15, std::allocator<int>());
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("Vector Constructor Type 3-2: Constructor with count copies of elements with value (big size value)");
	n = 1000;
	
	START_CLOCK;
	realVector = std::vector<int>(n, 125, std::allocator<int>());
	END_CLOCK_REAL;
	START_CLOCK;
	myVector = ft::vector<int>(n, 125, std::allocator<int>());
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("Vector Constructor Type 4-1: Constructor with count copies of elements with value (small size value)");
	n = 10;
	std::vector<int> testVec = std::vector<int>(n, 3000, std::allocator<int>());
	
	START_CLOCK;
	realVector = std::vector<int>(testVec.begin(), testVec.end(), std::allocator<int>());
	END_CLOCK_REAL;
	START_CLOCK;
	myVector = ft::vector<int>(testVec.begin(), testVec.end(), std::allocator<int>());
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("Vector Constructor Type 4-2: Constructor with count copies of elements with value (big size value)");
	n = 1500;
	testVec = std::vector<int>(n, 3000, std::allocator<int>());
	
	START_CLOCK;
	realVector = std::vector<int>(testVec.begin(), testVec.end(), std::allocator<int>());
	END_CLOCK_REAL;
	START_CLOCK;
	myVector = ft::vector<int>(testVec.begin(), testVec.end(), std::allocator<int>());
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("Vector Constructor Type 5: Copy Constructor");
	ft::vector<int> testMyVec = ft::vector<int>(n, 3000, std::allocator<int>());
	
	START_CLOCK;
	realVector = std::vector<int>(testVec);
	END_CLOCK_REAL;
	START_CLOCK;
	myVector = ft::vector<int>(testMyVec);
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE1("CAPACITY TEST");

	ANNOUNCE2("reserve");
	
	START_CLOCK;
	realVector.resize(500);
	END_CLOCK_REAL;
	START_CLOCK;
	myVector.resize(500);
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE1("MODIFIER TEST");

	ANNOUNCE2("clear");
	
	START_CLOCK;
	realVector.clear();
	END_CLOCK_REAL;
	START_CLOCK;
	myVector.clear();
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("insert 1");
	n = 15;
	realVector = std::vector<int>(n, 15, std::allocator<int>());
	myVector = ft::vector<int>(n, 15, std::allocator<int>());

	START_CLOCK;
	realVector.insert(realVector.begin() + 12, 35);
	END_CLOCK_REAL;
	START_CLOCK;
	myVector.insert(myVector.begin() + 12, 35);
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("insert 2");
	n = 4;

	START_CLOCK;
	realVector.insert(realVector.begin() + 7, n, 99);
	END_CLOCK_REAL;
	START_CLOCK;
	myVector.insert(myVector.begin() + 7, n, 99);
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	// ANNOUNCE2("insert 3");
	// n = 7;
	// testVec = std::vector<int>(n, 777, std::allocator<int>());
	// testMyVec = ft::vector<int>(n, 777, std::allocator<int>());

	// START_CLOCK;
	// realVector.insert(realVector.begin() + 26, testVec.begin(), testVec.end());
	// END_CLOCK_REAL;
	// START_CLOCK;
	// myVector.insert(myVector.begin() + 26, testMyVec.begin(), testMyVec.end());
	// END_CLOCK_MY;
	// CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("erase 1");

	START_CLOCK;
	realVector.erase(realVector.begin() + 15);
	END_CLOCK_REAL;
	START_CLOCK;
	myVector.erase(myVector.begin() + 15);
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("erase 2");

	START_CLOCK;
	realVector.erase(realVector.begin() + 2, realVector.begin() + 8);
	END_CLOCK_REAL;
	START_CLOCK;
	myVector.erase(myVector.begin() + 2, myVector.begin() + 8);
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("push_back");

	START_CLOCK;
	realVector.push_back(71359);
	END_CLOCK_REAL;
	START_CLOCK;
	myVector.push_back(71359);
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("pop_back");

	START_CLOCK;
	realVector.pop_back();
	END_CLOCK_REAL;
	START_CLOCK;
	myVector.pop_back();
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("resize");

	START_CLOCK;
	realVector.resize(40, 9);
	END_CLOCK_REAL;
	START_CLOCK;
	myVector.resize(40, 9);
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	ANNOUNCE2("swap");
	testVec = std::vector<int>(n, 777, std::allocator<int>());
	testMyVec = ft::vector<int>(n, 777, std::allocator<int>());

	START_CLOCK;
	realVector.swap(testVec);
	END_CLOCK_REAL;
	START_CLOCK;
	myVector.swap(testMyVec);
	END_CLOCK_MY;
	CHECK(VECTOR, ONLY_CLOCK);

	usleep(SLEEP_DURATION);
	std::cout << std::endl << "\033[0;36mVECTOR RESULT: " << resClock << " / " << count;
	if (resClock == count) {
		std::cout << "\033[0;34m SUCCESS\033[0;37m" << std::endl << std::endl;
		return (1);
	}
	std::cout << "\033[0;31m FAILURE\033[0;37m" << std::endl << std::endl;
	return (0);
}
