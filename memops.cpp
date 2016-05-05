#include "memops.h"

MemOps::MemOps(string filename){
	cout<<"MemOps constructor"<<endl;
    file = fopen(filename.c_str(), "r");
    if (file == NULL)
        cout << "MemOps: Cannot open file " << filename << endl;
    else
        getNextOp();
}

MemOps::~MemOps(){
    cout<<"MemOps destructor"<<endl;
    if (file)
        fclose(file);
}

void MemOps::getNextOp(){
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