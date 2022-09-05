#include "tests.hpp"

#include "vector.hpp"
#include <memory>
#include <vector>

void	printTimeResult(double realRes, double myRes) {
	if (realRes < myRes)
		printf("realVector: \033[0;31m%f\t\t\033[0;37mmyVector: %f\n", realRes, myRes);
	else
		printf("realVector: %f\t\tmyVector: \033[0;32m%f\033[0;37m\n", realRes, myRes);
}


int testVector() {
	ft::vector<int> myVector;
	std::vector<int> realVector;
	clock_t begin, end;
	float	realRes, myRes;

	std::cout << "*******************CONSTRUCTOR TEST*******************" << std::endl << std::endl;
	
	std::cout << "** Vector Constructor Type 1: Default Constructor" << std::endl;

	begin = clock();
	realVector = std::vector<int>();
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector = ft::vector<int>();
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	printTimeResult(realRes, myRes);

	std::cout << "** Vector Constructor Type 2: Constructor with allocator" << std::endl;
	
	begin = clock();
	realVector = std::vector<int>(std::allocator<int>());
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector = ft::vector<int>(std::allocator<int>());
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	printTimeResult(realRes, myRes);

	std::cout << "** Vector Constructor Type 3-1: Constructor with count copies of elements with value (small size value)" << std::endl;
	size_t n = 10;

	begin = clock();
	realVector = std::vector<int>(n, 15, std::allocator<int>());
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector = ft::vector<int>(n, 15, std::allocator<int>());
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	printTimeResult(realRes, myRes);

	std::cout << "** Vector Constructor Type 3-2: Constructor with count copies of elements with value (big size value)" << std::endl;
	n = 1000;
	
	begin = clock();
	realVector = std::vector<int>(n, 125, std::allocator<int>());
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector = ft::vector<int>(n, 125, std::allocator<int>());
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	printTimeResult(realRes, myRes);

	std::cout << "** Vector Constructor Type 4-1: Constructor with count copies of elements with value (small size value)" << std::endl;
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

	printTimeResult(realRes, myRes);

	std::cout << "** Vector Constructor Type 4-2: Constructor with count copies of elements with value (big size value)" << std::endl;
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

	printTimeResult(realRes, myRes);

	std::cout << "** Vector Constructor Type 5: Copy Constructor" << std::endl;
	ft::vector<int> testMyVec = ft::vector<int>(n, 3000, std::allocator<int>());
	
	begin = clock();
	realVector = std::vector<int>(testVec);
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myVector = ft::vector<int>(testMyVec);
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	printTimeResult(realRes, myRes);
	// begin = clock();
	// realVector = std::vector<int>(1000, 15);
	// end = clock();
	// timeRes = (double)(end - begin) / CLOCKS_PER_SEC;
	// printf("%f..\n", timeRes);

	// begin = clock();
	// myVector = ft::vector<int>(500, 15);
	// end = clock();
	// timeRes = (double)(end - begin) / CLOCKS_PER_SEC;
	// printf("%f..\n", timeRes);

	// begin = clock();
	// myVector.push_back(345);
	// end = clock();
	// timeRes = (double)(end - begin) / CLOCKS_PER_SEC;
	// printf("%f..\n", timeRes);

	// begin = clock();
	// realVector.push_back(345);
	// end = clock();
	// timeRes = (double)(end - begin) / CLOCKS_PER_SEC;
	// printf("%f..\n", timeRes);

	return (0);

}
