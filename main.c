#include <stdio.h>
#include "elev.h"
#include "finite_state_machine.h"
#include "order_overview.h"

enum state current_state = initialize;

int main() {

    while (current_state != exit) {
	    current_state = fsm_run(current_state);	
    }
    return 1;
    
}