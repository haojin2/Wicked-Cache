// CACHE_H_
#ifndef _CACHE_H_
#define _CACHE_H_
#include <vector>
#include <queue>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h> 

using namespace std;

size_t powerof2(size_t input);

size_t log2(size_t input);

class Cache_Base{
public:
	Cache_Base(){
		cout<<"Base constructor"<<endl;
	}
	Cache_Base(size_t size, size_t way = 1, size_t block_size = 1){
		this->size = powerof2(size) * 1024;
		if (way > this->size){
			this->way = this->size / 2;
		}
		else{
			this->way = powerof2(way);
		}
		block_size = powerof2(block_size);
		if (this->way * block_size > this->size){
			this->block_size = this->size / this->way;
		}
		else{
			this->block_size = block_size;
		}
		entries = vector<long>(this->size, -1);
		tag_mask = 0xffffffffffffffff << (log2(this->block_size) + log2(this->size / this->way));
		index_mask = ((size_t)0xffffffffffffffff) ^ tag_mask;
		cout<<size<<" kb with "<<way<<"-way associative"<<" with block size of "<<this->block_size<<endl;
	}
	virtual bool access(size_t address){}
protected:
	inline size_t _get_tag(size_t address){
		return (tag_mask & address) >> (log2(this->block_size) + log2(this->size / this->way));
	}
	inline size_t _get_index(size_t address){
		return (index_mask & address) >> log2(this->block_size);
	}
	size_t tag_mask;
	size_t index_mask;
	size_t block_size;
	size_t size;
	size_t way;
	vector<long> entries;
};

class LRU: public Cache_Base{
public:
	LRU(){
		cout<<"LRU"<<endl;
	}
	bool access(size_t address){
		return true;
	}
private:
	
};

class Random: public Cache_Base{
public:
	Random(){
		cout<<"Random"<<endl;
	}
	Random(size_t size, size_t way = 1, size_t block_size = 1)
	: Cache_Base(size, way, block_size){
		return;
	}
	bool access(size_t address){

		size_t index = _get_index(address);
		size_t tag = _get_tag(address);
		if (way != 1){
			for (size_t i = 0; i < way; ++i){
				if (entries[index * way + i] == (long)tag){
					return true;
				}
				if (entries[index * way + i] == (long)-1){
					entries[index * way + i] = (long)tag;
					return false;
				}
			}
			size_t victum = rand() % way;
			entries[index * way + victum] = (long)tag;
			return false;
		}
		else{
			if (entries[index] == (long)tag){
				return true;
			}
			else{
				entries[index] = (long)tag;
				return false;
			}
		}
	}
private:
	
};

#endif
