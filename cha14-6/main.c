# include "sync/sync.h"
# include <unistd.h>

static volatile int sleep_counter;
const char *lock = "/home/kopel/Desktop/lck.txt";

void printout(pid_t pid, int lock_id) {
	
	
	for (;;) {
		sleep(1);
		printf("%d is printing hello!\n", getpid());
		if (pid != 0 && sleep_counter++ == 5){
			printf("parent called release\n");
			 LCK_RELEASE(lock_id);
		}
	}
	

}


int main(int argc, char *argv[]) {

	int lock_id;
	pid_t pid;
		
	if ((pid = fork()) < 0) {
		fprintf(stderr, "failed to fork\n");
	} else if (0 == pid) {
		
		lock_id = LCK_SETUP(lock);
		LCK_WAIT(lock_id);
		printout(pid, lock_id);
		

	}

	else {
		
		lock_id = LCK_SETUP(lock);
		printout(pid, lock_id);
		

	}

}
