// _SNOOP_H_
#ifndef _SNOOP_H_
#define _SNOOP_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <queue>
#include <vector>
#include <tuple>
#include <utility>

#include "snoop_config.h"
#include "cache.h"
#include "protocol.h"
#include "memops.h"

#define READ 1
#define WRITE 2
#define RESPONSE 3
#define WRITEBACK 4

#define MEM -1

using namespace std;

class Snoop {
public:
	Snoop(){
		cout<<"Snoop constructor"<<endl;
        ptc = new PROTOCOL_TYPE();
        for (int i = 0; i < NUM_PROCESSORS; ++i)
        {
            processor_ops.push_back(MemOps("access_pattern_"+i.tostring()+".txt"));
            caches.push_back(new CACHE_TYPE(CACHE_SIZE, CACHE_NUM_WAYS, CACHE_BLOCK_SIZE));
            pending.push_back(false);
        }
	}

    ~Snoop(){
        cout<<"Snoop destructor"<<endl;
        delete ptc;
        for (int i = 0; i < NUM_PROCESSORS; ++i)
            delete caches[i];
    }

    void Run();

private:
    class BusObj
    {
    public:
        BusObj(int op, int wait_cycles, int src, int dest, long address) {
            this->op = op;
            this->wait_cycles = wait_cycles;
            this->src = src;
            this->dest = dest;
            this->address = address;
        };
    
        int op;
        int wait_cycles;
        int src;
        int dest;
        long address;
    };

    queue<BusObj> bus;
    queue<int> req_buffer;
    vector<MemOps> processor_ops;
    vector<Cache_Base*> caches;
    vector<bool> pending;
    Protocol* ptc;

    void resume(int id, BusObj & response);
    void access_writeback_updatestate(int id, long address, int src);
};

#endif // _SNOOP_H_