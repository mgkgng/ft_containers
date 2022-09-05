#include "tests.hpp"

#include "vector.hpp"
#include <vector>

int testVector() {
	ft::vector<int> myVector;
	std::vector<int> realVector;
	clock_t begin, end;
	double	timeRes = 0.0;

	begin = clock();
	myVector.push_back(345);
	end = clock();
	timeRes += (double)(end - begin) / CLOCKS_PER_SEC;

	std::cout << "my Vector time spent: " << timeRes << std::endl;

	timeRes = 0.0;
	begin = clock();
	realVector.push_back(345);
	end = clock();
	timeRes = (double)(end - begin) / CLOCKS_PER_SEC;

	std::cout << "Real Vector time spent: " << timeRes << std::endl;

	return (0);

}
