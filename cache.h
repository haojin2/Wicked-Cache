// CACHE_H_
#ifndef CACHE_H
#define CACHE_H
#include <vector>
#include <iostream>
using namespace std;
class cache_Base{
public:
	cache_Base(){
		cout<<"Base constructor"<<endl;
	}
	cache_Base(size_t size){
		cout<<"base constructor"<<endl;
		entries = vector<unsigned long>(size * 1024, 0);
				
	}
	virtual bool read(size_t address);
	virtual bool write(size_t address);
private:
	size_t size;
	vector<unsigned long> entries;	
}
#endif
