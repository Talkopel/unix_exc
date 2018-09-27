# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>

int _lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len);
	/* private use function - from APUE */

void _err(char *, int);
	/* private function */

int LCK_SETUP(char *pathname);
	/* this function sets up a file to use as a lock
	   it needs to be called from both processes before
	   synchronization can be started
	   better to call with absolute pathname */

void LCK_WAIT(int lock_id);
	/* this function waits until a resource has been
	   released by another process using LCK_RELEASE */

void LCK_RELEASE(int lock_id);
	/* this function releases all waiting processes */
	
		
	

