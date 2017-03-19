#include "order_overview.h"
#include "elev.h"

int orders[4][3] = {{0}};
int orders_amount = 0;

void oov_set_order(int floor_nr, int button, int value){
	//Neste linje sjekker om knappen ikke er en av de to ugyldige knappene, OG om bestillingen ikke allerede har den verdien
	if(!((floor_nr == 0 && button == BUTTON_CALL_DOWN) || (floor_nr == 3 && button == BUTTON_CALL_UP)) && orders[floor_nr][button] != value){			//OVERFLØDIG? når de to ugyldige også sjekkes i oov_set_new_orders?
		orders[floor_nr][button] = value;
		elev_set_button_lamp(button, floor_nr, value);
		orders_amount += (-1 + 2*value); 				//Øker med 1 hvis det blir gjort en bestilling. Minker med 1 dersom en bestilling slettes 
	}
}

void oov_set_new_orders(){						//Implementer reset-flagg?
	for(int floor = 0; floor < 4; floor++){
		for(int button = 0; button < 3; button++){
			if(!((floor == 0 && button == 1) || (floor == 3 && button == 0)) && elev_get_button_signal(button, floor)){ //Ikke sjekk ned og opp i henholdsvis 1. og 4. etasje
    			oov_set_order(floor, button, 1);	  				
			}
		}
	}
}

int oov_get_order(int floor_nr, int button){
	return orders[floor_nr][button];	
}

int oov_get_amount(){
	return orders_amount;
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

int oov_check_orders_along_dir(int from_floor, int along_dir){
	for (int floor = from_floor; (floor >= 0 && floor < 4); floor += along_dir){
		for(int button = 0; button < 3; button++){
			if (oov_get_order(floor, button)) {
				return 1;
			}
		}
	}
	return 0;
}

/*
//
//replacement oov functions:

int orders[4] = {-1};

void alt_oov_set_order_at_floor(int floor_nr, int value){
	orders[floor_nr] = value;
}

int alt_oov_get_order_at_floor(int floor_nr){
	return orders[floor_nr];
}

int alt_oov_check_along_direction(int from_floor, int along_dir){
	for (int floor = from_floor; (floor >= 0 && floor < 4); floor+= along_dir){
		if (alt_oov_get_order_at_floor(floor) > -1){ 								//just return the result of the if? Oh, no. 0 at a floor returns early
			return 1;
		}
	}
	return 0;
}

void alt_oov_check_buttons_and_set_new_orders(){
	for(int floor = 0; floor < 4; floor++){
		for(int button = 0; button < 3; button++){
			if(!((floor == 0 && button == 1) || (floor == 3 && button == 0)) && elev_get_button_signal(button, floor)){ //Ikke sjekk ned og opp i henholdsvis 1. og 4. etasje
    			alt_oov_set_order_at_floor(floor, button);
			}
		}
	}
}

/*
void alt_oov_reset_orders_at_floor(int floor_nr){ 	//Just to show that this function is now unnecessary
	alt_oov_set_order_at_floor(floor_nr, -1);		//<-- this function can be called directly
}
*/

/*
void alt_oov_reset_all_orders(){					//Is this function necessary? Could just for-loop in the actual case, or even use the set-new-orders with a flag?
	for (int floor = 0; floor < 4; floor ++){
		alt_oov_set_order_at_floor(floor, -1);	//Is it possible to do something like this: int orders[4] = {-1} as when initialized above?
	}
}
*/
/*
void alt_oov_check_buttons_at_floor(int floor_nr){
	for (int button = 0; button < 3; button ++){
		if (elev_get_button_signal(button, floor_nr)){
			elev_set_button_lamp(button, floor_nr, 1);
		}
	}
}

void alt_oov_set_all_floors(int value){				//Can use as reset, with value -1
	for (int floor = 0; floor < 4; floor ++){
		alt_oov_set_order_at_floor(floor, value);
	}
}



/*
//another set of functions, this time just simple optimization of the original ones

int orders[4][3] = {{0}};
int orders_amount = 0;

void oov_set_order(int floor_nr, int button, int value){
	//Neste linje sjekker om knappen ikke er en av de to ugyldige knappene, OG om bestillingen ikke allerede har den verdien
	if(!((floor_nr == 0 && button == 1) || (floor_nr == 3 && button == BUTTON_CALL_UP)) && orders[floor_nr][button] != value){			//OVERFLØDIG? når de to ugyldige også sjekkes i oov_set_new_orders?
		orders[floor_nr][button] = value;
		elev_set_button_lamp(button, floor_nr, value);
		orders_amount += (-1 + 2*value); 				//Øker med 1 hvis det blir gjort en bestilling. Minker med 1 dersom en bestilling slettes 
	}
}

void oov_set_new_orders(){						//Implementer reset-flagg?
	for(int floor = 0; floor < 4; floor++){
		for(int button = 0; button < 3; button++){
			if(!((floor == 0 && button == 1) || (floor == 3 && button == 0)) && elev_get_button_signal(button, floor)){ //Ikke sjekk ned og opp i henholdsvis 1. og 4. etasje
    			oov_set_order(floor, button, 1);	  				
			}
		}
	}
}

int oov_get_floor_order(int floor_nr, int button){
	for (button = 0; button < 3; button ++){

	}
	return orders[floor_nr][button];	
}

int oov_get_amount(){
	return orders_amount;
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

int oov_check_orders_along_dir(int from_floor, int along_dir){
	for (int floor = from_floor; (floor >= 0 && floor < 4); floor += along_dir){
		for(int button = 0; button < 3; button++){
			if (oov_get_order(floor, button)) {
				return 1;
			}
		}
	}
	return 0;
}

*/
