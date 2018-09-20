# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>


typedef void (*timer_handler)(int id);

typedef struct timer {
	int id;
	timer_handler func_p;
	unsigned int seconds;
	struct	timer *next;
} timer;


static volatile timer* head;
static volatile int timer_counter;
static struct sigaction act;


void handler(int signum) {
	
	/* this function is called on SIALRM, call heads function, and then free */
	
	/* to increase robustness - block SIGALRM while processing user function */
	timer *tmp;

	(head->func_p)(head->id);
	
	tmp = head;
	head = head->next;
	
	free(tmp);	
		

	return;

}

timer *_place_after(unsigned int secval);


int setup() {
	
	act.sa_handler = handler;
	if (sigaction(SIGALRM, &act, NULL) < 0)
		exit(-1);
	return 0;
}


int create_timer(timer_handler func_p, unsigned int seconds) {

	unsigned int time_to_ring = 0;	
	timer *anchor = 0;
	timer *tmp  = 0;
	
	if (0 == head) { /* create new timer */
	
		head = (timer *) malloc (sizeof(timer));
		head->id = timer_counter++;
		head->func_p = func_p;
		head->seconds = seconds;
		head->next = 0;
		return head->id;
	}
	
		
	/* If got to here - a timer already exists */
	time_to_ring = seconds - alarm();
	anchor = _place_after(time_to_ring);
	
	tmp = (timer *) malloc (sizeof(timer));
	tmp->id = timer_counter++;
	tmp->func_p = func_p;
	tmp->seconds = time_to_ring;
	
	if (anchor-> next != 0) {
		
		tmp->next = anchor->next;
		anchor->next = tmp;
	}
	else {
		
		tmp->next = 0; 
		anchor->next = tmp;

	}

	return tmp->id;
	
}

timer * _place_after(unsigned int secval) {
		
	timer *curr;
	curr = head;

	while (curr != 0) {
		if (curr->next != 0 && curr->next->seconds >= secval)
			return curr;
		else if (curr->next == 0)
			return curr;
		curr = curr->next;
	}
		
}

void user_callback(int id) {
	
	printf("timer %d finished\n", id);
}

int main(int argc, char *argv[]) {
	
	setup();

	int id1, id2, id3;

	id1 = create_timer((*user_callback), 3);
	id2 = create_timer((*user_callback), 4); 
	id3 = create_timer((*user_callback), 7); 

}
