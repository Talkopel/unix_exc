# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>


int main(int argc, char *argv[]) {
	
	pid_t pid;
	char buf[1000];

	if ((pid = fork()) < 0)
		exit(-1);

	if (pid == 0)
		return 1;

	
	sprintf(buf, "ps aux -q %d\n", pid);
	system(buf);

	
}
