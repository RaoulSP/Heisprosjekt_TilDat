#include "order_overview.h"
#include "elev.h"

int orders[4][3] = {{0}};
int orders_amount = 0;

void oov_set_order(int floor_nr, int button, int value){
	//Neste linje sjekker om knappen ikke er en av de to ugyldige knappene, OG om bestillingen ikke allerede har den verdien
	if(!((floor_nr == 0 && button == BUTTON_CALL_DOWN) || (floor_nr == 3 && button == BUTTON_CALL_UP)) && orders[floor_nr][button] != value){
		orders[floor_nr][button] = value;
		elev_set_button_lamp(button, floor_nr, value);
		orders_amount += (-1 + 2*value); 				//Øker med 1 hvis det blir gjort en bestilling. Minker med 1 dersom en bestilling slettes 
	}
}

int oov_get_order(int floor_nr, int button){
	return orders[floor_nr][button];	
}

void oov_reset_floor_orders(int floor_nr){
		for(int button = 0; button < 3; button++){
			oov_set_order(floor_nr, button, 0);
		}
}

void oov_reset_all_orders(){
	for(int floor_nr = 0; floor_nr < 4; floor_nr++){
		oov_reset_floor_orders(floor_nr);
	}
}

int oov_get_amount(){
	return orders_amount;
}