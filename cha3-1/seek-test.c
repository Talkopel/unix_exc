# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

int set_up_env(const char *filename)
{
	
	int fd;
	char test_text[] = "Hello World!Hello World!Hello world!\n";
	int bytes_written = 0;

	// create file - disregarding previous
	if ((fd = creat(filename, O_WRONLY)) == -1)
		return -1;
	
	bytes_written =  write(fd, test_text, strlen(test_text));
	close(fd);
	return bytes_written;

}

const char * file_test = "local.txt";

int main(int argc, char **argv)
{
	if (set_up_env(file_test) == -1)
		exit(-1);
	exit(0);
}
