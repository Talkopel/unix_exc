# include "sync.h"

void _err(char * err, int ern) {
	fprintf(stderr, "%s with errno: %d\n",err, ern);
}


int _lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	lock.l_type = type; /* F_RDLCK, F_WRLCK, F_UNLCK */
	lock.l_start = offset; /* byte offset, relative to l_whence */
	lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
	lock.l_len = len; /* #bytes (0 means to EOF) */
	return(fcntl(fd, cmd, &lock));
}

int LCK_SETUP(char *pathname) {
	
	int fd;

	if ((fd = open(pathname, O_CREAT | O_RDWR ,S_IRWXU | S_IRWXG | S_IROTH)) < 0) {
		_err("failed to open lock file", errno);
		return -1;
	}

	
	/* obtain read lock */
	if (_lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0) {
		_err("failed to obtain read lock in setup", errno);
		return -1;
	
	}

	return fd;
	
}


void LCK_WAIT(int lock_id) {
	
	/* wait to write lock - will continue execution only after all other processes
	   using this library relenquish their read lock */
	
	struct flock lock;	

	if (_lock_reg(lock_id, F_SETLKW, F_WRLCK, 0, SEEK_SET, 0) < 0) {
		_err("failed to waint for write lock.. undefined", errno);
		return;
	}

	if (_lock_reg(lock_id, F_SETLKW, F_UNLCK, 0, SEEK_SET, 0) < 0) {
		_err("failed to release write lock", errno);
		return;
	}



	if (_lock_reg(lock_id, F_SETLKW, F_RDLCK, 0, SEEK_SET, 0) < 0) {
		_err("failed to obtain read lock after releasing write", errno);
		return;
	}	
	
}

void LCK_RELEASE(int lock_id) {
	
	struct flock lock;

	if (_lock_reg(lock_id, F_SETLKW, F_UNLCK, 0, SEEK_SET, 0) < 0)
		_err("failed to relenquish read lock", errno);

	do {
		lock.l_type = F_RDLCK; /* F_RDLCK, F_WRLCK, F_UNLCK */
	        lock.l_start = 0; /* byte offset, relative to l_whence */
        	lock.l_whence = SEEK_SET; /* SEEK_SET, SEEK_CUR, SEEK_END */
	        lock.l_len = 0; /* #bytes (0 means to EOF) */		

		fcntl(lock_id, F_GETLK, &lock);		
		
	} while(lock.l_type != F_UNLCK); /* loop ends when write lock is released */

	do {
		lock.l_type = F_WRLCK;
		lock.l_start = 0;
		lock.l_whence = SEEK_SET;
		lock.l_len = 0;
		fcntl(lock_id, F_GETLK, &lock);
	
	} while(lock.l_type == F_UNLCK); /* loop ends when other read lock is placed */


	if (_lock_reg(lock_id, F_SETLKW, F_RDLCK, 0, SEEK_SET, 0) < 0)
		_err("failed to obtain read lock after relenquising", errno);

}











