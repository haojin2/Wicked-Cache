// MOSI_H_
#ifndef _MOSI_H_
#define _MOSI_H_
#include "protocol.h"
#define BUS_READ_CACHE 0
#define BUS_WRITE 1
#define PROC_READ 2
#define PROC_WRITE 3
#define BUS_READ_MEM 4

using namespace std;

class mosi: public Protocol{
public:
	mosi(){
		cout<<"MOSI constructor"<<endl;
	}
    ~mosi(){
        cout<<"MOSI destructor"<<endl;
    }
	char next_state(int operation, char curr_state){
		char output;
        switch(curr_state){
        	case 'm' :{ 
        	    switch(operation){
                    case 0: output = 'o';break;
                    case 1: output = 'i';break;
                    case 2: output = 'm';break;
                    case 3: output = 'm';break;
					default: cout<<"invalid operation"<<endl; break; // case 4 is impossible
           	    }
                break;
            }
        	case 'o' :{
        	    switch(operation){
                    case 0: output = 'o';break;
                    case 1: output = 'i';break;
                    case 2: output = 'o';break;
                    case 3: output = 'm';break;
					default: cout<<"invalid operation"<<endl; break; // case 4 is impossible
        	    }
                break;
            }
        	case 's' :{
        	    switch(operation){
                    case 0: output = 's';break;
                    case 1: output = 'i';break;
                    case 2: output = 's';break;
                    case 3: output = 'm';break;
					default: cout<<"invalid operation"<<endl; break; // case 4 is impossible
        	    }
                break;
            }
        	case 'i' :{
        	    switch(operation){
                    case 0: output = 's';break;
                    case 1: output = 'm';break;
                    //case 2: output = 's';break;  //impossible state
                    //case 3: output = 'm';break;  //impossible state
                    case 4: output = 's';break;
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
#endif // _MOSI_H_
