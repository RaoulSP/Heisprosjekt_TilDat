#include <time.h>
#include "timer.h"

int start_time = 0;

void timer_start_timer(){
	start_time = time(NULL);
}

int timer_is_time_out(){
	return difftime(time(NULL), start_time) > 3 ? 1 : 0;
}
