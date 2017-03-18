#include <stdio.h>
#include "elev.h"
#include "finite_state_machine.h"
#include "order_overview.h"

enum state current_state = start;

int main() {
    //Initialiser maskinvare
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    
    //Hovedloop
    while (1) {
	    current_state = fsm_run(current_state);	
    }
    return 0;
}