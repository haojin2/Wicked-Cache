#include "cache.h"
#include "snoop.h"
#include <iostream>

using namespace std;

int main(int argc, char ** argv){
	Cache_Base * temp;
	srand(time(NULL));
	if (argc < 2){
		return 1;
	}
	switch (argv[1][0]){
		case 'L':temp = new LRU(64, 4, 16);break;
		case 'R': temp = new Random(64, 4,16); break;
		// case 'M': temp = new MRU(64, 4, 16); break;
		default: break;
	}
	Snoop * new_snoop = new Snoop();
	new_snoop->Run();

	// cout<<temp->access(0x0000000000000000)<<endl;
	// cout<<temp->access(0x000000000000000F)<<endl;
	// // 0
	// cout<<temp->access(0x0000001000000001)<<endl;
	// cout<<temp->access(0x000000100000000F)<<endl;
	// // 1
	// cout<<temp->access(0x0000001100000002)<<endl;
	// cout<<temp->access(0x000000110000000F)<<endl;
	// // 2
	// cout<<temp->access(0x0000011100000003)<<endl;
	// cout<<temp->access(0x000001110000000F)<<endl;
	// // 3
	// cout<<temp->access(0x0000000100000000)<<endl;
	// // new 1
	// cout<<temp->access(0x0000001000000001)<<endl;
	// // 1
	// cout<<temp->access(0x0000010100000000)<<endl;
	// // new 2
	// delete temp;

	return 0;
}