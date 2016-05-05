// CACHE_H_
#ifndef _CACHE_H_
#define _CACHE_H_
#include <vector>
#include <queue>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h> 
#include <unordered_map>
#include <utility>
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
			this->block_size = block_size;  // jin 
		}
		entries = vector<long>(this->size, -1);
		status = vector<char>(this->size, 'i');
		tag_mask = 0xffffffffffffffff << (log2(this->block_size) + log2(this->size / this->way));
		index_mask = ((size_t)0xffffffffffffffff) ^ tag_mask;
		cout<<size<<" kb with "<<way<<"-way associative"<<" with block size of "<<this->block_size<<endl;
	}

	virtual pair<bool,char> access(size_t address) = 0;

	bool peek(size_t address){
		size_t index = _get_index(address);
		size_t tag = _get_tag(address);
		if (way != 1){
			for (size_t i = 0; i < way; ++i){
				if (entries[index * way + i] == (long)tag){
					return true;
				}
			}
			return false;
		}
		else{
			if (entries[index] == (long)tag){
				return true;
			}
			else{
				return false;
			}
		}
		return false;
	}

	char get_status(size_t address){
		if (!peek(address)){
			return 'i';
		}
		else{
			size_t index = _get_index(address);
			size_t tag = _get_tag(address);
			if (way != 1){
				for (size_t i = 0; i < way; ++i){
					if (entries[index * way + i] == (long)tag){
						return status[index * way + i];
					}
				}
			}
			else{
				if (entries[index] == (long)tag){
					return status[index];
				}
			}
		}
		return 'i';
	}

	bool set_status(size_t address, char new_status){
		if (!peek(address)){
			return false;
		}
		else{
			size_t index = _get_index(address);
			size_t tag = _get_tag(address);
			if (way != 1){
				for (size_t i = 0; i < way; ++i){
					if (entries[index * way + i] == (long)tag){
						status[index * way + i] = new_status;
						return true;
					}
				}
			}
			else{
				if (entries[index] == (long)tag){
					status[index] = new_status;
					return true;
				}
			}
		}
		return false;
	}

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
	vector<char> status;
};

class LRU: public Cache_Base{
public:
	LRU(){
		cout<<"LRU"<<endl;
	}

	LRU(size_t size, size_t way = 1, size_t block_size = 1)
		: Cache_Base(size, way, block_size) {}

	pair<bool,char> access(size_t address){
		size_t index = _get_index(address);
		size_t tag = _get_tag(address);
		vector<size_t> & temp = usage_map[index];
		if (way != 1){
			for (size_t i = 0; i < way; ++i){
				if (entries[index * way + i] == (long)tag){
					for (size_t j = temp.size() - 1; j >= 0; --j){
						if (temp[j] == i){
							temp.erase(temp.begin()+j);
							temp.push_back(i);
							cout<<"hit "<<i<<" , ";
							for(size_t k = 0; k < temp.size(); k++){
								cout<<temp[k]<<" ";
							}
							cout<<endl;
							break;
						}
					}
					return pair<bool,char>(true, status[index * way + i]);
				}
				if (entries[index * way + i] == (long)-1){
					entries[index * way + i] = (long)tag;
					temp.push_back(i);
					cout<<"warmup miss, ";
					for(size_t k = 0; k < temp.size(); k++){
						cout<<temp[k]<<" ";
					}
					cout<<endl;
					return pair<bool,char>(false, status[index * way + i]);
				}
			}
			size_t victim = temp[0];
			temp.erase(temp.begin());
			temp.push_back(victim);
			entries[index * way + victim] = (long)tag;
			cout<<"simply miss "<<endl;
			for(size_t k = 0; k < temp.size(); k++){
				cout<<temp[k]<<" ";
			}
			return pair<bool,char>(false, status[index * way + victim]);
		}
		else{
			if (entries[index] == (long)tag){
				return pair<bool,char>(true, status[index]);
			}
			else{
				entries[index] = (long)tag;
				return pair<bool,char>(false, status[index]);
			}
		}
	}

private:
	unordered_map<size_t, vector<size_t>> usage_map;
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

	pair<bool,char> access(size_t address){
		size_t index = _get_index(address);
		size_t tag = _get_tag(address);
		if (way != 1){
			for (size_t i = 0; i < way; ++i){
				if (entries[index * way + i] == (long)tag){
					return pair<bool,char>(true, status[index * way + i]);
				}
				if (entries[index * way + i] == (long)-1){
					entries[index * way + i] = (long)tag;
					return pair<bool,char>(false, status[index * way + i]);
				}
			}
			size_t victim = rand() % way;
			entries[index * way + victim] = (long)tag;
			return pair<bool,char>(false, status[index * way + victim]);
		}
		else{
			if (entries[index] == (long)tag){
				return pair<bool,char>(true, status[index]);
			}
			else{
				entries[index] = (long)tag;
				return pair<bool,char>(false, status[index]);
			}
		}
	}
	
private:
	
};

#endif
