void oov_set_order(int floor, int button, int value); //Verdien i etasje "floor" ved knapp "button" settes til "value", altså 0 eller 1
int oov_get_order(int floor, int dir);
void oov_reset_all_orders();	
void oov_reset_floor_orders(int floor);
int oov_get_amount();
int oov_check_orders_along_dir(int from_floor, int along_dir);		//Sjekker om det er gjort bestillinger langs en gitt retning fra en gitt etasje, og returnerer 1 dersom den finner noe 
void oov_set_new_orders(); 									//Sjekker om bestillingsknapper er trykket og lagrer dem som ordre i "order_overview"