#include <iostream>
#include "mesi.h"
#include "msi.h"
#include "mosi.h"
#include "moesi.h"
#include "mesif.h"
#include <vector>
using namespace std;

int main(int argc, char ** argv){
	cout<<"test"<<endl;
    vector<char> states = {'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i'};
    Protocol * mesif_protocol;
    mesif_protocol = new mesif();
    vector<char> temp_states = {'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i'};
    int operation;
    int temp_operation;
    for(int i=0; i<20; i++){
        operation = rand()% 16;//even = read, odd = write, operations/2 = processor number
        cout << "operation: " << operation << endl;
        for(int j=0; j<8; j++){
            if(operation/2 == j){
                if(operation%2 == 0){
                    temp_operation = 2; // pro read
                }
                else{
                    temp_operation = 3; // pro write
                }
            }
            else{
                if(operation%2 == 0){
                    temp_operation = 0; // bus read
                }
                else{
                    temp_operation = 1; // bus write
                }                
            }
            temp_states[j] = mesif_protocol -> next_state(temp_operation, states[j], states);
        }
        for(int k=0; k<8; k++){
            states[k] = temp_states[k];
        }
        cout << "states: " << states[0] << " " << states[1] << " " << states[2] << " " << states[3] << " " << states[4] << " " << states[5] << " " << states[6] << " " << states[7] << endl; 
    }
	return 0;
}
