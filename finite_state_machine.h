//De ulike tilstandene til heisen
enum state {
	start,
	calibrating,
	door_closed,
	door_open,
	fulfilling_order,
	em_stop_anywhere,
	em_stop_at_floor
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

//Hjelpefunksjoner
int check_along_dir(int from_floor, int along_dir);		//Sjekker om det er gjort bestillinger langs en gitt retning fra en gitt etasje, og returnerer 1 dersom den finner noe 
void check_order_buttons(); 							//Sjekker om bestillingsknapper er trykket og lagrer dem som ordre i "order_overview"