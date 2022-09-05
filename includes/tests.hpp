#pragma once

#include <time.h>
#include <memory>
#include <unistd.h>

#define SLEEP_DURATION 500000

using std::string;

/* tester */
int testVector();
int testMap();
int testSet();
int testStack();
int testPair();

/* utils */
int	printTimeResult(char *container, double realRes, double myRes);
