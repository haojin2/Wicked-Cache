#include "memops.h"

MemOps::MemOps(string filename) : wait_cycles(0), op(0), address(0) {
	cerr <<"MemOps constructor with file: "<< filename << endl;
    file = fopen(filename.c_str(), "r");
    if (file == NULL)
        cerr << "MemOps: Cannot open file " << endl;
    else
        get_next_op();
}

MemOps::~MemOps(){
    cerr << "MemOps destructor" << endl;
    fclose(file);
}

void MemOps::get_next_op(){
    size_t len = 0;
    char* line = NULL;
    if (-1 != getline(&line, &len, file)) {
        if (3 > sscanf(line, "%d %d %x", &wait_cycles, &op, &address)) {
            cerr << "MemOps: Scanning line failed." << endl;
            op = address = wait_cycles = -1;
        }
    } else {
        op = address = wait_cycles = -1;
    }
    free(line);
}