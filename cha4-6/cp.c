# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

# define BLOCK_SIZE 512 

int cp2(const char *orig, const char *new);
int block_not_empty(char *block);

int main(int argc, char **argv)
{
	
	int res;
		
	if (argc != 3) 
	{
		printf("Usage: cp2 <path> <path>\n");
		exit(-1);
	}

	if ((res = cp2(argv[1], argv[2])) < 0) 
	{
		printf("An error has occoured...\n");
		exit(-1);
	}

	exit(0);

}

int cp2(const char *orig, const char *new)
{
	
	struct stat st;
	char *buf;
	int fd1, fd2;
	int i;
	
	if (stat(orig, &st) == -1)
		return -1;
	
	if ((fd1 = open(orig, O_RDONLY)) == -1)
		return -2;

	if ((fd2 = creat(new, O_RDWR | S_IRWXG | S_IRWXU)) == -1)
		return -3;
	
	// need to iterate over BLOCK_SIZE chunks in memory -> if the whole block is zeroed its the only way to verify that its a hole
	// I don't know if its the best solution, but its what I got for now... :( 

	buf = (char *) malloc (BLOCK_SIZE);
	memset(buf, 0, BLOCK_SIZE);
	
	for (i = 0; i < st.st_size / BLOCK_SIZE; i++)
	{
		if (read(fd1, buf, BLOCK_SIZE) < BLOCK_SIZE)
			return -4;
		
		if (block_not_empty(buf))
			if (write(fd2, buf, BLOCK_SIZE) < BLOCK_SIZE)
				return -5;
			
		memset(buf, 0, BLOCK_SIZE);
	
	}

	if (st.st_size % BLOCK_SIZE != 0)
	{
		if (read(fd1, buf, st.st_size % BLOCK_SIZE) < st.st_size % BLOCK_SIZE)
			return -4;
		
		if (block_not_empty(buf))
			if (write(fd2, buf, st.st_size % BLOCK_SIZE) < st.st_size % BLOCK_SIZE)
				return -5;
	}	

	
	close(fd1);
	close(fd2);
	free(buf);
}


int block_not_empty(char *block)
{
	
	int i;

	for (i = 0; i < BLOCK_SIZE; i++)
	{
		if (block[i] != 0)
			return 1;
	
	}

	return 0;

}


