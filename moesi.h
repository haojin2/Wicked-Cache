// MOESI_H_
#ifndef _MOESI_H_
#define _MOESI_H_
#include "protocol.h"
#define BUS_READ_CACHE 0
#define BUS_WRITE 1
#define PROC_READ 2
#define PROC_WRITE 3
#define BUS_READ_MEM 4
using namespace std;

class moesi: public Protocol{
public:
	moesi(){
		cout<<"MOESI constructor"<<endl;
	}
    ~moesi(){
        cout<<"MOESI destructor"<<endl;
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
        	case 'e' :{
        	    switch(operation){
                    case 0: output = 's';break;
                    case 1: output = 'i';break;
                    case 2: output = 'e';break;
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
                    //case 2: output = 'i';break;  //impossible state
                    //case 3: output = 'm';break;  //impossible state
                    case 4: output = 'e';break;
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

#endif // _MOESI_H_
