// CACHE_H_
#ifndef _CACHE_H_
#define _CACHE_H_
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

bool powerof2(size_t input);

class Cache_Base{
public:
	Cache_Base(){
		cout<<"Base constructor"<<endl;
	}
	Cache_Base(size_t size){
		this->way = 1;
		this->size = powerof2(size);
		cout<<size<<" kb"<<endl;
		entries = vector<unsigned long>(size * 1024, 0);
	}
	Cache_Base(size_t size, size_t way){
		this->size = powerof2(size);
		if (way > size){
			this->way = size;
		}
		else{
			this->way = powerof2(way);
		}
		cout<<size<<" kb with "<<way<<" associative"<<endl;
	}
	virtual bool read(size_t address);
	virtual bool write(size_t address);
protected:
	size_t size;
	size_t way;
	vector<unsigned long> entries;
};

class LRU: public Cache_Base{
	LRU(){
		cout<<"LRU"<<endl;
	}
	LRU(size_t size){

	}
	LRU(size_t size, size_t way){

	}
	bool read(size_t address){

	}
	bool write(size_t address){

	}
private:
	
};

class Random: public Cache_Base{
public:
	Random(){
		cout<<"Random"<<endl;

	}
	Random(size_t size){

	}
	Random(size_t size, size_t way){
		
	}
	bool read(size_t address){

	}
	bool write(size_t address){
		
	}
private:
	
);
#endif
