// MOESI_H_
#ifndef _MOESI_H_
#define _MOESI_H_
#include "protocol.h"

using namespace std;

class moesi: public protocol{
public:
	moesi(){
		cout<<"MOESI constructor"<<endl;
	}
    ~moesi(){
        cout<<"MOESI destructor"<<endl;
    }
	char next_state(int operation, char curr_state){
        switch(curr_state){
        	case 'm' : 
        	    switch(operation){
                    case 0: return 'm';
                    case 1: return 'm';
                    case 2: return 'o';
                    case 3: return 'i';
           	    }                    

        	case 'o' :
        	    switch(operation){
                    case 0: return 'o';
                    case 1: return 'm';
                    case 2: return 'o';
                    case 3: return 'i';                  
        	    }
        	case 'e' :
        	    switch(operation){
                    case 0: return 'e';
                    case 1: return 'm';
                    case 2: return 's';
                    case 3: return 'i';
        	    }
        	case 's' :
        	    switch(operation){
                    case 0: return 's';
                    case 1: return 'm';
                    case 2: return 's';
                    case 3: return 'i';
        	    }
        	case 'i' :
        	    switch(operation){
                    case 0: return 'e';
                    case 1: return 'm';
                    case 2: return 'i';
                    case 3: return 'i';
        	    }        	    
        }
	}
private:
};
