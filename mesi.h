// MESI_H_
#ifndef _MESI_H_
#define _MESI_H_
#include "protocol.h"
#define BUS_READ 0
#define BUS_WRITE 1
#define PROC_READ 2
#define PROC_WRITE 3
using namespace std;

class mesi: public protocol{
public:
	mesi(){
		cout<<"MESI constructor"<<endl;
	}
    ~mesi(){
        cout<<"MESI destructor"<<endl;
    }
	char next_state(int operation, char curr_state){
		char output;
        switch(curr_state){
        	case 'm' :{ 
        	    switch(operation){
                    case 0: output = 's';break;
                    case 1: output = 'i';break;
                    case 2: output = 'm';break;
                    case 3: output = 'm';break;
					default: cout<<"invalid operation"<<endl; break;
           	    }
                break;
            }
        	case 'e' :{
        	    switch(operation){
                    case 0: output = 's';break;
                    case 1: output = 'i';break;
                    case 2: output = 'e';break;
                    case 3: output = 'm';break;
					default: cout<<"invalid operation"<<endl; break;
        	    }
                break;
            }
        	case 's' :{
        	    switch(operation){
                    case 0: output = 's';break;
                    case 1: output = 'i';break;
                    case 2: output = 's';break;
                    case 3: output = 'm';break;
					default: cout<<"invalid operation"<<endl; break;
        	    }
                break;
            }
        	case 'i' :{
        	    switch(operation){
                    case 0: output = 'i';break;
                    case 1: output = 'i';break;
                    case 2: output = 'e';break;
                    case 3: output = 'm';break;
					default: cout<<"invalid operation"<<endl; break;
        	    }
                break;
            }
            default: cout<<"invalid curr state"<<endl; break;
        }
        return output;
	}
private:
};
