# include <time.h>
# include <stdio.h>


int main(int argc, char **argv) {

	time_t t;
	struct tm *tmp;
	char timeoutput[64];

	t = time(0);
	tmp = localtime(&t);
	
	if (0 == tmp)
		return -1;
	
	if (strftime(timeoutput, 64, "%a %b %d %H:%M:%S %Z %Y", tmp) == 0)
		return -2;

	printf("%s\n", timeoutput);

	return 0;


}
