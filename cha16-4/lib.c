# include "lib.h"

void err_exit(char *message) {

	fprintf(stderr, "%s\n", message);
	exit(-1);
}
