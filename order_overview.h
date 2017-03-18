void oov_set_order(int floor, int button, int value); //Verdien i etasje "floor" ved knapp "button" settes til "value", altså 0 eller 1
int oov_get_order(int floor, int dir);
void oov_reset_all_orders();	
void oov_reset_floor_orders(int floor);
int oov_get_amount();