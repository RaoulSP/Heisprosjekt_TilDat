#include "order_overview.h"
#include "elev.h"

int orders[4][3] = {{0}};
int orders_amount = 0;

void oov_set_order(int floor, int button, int set){
	if(!((floor == 0 && button == 1) || (floor == 3 && button == 0))){ //Ignorerer de to ugyldige knappene
		value = set && elev_get_button_signal(button, floor);
		if (orders[floor][button] != value){
			orders[floor][button] = value;
			elev_set_button_lamp(button, floor, value);
			orders_amount += (-1 + 2 * value); //Øker med 1 hvis det blir gjort en bestilling. Minker med 1 dersom en bestilling slettes 
		}
	}
}

void oov_set_floor_orders(int floor, int set){
	for (int button = 0; button < 3; button ++){
		oov_set_order(floor, button, set);
	}
}

void oov_set_all_orders(int set){
	for (int floor = 0; floor < 4; floor ++){
		oov_set_floor_orders(floor, set);
	}
}

int oov_check_order(int floor, int button){
	return orders[floor][button];
}

int oov_check_floor(int floor){
	return (oov_check_order(floor, 2) || oov_check_order(floor, 1) || oov_check_order(floor, 0));
}

int oov_check_floors_along_dir(int start_floor, int along_dir){
	for (int floor = start_floor; (floor >= 0 && floor < 4); floor += along_dir){
			if (oov_check_floor(floor)){
				return 1;
		}
	}
	return 0;
}

int oov_get_amount(){
	return orders_amount;
}