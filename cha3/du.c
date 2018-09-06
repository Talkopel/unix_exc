# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

int dup22(int oldfd, int newfd)
{
	int tmpfd;
	int firstfd;

	// check if old and new are same value
	if (oldfd == newfd)
	       return newfd;	


	// check that oldfd is a valid descriptor
	if ((tmpfd = dup(oldfd)) == -1)
		return -1;
	
	if ((tmpfd = dup(newfd)) != -1)
	{
		// if new fd is already open
		close(newfd);
		close(tmpfd);
	
	}

	firstfd = dup(oldfd);
	tmpfd = firstfd;
	
	while (tmpfd < newfd)
		tmpfd = dup(oldfd);
	
	while (tmpfd-- >= firstfd) 
		close(tmpfd);

	return newfd;



}

const char * check = "Hello World!\n";

int main(int argc, char **argv)
{
	
	int fd;
	size_t write_size = 0;
	
	fd = dup22(STDOUT_FILENO, 7);
	
	write_size = write(fd, check, strlen(check));
	write_size = write(STDERR_FILENO, check, strlen(check));

	exit(0);

}
