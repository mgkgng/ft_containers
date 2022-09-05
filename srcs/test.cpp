#include <iostream>
#include <string>
#include <chrono>

#include "tests.hpp"

using std::string;

typedef struct results {
	bool vector;
	bool map;
	bool stack;
	bool set;
} results;

void printResult(string container, bool res) {
	usleep(SLEEP_DURATION);
	std::cout << container << ": ";
	if (res)
		std::cout << "SUCCESS" << std::endl;
	else
		std::cout << "FAILURE" << std::endl;
}

int main() {
	results res;

	std::cout << "Test Starts." << std::endl;

	res.vector = testVector();
	// res.map = testMap();
	// res.stack = testStack();
	// res.set = testSet();

	usleep(SLEEP_DURATION);
	std::cout << "Test Result:" << std::endl;
	printResult("Vector", res.vector);
	// printResult("Map", res.map);
	// printResult("Stack", res.stack);
	// printResult("Set", res.set);
}