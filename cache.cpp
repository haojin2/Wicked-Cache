// _CACHE_CPP_
#include "cache.h"
#include <iostream>

using namespace std;

size_t powerof2(size_t input){
	int count = 0;
	while (input > 0){
		count += 1;
		input = input >> 1;
	}
	return (0x1<<count);
}

