# include <unistd.h>
# include <signal.h>
# include <stdlib.h>


typedef void (*timer_handler)(int id);

struct timer {
	int id;
	timer_handler func_p;
	unsigned int seconds;
}


static volatile timer* head;
static volatile timer_counter;

int setup() {
	
			

}


int create_timer(timer_handler func_p, unsigned int seconds) {

	if (0 == head) { /* create new timer */
	
		head = (timer *) malloc (sizeof(timer));
		head->id = timer_counter++;
		head->func_p = func_p;
		head->seconds = seconds;

	}

}



