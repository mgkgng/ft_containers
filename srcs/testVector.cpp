#include "tests.hpp"

#define SLEEP_DURATION 50000
#include "vector.hpp"
#include <memory>
#include <vector>
#include <unistd.h>

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

int	printTimeResult(double realRes, double myRes) {
	if (realRes * 20 < myRes) {
		printf("realVector: \033[0;31m%f\t\t\033[0;37mmyVector: %f\n", realRes, myRes);
		return (0);
	}
	else if (realRes < myRes) 
		printf("realVector: \033[0;33m%f\t\t\033[0;37mmyVector: %f\n", realRes, myRes);
	else
		printf("realVector: %f\t\tmyVector: \033[0;32m%f\033[0;37m\n", realRes, myRes);
	return (1);
}


int testVector() {
	ft::vector<int> myVector;
	std::vector<int> realVector;
	clock_t begin, end;
	float	realRes, myRes;
	int		resTest = 0;
	int		count = 0;

	std::cout << "\033[0;36m*******************CONSTRUCTOR TEST*******************\033[0;37m" << std::endl << std::endl;
	
	usleep(SLEEP_DURATION);
	std::cout << "\033[0;34m** Vector Constructor Type 1: Default Constructor\033[0;37m" << std::endl;

	begin = clock();
	realVector = std::vector<int>();
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector = ft::vector<int>();
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	resTest += printTimeResult(realRes, myRes);
	count++;

	usleep(SLEEP_DURATION);
	std::cout << "\033[0;34m** Vector Constructor Type 2: Constructor with allocator\033[0;37m" << std::endl;
	
	begin = clock();
	realVector = std::vector<int>(std::allocator<int>());
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector = ft::vector<int>(std::allocator<int>());
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	resTest += printTimeResult(realRes, myRes);
	count++;

	usleep(SLEEP_DURATION);
	std::cout << "\033[0;34m** Vector Constructor Type 3-1: Constructor with count copies of elements with value (small size value)\033[0;37m" << std::endl;
	size_t n = 10;

	begin = clock();
	realVector = std::vector<int>(n, 15, std::allocator<int>());
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector = ft::vector<int>(n, 15, std::allocator<int>());
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	resTest += printTimeResult(realRes, myRes);
	count++;

	usleep(SLEEP_DURATION);
	std::cout << "\033[0;34m** Vector Constructor Type 3-2: Constructor with count copies of elements with value (big size value)\033[0;37m" << std::endl;
	n = 1000;
	
	begin = clock();
	realVector = std::vector<int>(n, 125, std::allocator<int>());
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector = ft::vector<int>(n, 125, std::allocator<int>());
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	resTest += printTimeResult(realRes, myRes);
	count++;

	usleep(SLEEP_DURATION);
	std::cout << "\033[0;34m** Vector Constructor Type 4-1: Constructor with count copies of elements with value (small size value)\033[0;37m" << std::endl;
	n = 10;
	std::vector<int> testVec = std::vector<int>(n, 3000, std::allocator<int>());
	
	begin = clock();
	realVector = std::vector<int>(testVec.begin(), testVec.end(), std::allocator<int>());
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector = ft::vector<int>(testVec.begin(), testVec.end(), std::allocator<int>());
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	resTest += printTimeResult(realRes, myRes);
	count++;

	usleep(SLEEP_DURATION);
	std::cout << "\033[0;34m** Vector Constructor Type 4-2: Constructor with count copies of elements with value (big size value)\033[0;37m" << std::endl;
	n = 1500;
	testVec = std::vector<int>(n, 3000, std::allocator<int>());
	
	begin = clock();
	realVector = std::vector<int>(testVec.begin(), testVec.end(), std::allocator<int>());
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector = ft::vector<int>(testVec.begin(), testVec.end(), std::allocator<int>());
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	resTest += printTimeResult(realRes, myRes);
	count++;

	usleep(SLEEP_DURATION);
	std::cout << "\033[0;34m** Vector Constructor Type 5: Copy Constructor\033[0;37m" << std::endl;
	ft::vector<int> testMyVec = ft::vector<int>(n, 3000, std::allocator<int>());
	
	begin = clock();
	realVector = std::vector<int>(testVec);
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector = ft::vector<int>(testMyVec);
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	resTest += printTimeResult(realRes, myRes);
	count++;

	usleep(SLEEP_DURATION);
	std::cout << std::endl << "\033[0;36m*******************CAPACITY TEST*******************\033[0;37m" << std::endl << std::endl;

	usleep(SLEEP_DURATION);
	std::cout << "\033[0;34m** reserve\033[0;37m" << std::endl;
	
	begin = clock();
	realVector.resize(500);
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector.resize(500);
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	resTest += printTimeResult(realRes, myRes);
	count++;

	usleep(SLEEP_DURATION);
	std::cout << std::endl << "\033[0;36m*******************MODIFIER TEST*******************\033[0;37m" << std::endl << std::endl;

	usleep(SLEEP_DURATION);
	std::cout << "\033[0;34m** clear\033[0;37m" << std::endl;
	
	begin = clock();
	realVector.clear();
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector.clear();
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	resTest += printTimeResult(realRes, myRes);
	count++;

	usleep(SLEEP_DURATION);
	n = 15;
	std::cout << "\033[0;34m** insert 1\033[0;37m" << std::endl;
	realVector = std::vector<int>(n, 15, std::allocator<int>());
	myVector = ft::vector<int>(n, 15, std::allocator<int>());
	//printMyVector(myVector);

	begin = clock();
	realVector.insert(realVector.begin() + 12, 35);
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector.insert(myVector.begin() + 12, 35);
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	resTest += printTimeResult(realRes, myRes);
	count++;

	usleep(SLEEP_DURATION);
	std::cout << "\033[0;34m** insert 2\033[0;37m" << std::endl;
	n = 4;

	begin = clock();
	realVector.insert(realVector.begin() + 7, n, 99);
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;
	printRealVector(realVector);

	begin = clock();
	myVector.insert(myVector.begin() + 7, n, 99);
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;
	printMyVector(myVector);

	resTest += printTimeResult(realRes, myRes);
	count++;

	usleep(SLEEP_DURATION);
	std::cout << "\033[0;34m** insert 3\033[0;37m" << std::endl;
	n = 7;
	testVec = std::vector<int>(n, 777, std::allocator<int>());
	testMyVec = ft::vector<int>(n, 777, std::allocator<int>());

	begin = clock();
	realVector.insert(realVector.begin() + 26, testVec.begin(), testVec.end());
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;
	printRealVector(realVector);

	begin = clock();
	myVector.insert(myVector.begin() + 26, testMyVec.begin(), testMyVec.end());
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;
	printMyVector(myVector);

	resTest += printTimeResult(realRes, myRes);
	count++;

	usleep(SLEEP_DURATION);
	std::cout << std::endl << "\033[0;36mVECTOR RESULT: " << resTest << " / " << count;
	if (resTest == count)
		std::cout << "\033[0;34m SUCCESS\033[0;37m" << std::endl << std::endl;
	else
		std::cout << "\033[0;31m FAILURE\033[0;37m" << std::endl << std::endl;

	return (0);
}
