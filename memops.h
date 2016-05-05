// MEMOPS_H_
#ifndef MEMOPS_H_
#define MEMOPS_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define READ 1
#define WRITE 2
// #define READEX 3

using namespace std;

class MemOps {
public:
	MemOps(string filename){
		cout<<"MemOps constructor"<<endl;
        file = fopen(filename.c_str(), "r");
        if (file == NULL)
            cout << "MemOps: Cannot open file " << filename << endl;
        else
            getNextOp();
	}

    ~MemOps(){
        cout<<"MemOps destructor"<<endl;
        if (file)
            fclose(file);
    }

	void getNextOp(){
        assert(file != NULL);

        char* line;
        size_t len;
        if (-1 != getline(&line, &len, file)) {
            if (3 > sscanf(line, "%d %d %x", &wait_cycles, &op, &address))
                cout << "MemOps: Scanning line failed." << endl;
            free(line);
        } else {
            wait_cycles = -1;
        }
    }

private:
    FILE * file;
    int wait_cycles;
    int op;
    long address;
};

#endif // _MEMOPS_H_