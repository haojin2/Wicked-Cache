// PROTOCOL_H_
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_
#include <vector>
#include <queue>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <unordered_map>
#include <utility>

using namespace std;

class Protocol
{
public:
	Protocol(){
		cout<<"protocol"<<endl;
	}
	virtual char next_state(int operation, char curr_state){}
private:
};

#endif // _PROTOCOL_H_
