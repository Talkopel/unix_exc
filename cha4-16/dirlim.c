# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>

# define PATH_DIRLIM ( PATH_MAX * 2 )

static char fullpath[PATH_DIRLIM]; /* final path needs to be larger than PATH_MAX */

int main(int argc, char **argv) {
	
	int dircounter = 0;
	char dirname[NAME_MAX];
	int fd;
	
	while(strlen(fullpath) < PATH_MAX) {
		
		memset(dirname, 0, NAME_MAX);	
		snprintf(dirname, PATH_DIRLIM, "dir%d", dircounter++);
		if (mkdir(dirname, S_IRWXU | S_IRWXG | S_IRWXO) < 0)
			exit(-1);
		
		if (chdir(dirname) < -1)
			exit(-2);

		if (getcwd(fullpath, PATH_DIRLIM) == 0) {
			fprintf(stderr, "Error getting current working directory after: %s with error code: %d", fullpath, errno);
			exit(-3);
		} 

	}
	
	
	if (getcwd(fullpath, PATH_DIRLIM) == 0) {
		fprintf(stderr, "Error after loop; getting current working directory after: %s with error code: %d", fullpath, errno);
		exit(-4);
	}

	printf("%s", fullpath);


	/* try to open file in this directory */
	if ((fd = creat("hello.txt", S_IRWXU | S_IRWXG)) > 0)
		if (write(fd, fullpath, PATH_DIRLIM) < PATH_DIRLIM)
			exit(-5);
	else
		exit(-6);
}
