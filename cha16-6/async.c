# include <fcntl.h>
# if defined(SOLARIS)
# include <stropts.h>
# endif
# include <sys/ioctl.h>
# include <unistd.h>
# include <stdlib.h>

int set_async(int fd) {

	/* sets a socket as async, user has to set up signal processing */
	int flags = 1;

	if (fcntl(fd, F_SETOWN, getpid()) < 0)
		return -1;

	
	if (ioctl(fd, FIOASYNC, &flags) < 0)
		return -1;

	return 0;
	
}


int set_sync(int fd) {
	
	int flags = 0;

	if (ioctl(fd, FIOASYNC, &flags) < 0)
		return -1;

	return 0;	

}
