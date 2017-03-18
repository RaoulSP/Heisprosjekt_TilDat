#include <stdio.h>
#include "finite_state_machine.h"
#include "elev.h"
#include "timer.h"
#include "order_overview.h"

//Kode som bare gjennomf�res �n gang i overgangene mellom tilstandene, kj�res i "fsm_trans" funksjonene
//Kode som m� kj�res kontinuerlig mens heisen er i en tilstand, kj�res i casene
enum state fsm_run(enum state current_state) {

	switch (current_state) {

	case(initialize):
		if (!elev_init()) { 									//Initialiser maskinvare
			printf("Unable to initialize elevator hardware!\n");
			next_state = exit;
		}
		else{
			fsm_trans_start_calibration();
			next_state = calibrating;
		}
		break;

	case(calibrating):
		if(elev_get_floor_sensor_signal() >= 0) {
			fsm_trans_finish_calibration();
			next_state = door_closed;
		}
		break;

	case(door_closed):
		oov_check_order_buttons();
		if(elev_get_stop_signal()){	
			fsm_trans_em_stop_press();
			next_state = em_stop_anywhere;
		}
		else if(oov_get_amount()){
			fsm_trans_depart();
			next_state = fulfilling_order;				
		}
		break;

	case(fulfilling_order):
		oov_check_order_buttons();
		if(elev_get_stop_signal()){
			fsm_trans_em_stop_press();
			next_state = em_stop_anywhere; 
		}
		else{
			sensor_signal = elev_get_floor_sensor_signal();
			if (sensor_signal >= 0) { 
				//Styring av etasjeindikator
				if(sensor_signal != current_floor){ 
					current_floor = sensor_signal;
					elev_set_floor_indicator(current_floor);
				}
				//Stopper hvis noen vil av heisen, eller p�stige i bevegelsesretningen, eller hvis det ikke er flere bestillinger i etasjene lenger bort i bevegelsesretningen
				if(oov_get_order(current_floor, 2) || (oov_get_order(current_floor, 0) && dir == 1) || (oov_get_order(current_floor, 1) && dir == -1) || !check_orders_along_dir(current_floor + dir, dir)){
						fsm_trans_arrive();
						next_state = door_open;
				}
			}
		}
		break;

	case(door_open):
		oov_check_order_buttons();
		if (elev_get_stop_signal()){
			fsm_trans_em_stop_press();
			next_state = em_stop_anywhere;
		}
		else{
			if(timer_check()){
				fsm_trans_close();
				next_state = door_closed;
			}
			else{
				for(int button = 0; button < 3; button++){
					if(oov_get_order(current_floor, button)){
						fsm_trans_reopen();
					}
				}
			}
		}	
		break;	

	case(em_stop_anywhere):
		if(elev_get_floor_sensor_signal() != -1){
			fsm_trans_em_stop_open();
			next_state = em_stop_at_floor;
		}
		else if(!elev_get_stop_signal()){
			fsm_trans_em_stop_release();
			next_state = door_closed;
		}
		break;

	case(em_stop_at_floor):
		if(!elev_get_stop_signal()){
			fsm_trans_em_stop_floor_release();
			next_state = door_open;
		}
		break;
	}

	return next_state;
}

void fsm_trans_start_calibration(){
	dir = 1;
	elev_set_motor_direction(dir);
}

void fsm_trans_finish_calibration(){
	elev_set_motor_direction(0);
	current_floor = elev_get_floor_sensor_signal();
	elev_set_floor_indicator(current_floor);	
}

void fsm_trans_depart(){
	if(!check_orders_along_dir(current_floor + dir, dir)){
		current_floor += dir;
		dir *= -1;
	}
	elev_set_motor_direction(dir);
}

void fsm_trans_arrive(){
	elev_set_motor_direction(0);
	oov_reset_floor_orders(current_floor);
	elev_set_door_open_lamp(1);
	timer_start();
}

void fsm_trans_reopen(){
	timer_start();
	oov_reset_floor_orders(current_floor);
}

void fsm_trans_close(){
	elev_set_door_open_lamp(0);
}

void fsm_trans_em_stop_press(){
	elev_set_motor_direction(0);
	oov_reset_all_orders();
	elev_set_stop_lamp(1);
}

void fsm_trans_em_stop_open(){
	elev_set_door_open_lamp(1);
}

void fsm_trans_em_stop_release(){
	elev_set_stop_lamp(0);
}

void fsm_trans_em_stop_floor_release(){
	timer_start();
	elev_set_stop_lamp(0);
}