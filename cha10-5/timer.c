# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>

typedef void (*timer_handler)(int id);

typedef struct timer {
	int id;
	timer_handler func_p;
	time_t start;
	time_t end;
	struct	timer *next;
} timer;


static volatile timer* head;
static volatile int timer_counter;
static struct sigaction new_action, old_action;


void handler(int signum) {
	
	/* this function is called on SIALRM, call heads function, and then free */
	
	/* to increase robustness - block SIGALRM while processing user function */
	timer *tmp;

	(head->func_p)(head->id);
	
	tmp = head;
	if (head->next != 0) {
		head = head->next;
		alarm(head->end - time(NULL));
	}	
	free(tmp);	
		

	return;

}

timer *_place_after(time_t secval);


int setup() {
	
	new_action.sa_handler = handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	if (sigaction(SIGALRM, &new_action, &old_action) < 0)
		exit(-1);
	return 0;
}


int create_timer(timer_handler func_p, unsigned int seconds) {

	unsigned int calc_end = 0;	
	timer *anchor = 0;
	timer *tmp  = 0;
	
	if (0 == head) { /* create new timer */
	
		head = (timer *) malloc (sizeof(timer));
		head->id = timer_counter++;
		head->func_p = func_p;
		head->start = time(NULL);
		head->end = head->start + seconds;
		head->next = 0;
		alarm(seconds);
		return head->id;
	}
	
		
	/* If got to here - a timer already exists */
	calc_end = time(NULL) + seconds;	
	anchor = _place_after(calc_end);

	tmp = (timer *) malloc (sizeof(timer)); /*looks almost the same as the code in the first if - make one function*/
	tmp->id = timer_counter++;
	tmp->func_p = func_p;
	tmp->start = time(NULL);
	tmp->end = tmp->start + seconds;
	
	if (calc_end < head->end) {
		/* replace head with tmp and restart alarm */
		tmp->next = head;
		head = tmp;
		alarm(calc_end - time(NULL));

	}
	else if (anchor->next != 0) { /*else if and if can be united under same else*/
		
		tmp->next = anchor->next;
		anchor->next = tmp;
	}
	else {
		tmp->next = 0; 
		anchor->next = tmp;
	}

	return tmp->id;
	
}

timer * _place_after(time_t end) {
		
	timer *curr;
	curr = head;
/* the return is doplicated - rewrite the function, one return in the end of the function*/
	while (curr != 0) {
		if (curr->next != 0 && curr->next->end >= end) 
			return curr;
		else if (curr->next == 0)
			return curr;
		curr = curr->next;
	}
		
}

void user_callback(int id) {
	
	printf("timer %d finished. the time is: %lu\n", id, time(NULL));
}

int main(int argc, char *argv[]) {
	
	setup();

	int id1, id2, id3;

	id1 = create_timer((*user_callback), 3);
	id2 = create_timer((*user_callback), 7); 
	id3 = create_timer((*user_callback), 1); 
	for(;;)
		pause();
}
