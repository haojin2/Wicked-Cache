// MOSI_H_
#ifndef _MOSI_H_
#define _MOSI_H_
#include "protocol.h"

using namespace std;

class mosi: public Protocol{
public:
	mosi(){
		cerr<<"MOSI constructor"<<endl;
	}
    ~mosi(){
        cerr<<"MOSI destructor"<<endl;
    }
	tuple<char, bool, bool> next_state(int operation, char curr_state){
		char output;
		bool write_back = false;
		bool respond = false;
        switch(curr_state){
			case 'm':{
				switch (operation){
					case PROC_READ_FROM_CACHE: output = 'm'; break;
					// case PROC_READ_FROM_MEM:   output = 'm'; break; /* impossible state */
					case PROC_WRITE:           output = 'm'; break;
					case BUS_READ:             output = 'o'; write_back = false; respond = true; break;
                    case BUS_WRITE:            output = 'i'; write_back = false; respond = false; break;
				}
				break;
			}
			case 'o':{
				switch (operation){
					case PROC_READ_FROM_CACHE: output = 'o'; break;
					// case PROC_READ_FROM_MEM:   output = 's'; break; /* impossible state */
					case PROC_WRITE:           output = 'm'; write_back = true; break;
					case BUS_READ:             output = 'o'; write_back = false; respond = true; break;
                    case BUS_WRITE:            output = 'i'; write_back = true; respond = false; break;
				}
				break;
			}
			case 's':{
				switch (operation){
					case PROC_READ_FROM_CACHE: output = 's'; break;
					// case PROC_READ_FROM_MEM:   output = 's'; break; /* impossible state */
					case PROC_WRITE:           output = 'm'; break;
					case BUS_READ:             output = 's'; write_back = false; respond = true; break;
                    case BUS_WRITE:            output = 'i'; write_back = false; respond = false; break;
				}
				break;
			}
			case 'i':{
				switch (operation){
					case PROC_READ_FROM_CACHE: output = 's'; break;
					case PROC_READ_FROM_MEM:   output = 's'; break;
					case PROC_WRITE:           output = 'm'; break;
					case BUS_READ:             output = 'i'; write_back = false; respond = false; break;
                    case BUS_WRITE:            output = 'i'; write_back = false; respond = false; break;
					default: cerr<<"invalid operation"<<endl; break;
				}
				break;
			}
            default: cerr<<"invalid curr state"<<endl; break;
        }
        return tuple<char, bool, bool>(output, write_back, respond);
	}

	bool hit(int operation, char curr_state){
		bool hit;
		switch (curr_state){
			case 'm':{
				hit = true;
				break;
			}
			case 'o':{
				hit = (operation == READ);
				break;
			}
			case 's':{
				hit = (operation == READ);
				break;
			}
			case 'i':{
				hit = false;
				break;
			}
			default: cerr<<"invalid curr state"<<endl; break;
		}
		return hit;
	}

	bool dirty(char state){
		return state == 'm';
	}
private:
};
#endif // _MOSI_H_
