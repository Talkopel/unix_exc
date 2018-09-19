# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

int sig2str(int signo, char *copy_buf) {
	
	char *signame;
	
	signame = strsignal(signo);
	
	strncpy(copy_buf, signame, strlen(signame) + 1);	
	
	return 0;
	
			

}


int main(int argc, char *argv) {
	
	int i;
	char signame_buf[30];	


	for (i = 0; i < 32; i ++) { 
		sig2str(i, signame_buf);
		printf("signal no' %d, is %s\n",i, signame_buf);

	}

	return 0;	
	
}
