void oov_set_order(int floor, int button, int set); //Sets one order in the array. Works kind of like a set/reset latch. If the set flag is 1 then the order is set according to the returned button value. If the set flag is 0, the order is reset. */
void oov_set_floor_orders(int floor, int set);
void oov_set_all_orders(int set);
int oov_get_order(int floor, int button);
int oov_get_floor(int floor);
int oov_check_along_dir(int from_floor, int along_dir); //Sjekker om det er gjort bestillinger langs en gitt retning fra en gitt etasje, og returnerer 1 dersom den finner noe
int oov_get_amount();
