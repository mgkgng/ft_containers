#include "tests.hpp"

#include <map>
#include "map.hpp"
#include <utility>

template<class Key, class Value>
bool compare(ft::map<Key, Value> mine, std::map<Key, Value> real) {
	if (mine.size() != real.size()) {
		PRINT_KO;
		std::cout << "SIZE IS DIFFERENT: " << mine.size() << " / " << real.size() << std::endl;
		return (false);
	}

	typename ft::map<Key, Value>::iterator myIt;
	typename std::map<Key, Value>::iterator realIt = real.begin();
	for (myIt = mine.begin(); myIt != mine.end(); myIt++) {
		// if (*myIt != *realIt++) {
		// 	PRINT_KO;
		// 	// printMine(mine);
		// 	// printReal(real);
		// 	return (false);
		// }
	}
	PRINT_OK;
	return (true);
}

int testMap() {
	clock_t begin, end;
	float	realRes, myRes;
	int		resClock = 0, count = 0;

	ANNOUNCE1("CONSTRUCTOR TEST");
	
	ANNOUNCE2("Map Constructor Type 1: Default Constructor");

	START_CLOCK;
	std::map<int, string> real;
	END_CLOCK_REAL;
	START_CLOCK;
	ft::map<int, string> mine;
	END_CLOCK_MY;
	CHECK(MAP, ONLY_CLOCK);

	// ft::map<int, string>::iterator myIt = mine.begin();
	// std::map<int, string>::iterator realIt = real.begin();
	// std::cout << "pardon?" << std::endl;
	// std::cout << "my type: " << typeid(myIt).name() << std::endl;
	// std::cout << "real type: " << typeid(realIt).name() << std::endl;


	ANNOUNCE2("Map Constructor Type 2: Default Constructor with compare and allocator");

	START_CLOCK;
	real = std::map<int, string>(std::less<int>(), std::allocator<std::pair<const int, string> >());
	END_CLOCK_REAL;
	START_CLOCK;
	mine = ft::map<int, string>(std::less<int>(), std::allocator<ft::pair<const int, string> >());
	END_CLOCK_MY;
	CHECK(MAP, ONLY_CLOCK);

	ANNOUNCE2("Map Constructor Type 3: Constructor with iterator");
	std::map<int, string> testMap;

	testMap[2] = "lol";
	testMap[5] = "five";
	testMap[1] = "prime";
	std::cout << "test value at begin: " << (*testMap.begin()).second << std::endl;
	START_CLOCK;
	real = std::map<int, string>(testMap.begin(), testMap.end());
	END_CLOCK_REAL;
	START_CLOCK;
	mine = ft::map<int, string>(testMap.begin(), testMap.end());
	END_CLOCK_MY;
	CHECK(MAP, ONLY_CLOCK);

	END_TEST(MAP);
}