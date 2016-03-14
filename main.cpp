#include "cache.h"
#include <iostream>

using namespace std;

int main(){
	Cache_Base * temp;
	srand(time(NULL));
	temp = new Random(64, 4, 4);
	cout<<temp->access(0x0000000000000000)<<endl;
	cout<<temp->access(0x0000000000000001)<<endl;
	cout<<temp->access(0x0000001000000003)<<endl;
	cout<<temp->access(0x0000001000000001)<<endl;
	cout<<temp->access(0x0000001100000002)<<endl;
	cout<<temp->access(0x0000001100000002)<<endl;
	cout<<temp->access(0x0000000000000000)<<endl;
	delete temp;
	return 0;
}