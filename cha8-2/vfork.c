# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>


int fork_out() {
	
	pid_t pid;

	if ((pid = vfork()) < 0)
		exit(-1);

	if (pid == 0)
		return 1;
	
	else 
		return 0;

}


int main (int argc, char *argv[]) {
	
	int res;
	
	printf("before fork..\n"); 

	res = fork_out(); /* segmentation fault because of return address overloading by stack frame  */

	printf("result: %d\n", res);

	_exit(0);

}
