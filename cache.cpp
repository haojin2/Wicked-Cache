// _CACHE_CPP_
#include "cache.h"
#include <iostream>

using namespace std;

size_t powerof2(size_t input){
	int count = -1;
	if (input == 0){
		return input;
	}
	while (input > 0){
		count += 1;
		input = input >> 1;
	}
	return (size_t)(0x1<<count);
}

size_t log2(size_t input){
	int count = -1;
	if (input == 0)
	{
		return input;
	}
	while (input > 0){
		count += 1;
		input = input >> 1;
	}
	return (size_t)(count);
}

