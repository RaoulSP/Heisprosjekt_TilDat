#include "order_overview.h"
#include "elev.h"

int orders[4][3] = {{0}};
int orders_amount = 0;

void oov_set_order(int floor_nr, int button, int value){
	//Neste linje sjekker om knappen ikke er en av de to ugyldige knappene, OG om bestillingen ikke allerede har den verdien
	if(!((floor_nr == 0 && button == 1) || (floor_nr == 3 && button == 0)) && orders[floor_nr][button] != value){			//OVERFLØDIG? når de to ugyldige også sjekkes i oov_set_new_orders?
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

int oov_get_order(int floor_nr, int button){	//change into get_floor_order?
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
//alternative 1, using a 1D array. Not completed, needs more work which follows through on the idea

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

void alt_oov_reset_all_orders(){					//Is this function necessary? Could just for-loop in the actual case, or even use the set-new-orders with a flag?
	for (int floor = 0; floor < 4; floor ++){
		alt_oov_set_order_at_floor(floor, -1);	//Is it possible to do something like this: int orders[4] = {-1} as when initialized above?
	}
}


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
*/




/*
//Various function alternatives/drafts:
//int orders[4][3] = {{0}}; 	2D array

void set_floor_orders(int floor_nr, int up, int down, int command){
		orders[floor_nr][button] = value;
		elev_set_button_lamp(button, floor_nr, value);
}

void set_floor_orders(int floor_nr, int up, int down, int command){
		for (int button = 0; button < 3; button ++){
			orders[floor_nr][button] = value;
			elev_set_button_lamp(button, floor_nr, value);
		}		
}

void check_all_buttons(){
	for (int floor = 0; floor < 4; floor++){
		set_floor_orders(floor_nr, elev_get_button_signal(0, floor_nr), elev_get_button_signal(1, floor_nr), elev_get_button_signal(2, floor_nr));
	}
}

void check_all_buttons(){
	for (int floor = 0; floor < 4; floor++){
		for (int button = (floor == 0); button < 3 - (floor == 4); button ++){
			if (elev_get_button_signal(button, floor)){
				set_floor_order
			}
		}
	}
}

void set_reset_floor(){
}

void get_floor_bool(int floor){
	return orders[floor][0] + orders[floor][1] + orders[floor][2];
}

//Possible examples of desired use
set_floor_orders(floor_nr, 0, 0, 0); //reset floor
get_floor_bool(floor_nr);
set_floor_orders(floor_nr, elev_get_button_signal(0, floor_nr), elev_get_button_signal(1, floor_nr), elev_get_button_signal(2, floor_nr));

*/




void set_single(floor, button, set){											//A function that works kind of like a set/reset latch to set a single order? So if the set flag is 1 then the value is set according to if the button is pressed. If the set flag is 0, the order is reset. Might work! following through on this concept below, with the other functions.
	if(!((floor == 0 && button == 1) || (floor == 3 && button == 0))){
		value = set && elev_get_button_signal(button, floor); 					//replaced * with &&. with * , does it check button signal too often? Does it call the button check when set is 0? With &&, will it abort after set == 0?
		if (orders[floor_nr][button] != value){		//Necessary? Nice to do
			orders[floor_nr][button] = value;
			elev_set_button_lamp(button, floor, value);
		}
	}
}

void set_floor(floor, set){
	for (button = 0; button < 3; button ++){
		set_single(floor, button, set);
	}
}

void set_all(set){																//define an enum SET RESET?
	for (floor = 0; floor < 4; floor ++){
		set_floor(floor, set);
	}
}

int get_floor(floor){
	int sum = 0;																//return boolean, return button type, or return direction type? What is the most elegant?
	for (button = 0; button < 3; button ++){
		sum += (button + 1) * (orders[floor_nr][button]);
	}
	return (sum - 1);															//Some trickery to have get_floor return 0 or 1 if only the up or down button has been stored, and 2 or more if command or multiple buttons have been stored.
}

int get_floor(floor){															//alternative
	int sum = 0;
	int last_button;
	for (button = 0; button < 3; button ++){
		if (orders[floor_nr][button]){
			sum += 1;
			last_button = button;
		}
	if (sum > 1){
		return 2;
	}
	else {
		return last_button;
	}
}

int check_along_dir(int from_floor, int along_dir){									//scan along direction? scan direction? Check partition? Scan ahead? Check in range? Any in range?
	for (int floor = from_floor; (floor >= 0 && floor < 4); floor += along_dir){
			if (get_floor(floor) > -1){
				return 1;
		}
	}
	return 0;
}


/*
// dirn = (button*(-2)+1), this can be used? For simplifying the assert condition

//if dirn ends up being -1 or 1, then you want to avoid first floor & -1, and upper floor & 1, so you don't want to exceed the floor numbers either way.

if(!((floor == 0 && button == 1) || (floor == 3 && button == 0))) //Original

// (floor + (-2 * button) + 1) has to be within the limits.

if((floor + (-2 * button) + 1) >= 0 && (floor + (-2 * button) + 1) < 4) //this is longer than what it was intended to replace, way more complicated, and doesn't even work because the command button gives false negatives.
*/