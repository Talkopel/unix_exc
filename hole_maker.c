# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

const char *text = "ABCDEFGHIJKLMPPQRSTUV";

int main(int argc, char **argv)
{
	// going to create file with holes
	
	int fd;

	if ((fd = creat("hole.txt", O_RDWR | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) == -1)
		exit(-1);

	
	write(fd, text, strlen(text));

	lseek(fd, 10000, SEEK_END);

	write(fd,text, strlen(text));
	
	exit(0);

}
