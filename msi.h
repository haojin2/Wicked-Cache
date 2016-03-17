// _MSI_H_
#include "protocol.h"
#define BUS_READ 0
#define BUS_WRITE 1
#define PROC_READ 2
#define PROC_WRITE 3

class msi: public protocol{
public:
	msi(){
		cout<<"MSI constructor\n";
	}
	~msi(){
		cout<<"MSI destructor\n";
	}

	inline char next_state(int operation, char curr_state){
		char output;
		switch (curr_state){
			case 'm':{
				switch (operation){
					case 0: output = 's';break;
					case 1: output = 'i';break;
					case 2: output = 'm';break;
					case 3: output = 'm';break;
					default: cout<<"invalid operation"<<endl; break;
				}
				break;
			}
			case 's':{
				switch (operation){
					case 0: output = 's';break;
					case 1: output = 'i';break;
					case 2: output = 's';break;
					case 3: output = 'm';break;
					default: cout<<"invalid operation"<<endl; break;
				}
				break;
			}
			case 'i':{
				switch (operation){
					case 0: output = 'i';break;
					case 1: output = 'i';break;
					case 2: output = 'i';break;
					case 3: output = 'i';break;
					default: cout<<"invalid operation"<<endl; break;
				}
				break;
			}
			default: cout<<"invalid curr state"<<endl; break;
		}
		return output;
	}

	/* data */
};