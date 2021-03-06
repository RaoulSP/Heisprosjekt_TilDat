//De ulike tilstandene til heisen
enum state {
	initialize,
	calibrating,
	door_closed,
	door_open,
	fulfilling_order,
	em_stop_anywhere,
	em_stop_at_floor,
	exit				//ikke implementert som en case - programmet avsluttes fra main med en gang current_state == exit;
};

//Variabler
enum state next_state;
int sensor_signal;
int current_floor;
int dir;

//Hovedfunksjon - Returnerer neste tilstand
enum state fsm_run(enum state current_state);

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