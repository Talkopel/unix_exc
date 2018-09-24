# include <signal.h>
# include <stdio.h>
# include <unistd.h> 
# include <string.h>
# include <stdlib.h>


# define SIGCOUNT (sizeof(sys_siglist) / 8)

void pr_mask(char *str);

int main(int argc, char *argv[]) {

	sigset_t set;

	if (sigfillset(&set) < 0)
		exit(-1);

	if (sigprocmask(SIG_SETMASK, &set, 0) < 0)
		exit(-2);

	pr_mask("hello");

}

void pr_mask(char *str) {

	sigset_t set;
	int i;
	/* because my implementation uses sigset_t as a struct, bitwise operations aren't possible */
	if (sigprocmask(SIG_UNBLOCK, NULL, &set) < 0)
		return;
	printf("%s:  ", str);		
	for (i = 0; i < SIGCOUNT; i++) {
		if (sigismember(&set, i) == 1)
			printf("  %s", strsignal(i));
	}
	

}
