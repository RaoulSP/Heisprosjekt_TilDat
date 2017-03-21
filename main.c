#include "finite_state_machine.h"

state current_state = initialize;

int main() {

    while (current_state != abort) {
	    current_state = fsm_run(current_state);	
    }
    return 1;
    
}