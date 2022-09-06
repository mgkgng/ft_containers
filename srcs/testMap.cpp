#include "tests.hpp"

#include <map>
#include "map.hpp"

int testMap() {
	ft::map<int, string> myMap;
	std::map<int, string> realMap;
	clock_t begin, end;
	float	realRes, myRes;
	int		resClock = 0, count = 0;

	ANNOUNCE1("CONSTRUCTOR TEST");
	
	ANNOUNCE2("Map Constructor Type 1: Default Constructor");

	START_CLOCK;
	realMap = std::map<int, string>(std::less<int>());
	END_CLOCK_REAL;
	START_CLOCK;
	myMap = ft::map<int, string>();
	END_CLOCK_MY;
	CHECK(MAP, ONLY_CLOCK);

	ANNOUNCE2("Map Constructor Type 2: Constructor with iterator");

	START_CLOCK;
	realMap = std::map<int, string>();
	END_CLOCK_REAL;
	START_CLOCK;
	myMap = ft::map<int, string>();
	END_CLOCK_MY;
	CHECK(MAP, ONLY_CLOCK);

	usleep(SLEEP_DURATION);
	std::cout << std::endl << "\033[0;MAP RESULT: " << resClock << " / " << count;
	if (resClock == count) {
		std::cout << "\033[0;34m SUCCESS\033[0;37m" << std::endl << std::endl;
		return (1);
	}
	std::cout << "\033[0;31m FAILURE\033[0;37m" << std::endl << std::endl;
	return (0);
}