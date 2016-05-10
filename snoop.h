// _SNOOP_H_
#ifndef _SNOOP_H_
#define _SNOOP_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <queue>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>

#include "cache.h"
#include "protocol.h"
#include "memops.h"
#include "snoop_config.h"

#define READ 1
#define WRITE 2
#define RESPONSE 3
#define WRITEBACK 4

#define MEM -1

using namespace std;

class Snoop {
public:
	Snoop();
    ~Snoop();
    void Run();

private:
    class BusObj
    {
    public:
        BusObj(int op, int wait_cycles, int src, int dest, long address,
               bool exclusive_response);
    
        int op;
        int wait_cycles;
        int src;
        int dest;
        long address;
        bool exclusive_response;
    };

    queue<BusObj> bus;
    queue<int> req_buffer;
    vector<MemOps*> processor_ops;
    vector<Cache_Base*> caches;
    vector<bool> pending;
    Protocol* ptc;
    vector<int> random_selector;

    void resume(int id, BusObj & bus_obj, bool exclusive);
    void access_writeback_updatestate(int id, long address, int src,
                                      bool exclusive = false);
};

#endif // _SNOOP_H_