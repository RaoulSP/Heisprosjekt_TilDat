#include <time.h>
#include "timer.h"

int start_time;

void timer_start(){
	start_time = time(NULL);
}

int timer_check(){
	return difftime(time(NULL), start_time) > 3 ? 1 : 0; //Inline function
}