#include <iostream>
#include <string>
#include <chrono>

#include "tests.hpp"

typedef struct results {
	bool vector;
	bool map;
	bool set;
} results;

int main() {
	results res;

	std::cout << "Test Starts." << std::endl;

	res.vector = testVector();
	//res.map = testMap();

	std::cout << "Test Result:" << std::endl;
}