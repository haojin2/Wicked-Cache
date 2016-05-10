// _MEMOPS_H_
#ifndef _MEMOPS_H_
#define _MEMOPS_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define READ 1
#define WRITE 2

using namespace std;

class MemOps {
public:
	MemOps(string filename);
    ~MemOps();
	void getNextOp();

// private:
    FILE * file;
    int wait_cycles;
    int op;
    long address;
};

#endif // _MEMOPS_H_