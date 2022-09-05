#include "tests.hpp"

#include <map>
#include "map.hpp"

#define TIME_TEST resTest += printTimeResult((char *) "Map", realRes, myRes)

int testMap() {
	ft::map<int, string> myMap;
	std::map<int, string> realMap;
	clock_t begin, end;
	float	realRes, myRes;
	int		resTest = 0;
	int		count = 0;

	std::cout << "\033[0;36m*******************CONSTRUCTOR TEST*******************\033[0;37m" << std::endl << std::endl;
	
	usleep(SLEEP_DURATION);
	std::cout << "\033[0;34m** Map Constructor Type 1: Default Constructor\033[0;37m" << std::endl;

	begin = clock();
	realMap = std::map<int, string>();
	end = clock();
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	myMap = ft::map<int, string>();
	end = clock();
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;

	TIME_TEST;
	count++;

	usleep(SLEEP_DURATION);
	std::cout << std::endl << "\033[0;MAP RESULT: " << resTest << " / " << count;
	if (resTest == count) {
		std::cout << "\033[0;34m SUCCESS\033[0;37m" << std::endl << std::endl;
		return (1);
	}
	std::cout << "\033[0;31m FAILURE\033[0;37m" << std::endl << std::endl;
	return (0);
}