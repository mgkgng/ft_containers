#include "tests.hpp"

#include <map>
#include "map.hpp"

template<class Key, class Value>
bool compare(ft::map<Key, Value> mine, std::map<Key, Value> real) {
	typename ft::map<Key, Value>::iterator myIt = mine.begin();
	typename std::map<Key, Value>::iterator realIt = real.begin();
	
	return (false);
}

int testMap() {
	ft::map<int, string>	mine;
	std::map<int, string>	real;
	clock_t begin, end;
	float	realRes, myRes;
	int		resClock = 0, count = 0;

	ANNOUNCE1("CONSTRUCTOR TEST");
	
	ANNOUNCE2("Map Constructor Type 1: Default Constructor");

	START_CLOCK;
	real = std::map<int, string>(std::less<int>());
	END_CLOCK_REAL;
	START_CLOCK;
	mine = ft::map<int, string>();
	END_CLOCK_MY;
	CHECK(MAP, ONLY_CLOCK);

	ANNOUNCE2("Map Constructor Type 2: Constructor with iterator");

	START_CLOCK;
	real = std::map<int, string>();
	END_CLOCK_REAL;
	START_CLOCK;
	mine = ft::map<int, string>();
	END_CLOCK_MY;
	CHECK(MAP, ONLY_CLOCK);

	ANNOUNCE2("Map Constructor Type 2: Constructor with iterator");

	START_CLOCK;
	real = std::map<int, string>();
	END_CLOCK_REAL;
	START_CLOCK;
	mine = ft::map<int, string>();
	END_CLOCK_MY;
	CHECK(MAP, ONLY_CLOCK);

	END_TEST(MAP);
}