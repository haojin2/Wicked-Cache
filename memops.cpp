#include "memops.h"

MemOps::MemOps(string filename){
	cerr<<"MemOps constructor"<<filename<<endl;
    file = fopen(filename.c_str(), "r");
    if (file == NULL)
        cerr << "MemOps: Cannot open file " << endl;
    else
        getNextOp();
}

MemOps::~MemOps(){
    cerr<<"MemOps destructor"<<endl;
    fclose(file);
    free(line);
}

void MemOps::getNextOp(){
    size_t len;
    if (-1 != getline(&line, &len, file)) {
        if (3 > sscanf(line, "%d %d %x", &wait_cycles, &op, &address))
            cerr << "MemOps: Scanning line failed." << endl;
    } else {
        op = address = wait_cycles = -1;
    }
}