#include <iostream>
#include <string>
#include <chrono>

#include "tests.hpp"

typedef struct results {
	bool vector;
	bool map;
	bool pair;
	bool stack;
	bool set;
} results;

void printResult(std::string container, bool res) {
	usleep(SLEEP_DURATION);
	std::cout << container << ": ";
	if (res)
		std::cout << "SUCCESS" << std::endl;
	std::cout << "FAILURE" << std::endl;
}

int main() {
	results res;

	std::cout << "Test Starts." << std::endl;

	res.vector = testVector();
	res.pair = testPair();
	res.map = testMap();
	// res.stack = testStack();
	// res.set = testSet();

	usleep(SLEEP_DURATION);
	std::cout << "Test Result:" << std::endl;
	printResult("Vector", res.vector);
	printResult("Pair", res.pair);
	printResult("Map", res.map);
	// printResult("Stack", res.stack);
	// printResult("Set", res.set);
}