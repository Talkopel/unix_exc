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
static sigaction act;


void handler(int signum) {
	
	return;

}

int setup() {
	
	act.sa_handler = handler;
	if (sigaction(SIGALRM, &act, NULL) < 0)
}


int create_timer(timer_handler func_p, unsigned int seconds) {

	unsigned int time_to_ring = 0;	
	
	if (0 == head) { /* create new timer */
	
		head = (timer *) malloc (sizeof(timer));
		head->id = timer_counter++;
		head->func_p = func_p;
		head->seconds = seconds;

	}

	

}



