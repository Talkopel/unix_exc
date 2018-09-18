# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "apue.h"

void pr_siginfo(siginfo_t *sig) {
	
	
	if (CLD_EXITED == sig->si_code)
		printf("Normal termination; exit status %d\n", sig->si_status);

	else
		printf("Terminated unnaturaley; signal nubmer: %d  ", sig->si_status);
	
	if (CLD_DUMPED == sig->si_code)
		printf("Core file generated..\n");
	else 
		printf("\n");

}


int main(void) {
	
	siginfo_t info;
	pid_t pid;
	int status;

	if ((pid = fork()) < 0)
		err_sys("fork error");

	else if (pid == 0) /* child */
		exit(7);

	if (waitid(P_PID, pid, &info, WEXITED | WSTOPPED ) < 0) /* wait for child */
		err_sys("wait error");
	pr_siginfo(&info); /* and print its status */

	if ((pid = fork()) < 0)
		err_sys("fork error");	

	else if (pid == 0) /* child */
		abort(); /* generates SIGABRT */

	if (waitid(P_PID, pid, &info, WEXITED| WSTOPPED) < 0) /* wait for child */
		err_sys("wait error");
	pr_siginfo(&info); /* and print its status */

	if ((pid = fork()) < 0)
		err_sys("fork error");
	
	else if (pid == 0) /* child */
		status /= 0; /* divide by 0 generate SIGFPE */
	
	if (waitid(P_PID, pid, &info, WEXITED | WSTOPPED) < 0) /* wait for child */
		err_sys("wait error");	

	pr_siginfo(&info); /* and print its status */
	exit(0);
}
