#include "snoop.h"
#include <iostream>

using namespace std;

int main(int argc, char ** argv){

	Snoop * new_snoop = new Snoop();
	new_snoop->Run();
	delete new_snoop;

	return 0;
}