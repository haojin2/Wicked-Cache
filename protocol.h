// _PROTOCOL_H_
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <iostream>
#include <stdlib.h>
#include <tuple>

#include "memops.h"

#define PROC_READ_FROM_CACHE 0
#define PROC_READ_FROM_MEM 1
#define PROC_WRITE 2
#define BUS_READ 3
#define BUS_WRITE 4

using namespace std;

class Protocol
{
public:
	Protocol();
	
	/* Returns (next_state, write_back?, respond?) */
	virtual tuple<char, bool, bool> next_state(int operation, char curr_state) = 0;
	virtual bool hit(int operation, char curr_state) = 0;

	int to_proc(int op, bool from_cache = true);
	int to_bus(int op);

private:

};

#endif // _PROTOCOL_H_
