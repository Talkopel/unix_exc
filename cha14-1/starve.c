# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h> 

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;

	lock.l_type = type; /* F_RDLCK, F_WRLCK, F_UNLCK */
	lock.l_start = offset; /* byte offset, relative to l_whence */
	lock.l_whence = whence; /* SEEK_SET, SEEK_SET, SEEK_END */
	lock.l_len = len; /* #bytes (0 means to EOF) */

	return(fcntl(fd, cmd, &lock));
}


void err_exit(const char *message, int code) {

	fprintf(stderr, "%s\n", message);
	exit(code);

}

int main(int argc, char* argv[]) {

	int fd;
	pid_t pid1, pid2, pid3;
	

	if ((fd = open("trial.txt", O_RDWR | O_CREAT | O_TRUNC, 666)) < 0) 
		err_exit("couldn't create file", -1);
	
	if (write(fd, "1234", 4) < 4)
		err_exit("couldn't write to created file", -2);

	
	if ((pid1 = fork()) < 0)
		err_exit("coudln't fork 1", -3);
	else if (0 == pid1) {
		/* read lock fd and then pause */
		if (lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0)
			err_exit("child 1 couldn't lock file", -4);
		
		printf("child 1 got read lock\n");
		pause();
		exit(0);
	}
	else sleep(1); 
	
	
	if ((pid2 = fork()) < 0)
		err_exit("couldn't fork 2", -3);
	else if (0 == pid2) {
	
	/* read lock again */
		if (lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0)
			err_exit("child 2 coudlnt lock file", -4);
		
		printf("child 2 got read lock\n");
		pause(); 
		exit(0);

	} else sleep(1);


	if ((pid3 = fork()) < 0)
		err_exit("couldn't fork 3", -3);
	else if (0 == pid3) {

		if (lock_reg(fd, F_SETLKW, F_WRLCK, 0, SEEK_SET, 0) < 0)
			err_exit("child 3 stopped waiting for write lock for some reason", -5);

		printf("got write lock???\n");
		exit(0);

	}

	else {
		/* parent get lock without waiting */
		if (lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0)
			printf("parent failed to acquire write lock while child was waiting with error: %d\n", errno);

	}	

	return 0;

}
