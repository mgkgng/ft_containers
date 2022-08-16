#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>

#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"

int main() {
	ft::vector<int> myVector;
	std::vector<int> realVector;

	myVector.push_back(345);
	std::cout << "let's see" << myVector.at(0) << std::endl;

}