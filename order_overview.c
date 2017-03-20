#include "order_overview.h"
#include "elev.h"



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

int get_floor(floor){	//get_floor_demand? get_floor_preference? get_floor_button
	int sum = 0;																//return boolean, return button type, or return direction type? What is the most elegant?
	for (button = 0; button < 3; button ++){	//would be slightly more efficient in the opposite direction
		sum += (button + 1) * (orders[floor_nr][button]);						//Some trickery to have get_floor return 0 or 1 if only the up or down button has been stored, and 2 or more if command or multiple buttons have been stored.
	}
	return (sum - 1);															//could initialize sum to -1 and not subtract here, with same result

}
int check_along_dir(int from_floor, int along_dir){									//scan along direction? scan direction? Check partition? Scan ahead? Check in range? Any in range?
	for (int floor = from_floor; (floor >= 0 && floor < 4); floor += along_dir){
			if (get_floor(floor) > -1){
				return 1;
		}
	}
	return 0;
}
