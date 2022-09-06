#pragma once

#include <time.h>
#include <memory>
#include <unistd.h>

#define VECTOR "Vector"
#define MAP "Map"

#define SLEEP_DURATION 500000

/***** ANNOUNCE ******/
#define ANNOUNCE1(s) do {\
	usleep(SLEEP_DURATION);\
	std::cout << "\033[0;36m*******************" << s << "*******************\033[0;37m" << std::endl << std::endl;\
} while (0)
#define ANNOUNCE2(s) do {\
	usleep(SLEEP_DURATION);\
	std::cout << "\033[0;34m** " << s << "\033[0;37m" << std::endl;\
} while (0)

/***** CHECKER *****/
#define ONLY_CLOCK 0
#define WITH_COMPARE 1
#define CHECK_CLOCK(CONTAINER) do {\
	resClock += printTimeResult((char *) CONTAINER, realRes, myRes);\
} while (0)

#define COMPARE_VECTORS

#define CHECK(CONTAINER, x) do {\
	CHECK_CLOCK(CONTAINER);\
	if (x == WITH_COMPARE)\
		COMPARE_VECTORS;\
	count++;\
} while (0)

/***** CLOCK *****/
#define START_CLOCK begin = clock()
#define END_CLOCK_REAL do {\
	end = clock();\
	realRes = (double)(end - begin) / CLOCKS_PER_SEC;\
} while (0)
#define END_CLOCK_MY do {\
	end = clock();\
	myRes = (double)(end - begin) / CLOCKS_PER_SEC;\
} while (0)

using std::string;

/* tester */
int testVector();
int testMap();
int testSet();
int testStack();
int testPair();

/* utils */
int	printTimeResult(char *container, double realRes, double myRes);
