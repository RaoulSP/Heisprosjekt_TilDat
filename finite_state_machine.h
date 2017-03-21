//De ulike tilstandene til heisen

enum tag_state {
	initialize,
	calibrating,
	door_closed,
	door_open,
	fulfilling_order,
	em_stop_anywhere,
	em_stop_at_floor,
	abort				//ikke implementert som en switch case - programmet avsluttes fra main med en gang current_state == abort;
};

typedef enum tag_state state;

//Variabler
state next_state;
int sensor_signal;
int current_floor;
int dir;

//Hovedfunksjon - Returnerer neste tilstand
state fsm_run(state current_state);

//Overganger mellom tilstander
void fsm_trans_start_calibration();
void fsm_trans_finish_calibration();
void fsm_trans_depart();
void fsm_trans_arrive();
void fsm_trans_reopen();
void fsm_trans_close();
void fsm_trans_em_stop_press();
void fsm_trans_em_stop_release();
void fsm_trans_em_stop_open();
void fsm_trans_em_stop_floor_release();