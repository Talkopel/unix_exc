# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>

void alrm_handler(int sig);


int main(int argc, char *argv[]) {
	
	char *buf;
	FILE *fp;
	unsigned long long i;
	struct sigaction new, old;
	
	buf = (char *) malloc(100000000);

	if (0 == buf)
		exit(-3);
	else
		memset(buf, 71, 100000000);
		
	if ((fp = fopen("hello.txt", "w")) == 0)
		exit(-1);
	
	sigemptyset(&new.sa_mask);
	new.sa_flags = 0;
	new.sa_handler = alrm_handler;
	if (sigaction(SIGALRM, &new, &old) < 0)
		exit(-2);

	alarm(1);

	printf("%lu written\n",	fwrite(buf, 100000000, 1, fp));

	fclose(fp);
	free(buf);

}


void alrm_handler(int sig) {
	
	printf("Caught sigalrm!\n");
	pause();
	return;
}
