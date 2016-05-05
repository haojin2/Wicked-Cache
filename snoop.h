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

#include "snoop_config.h"
#include "cache.h"
#include "protocol.h"
#include "memops.h"

#define RESPONSE 0
#define MEM -1

using namespace std;

class Snoop {
public:
	Snoop(){
		cout<<"Snoop constructor"<<endl;
        ptc = new PROTOCOL_TYPE();
        for (int i = 0; i < NUM_PROCESSORS; ++i)
        {
            caches.push_back(new CACHE_TYPE(CACHE_SIZE, CACHE_NUM_WAYS, CACHE_BLOCK_SIZE));
            processor_ops.push_back(MemOps("access_pattern_"+i.tostring()+".txt"));
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
    queue<int> reqBuffer;
    vector<MemOps> processor_ops;
    vector<Cache_Base*> caches;
    Protocol* ptc;
};

#endif // _SNOOP_H_