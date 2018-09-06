# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>

const char * file_test = "local.txt";
const char * file_content = "ABCDEFGHIJKLMNOPQRSTUZWXYZ";
const char * test_write = "BLABLABLA";

int set_up_env(const char *filename)
{
	
	int fd;
	int bytes_written = 0;

	// create file - disregarding previous
	if ((fd = creat(filename, O_RDWR | O_TRUNC | S_IRWXU)) == -1)
		return -1;
	
	bytes_written =  write(fd, file_content, strlen(file_content));
	close(fd);
	return bytes_written;

}

void dump_fd_out(int fd)
{	
	char buf[10];

	lseek(fd, 0, SEEK_SET);

	while(memset(buf, 0, 10) && read(fd, buf, 10) > 0)
		write(STDOUT_FILENO, buf, 10); 
	

}


int test_with_file(const char *filename)
{
	
	int fd;
	char buf[10];

	if ((fd = open(filename, O_RDWR | O_APPEND)) == -1)
		return -1;

	if (lseek(fd, 0, SEEK_SET) == -1)
		return -2;

	printf("Trying to write %s to start of file...\n", test_write);	

	if (write(fd, test_write, strlen(test_write)) == -1)
		return -4;

	// write all file content to stdout
	printf("File content:\n ");
	dump_fd_out(fd);
	printf("\n");
	
	close(fd);

	return 0;
}


int main(int argc, char **argv)
{
	if (set_up_env(file_test) == -1)
		exit(-1);
	
	switch (test_with_file(file_test))
	{

	case -1:
		printf("failed to open file!\n");
		exit(-1);
	case -2:
		printf("failed to seek start!\n");
		exit(-1);
	case -3:
		printf("failed to read from start!\n");
		exit(-1);
	case -4:
		printf("failed to write to file!\n");
		exit(-1);
	case 0:
		printf("all operations were successful!\n");
		exit(0);
	}
	
	exit(0);
}
