// CACHE_H_
#ifndef _CACHE_H_
#define _CACHE_H_
#include <vector>
#include <iostream>
using namespace std;
class Cache_Base{
public:
	Cache_Base(){
		cout<<"Base constructor"<<endl;
	}
	Cache_Base(size_t size){
		cout<<size<<" kb"<<endl;
		entries = vector<unsigned long>(size * 1024, 0);
		this->size = size;	
	}
	Cache_Base(size_t size, size_t way){
		cout<<size<<" kb with "<<way<<" associative "<<endl;
		this->way = way;
		this->size = size;
	}
	virtual bool read(size_t address);
	virtual bool write(size_t address);
protected:
	size_t size;
	size_t way;
	vector<unsigned long> entries;
	
};
class LRU: public Cache_Base{
	
};
#endif
