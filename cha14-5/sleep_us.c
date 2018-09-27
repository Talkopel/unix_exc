# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/select.h>

int sleep_us(unsigned int);

int main(int argc, char *argv[]) {
	
	

	sleep_us(200);



}


int sleep_us(unsigned int microseconds) {

	struct timeval tv; 

	tv.tv_usec = microseconds;

	return(select(1, NULL, NULL, NULL, &tv));
}
