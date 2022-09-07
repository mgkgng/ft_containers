#pragma once

#include <time.h>
#include <memory>
#include <iostream>
#include <unistd.h>

#define VECTOR "Vector"
#define MAP "Map"
#define PAIR "Pair"

#define SLEEP_DURATION 50000

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

#define COMPARE compare(mine, real)

#define CHECK(CONTAINER, x) do {\
	CHECK_CLOCK(CONTAINER);\
	if (x == WITH_COMPARE)\
		COMPARE;\
	count++;\
	std::cout << std::endl;\
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

/***** END *****/
#define END_TEST(CONTAINER) do {\
	usleep(SLEEP_DURATION);\
	std::cout << std::endl << "\033[0;36m" << CONTAINER << " Result: " << resClock << " / " << count;\
	if (resClock == count) {\
		std::cout << "\033[0;32m SUCCESS\033[0;37m" << std::endl << std::endl;\
		return (1);\
	}\
	std::cout << "\033[0;31m FAILURE\033[0;37m" << std::endl << std::endl;\
	return (0);\
} while (0)

/***** PRINT *****/
#define PRINT_OK std::cout << "result: \033[0;32mOK\033[0;37m"
#define PRINT_KO std::cout << "result: \033[0;31mKO\033[0;37m"

using std::string;

/* tester */
int testVector();
int testMap();
int testPair();
int testSet();
int testStack();
int testPair();

/* utils */
int	printTimeResult(char *container, double realRes, double myRes);
