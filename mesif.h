// MESIF_H_
#ifndef _MESIF_H_
#define _MESIF_H_
#include "protocol.h"

using namespace std;

class mesif: public Protocol{
public:
	mesif(){
		cout<<"MESIF constructor"<<endl;
	}
    ~mesif(){
        cout<<"MESIF destructor"<<endl;
    }
	tuple<char, bool, bool> next_state(int operation, char curr_state){
		char output;
		bool write_back = false;
		bool respond = false;
        switch(curr_state){
        	case 'm' :{ 
				switch (operation){
					case PROC_READ_FROM_CACHE: output = 'm'; break;
					// case PROC_READ_FROM_MEM:   output = 'm'; break; /* impossible state */
					case PROC_WRITE:           output = 'm'; break;
					case BUS_READ:             output = 's'; write_back = true; respond = true; break;
                    case BUS_WRITE:            output = 'i'; write_back = false; respond = false; break;
					default: cout<<"invalid operation"<<endl; break;
				}
				break;
            }
        	case 'e' :{
				switch (operation){
					case PROC_READ_FROM_CACHE: output = 'e'; break;
					// case PROC_READ_FROM_MEM:   output = 's'; break; /* impossible state */
					case PROC_WRITE:           output = 'm'; break;
					case BUS_READ:             output = 's'; write_back = false; respond = true; break;
                    case BUS_WRITE:            output = 'i'; write_back = false; respond = false; break;
					default: cout<<"invalid operation"<<endl; break;
				}
				break;
            }
        	case 's' :{
				switch (operation){
					case PROC_READ_FROM_CACHE: output = 's'; break;
					// case PROC_READ_FROM_MEM:   output = 's'; break; /* impossible state */
					case PROC_WRITE:           output = 'm'; break;
					case BUS_READ:             output = 's'; write_back = false; respond = false; break;
                    case BUS_WRITE:            output = 'i'; write_back = false; respond = false; break;
					default: cout<<"invalid operation"<<endl; break;
				}
				break;
            }
        	case 'i' :{
				switch (operation){
					case PROC_READ_FROM_CACHE: output = 'f'; break;
					case PROC_READ_FROM_MEM:   output = 'e'; break;
					case PROC_WRITE:           output = 'm'; break;
					case BUS_READ:             output = 'i'; write_back = false; respond = false; break;
                    case BUS_WRITE:            output = 'i'; write_back = false; respond = false; break;
					default: cout<<"invalid operation"<<endl; break;
				}
				break;
            }
        	case 'f' :{
				switch (operation){
					case PROC_READ_FROM_CACHE: output = 'f'; break;
					// case PROC_READ_FROM_MEM:   output = 's'; break; /* impossible state */
					case PROC_WRITE:           output = 'm'; break;
					case BUS_READ:             output = 's'; write_back = false; respond = true; break;
                    case BUS_WRITE:            output = 'i'; write_back = false; respond = false; break;
					default: cout<<"invalid operation"<<endl; break;
				}
				break;
            }
            default: cout<<"invalid curr state"<<endl; break;
        }
        return make_tuple(output, write_back, respond);
	}

	bool hit(int operation, char curr_state){
		bool hit;
		switch (curr_state){
			case 'm':{
				hit = true;
				break;
			}
			case 'e':{
				hit = true;
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
			case 'f':{
				hit = (operation == READ);
				break;
			}
			default: cout<<"invalid curr state"<<endl; break;
		}
		return hit;
	}

	bool dirty(char state){
		return state == 'm';
	}

private:
};
#endif // _MESIF_H_
