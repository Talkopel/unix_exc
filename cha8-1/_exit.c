#include "apue.h"
# include <unistd.h>

int globvar = 6; /* external variable in initialized data */

void close_io() {
	
	fclose(stdout);
	fclose(stdin);
	fclose(stderr);
}

int main(void){

	int var; /* automatic variable on the stack */
	pid_t pid;
	var = 88;

	printf("before vfork\n"); /* we don’t flush stdio */
	
	if (atexit(close_io) < 0) /* this tells adds my function as an exit handler - which flushes and closes all streams */
		err_sys("at exit error");

	if ((pid = vfork()) < 0) {
		err_sys("vfork error");
	} else if (pid == 0) { /* child */
		globvar++; /* modify parent’s variables */
		var++;
		exit(0); /* child terminates */
	}

	/* parent continues here */
	printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,var);
	exit(0);
}
