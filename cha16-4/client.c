# include <netdb.h>
# include <errno.h>
# include <sys/socket.h>
# include <string.h> 
# include "lib.h"


int main(int argc, char *argv[]) {

	struct addrinfo *ailist, *aip;
	struct addrinfo inf;
	int sockfd, err, hostlength;
	char *host;
	char buf[ebufsz];
	FILE *fd_read;

	if ((hostlength = sysconf(_SC_HOST_NAME_MAX)) < 0)
		hostlength = 256;
	
	if ((host = (char *) malloc(hostlength)) == NULL)	
		err_exit("malloc error");

	if (gethostname(host, hostlength) < 0)
		err_exit("host error");

	memset(&inf, 0, sizeof(inf));
	inf.ai_flags = AI_CANONNAME;
	inf.ai_socktype = SOCK_STREAM; /* tcp */
	inf.ai_canonname = NULL;
	inf.ai_addr = NULL;
	inf.ai_next = NULL;

	if ((err = getaddrinfo(host, "psremote", &inf, &ailist)) != 0) {
		snprintf(buf, ebufsz, "getaddrinfo err: %s\n", gai_strerror(err));
		err_exit(buf);
	}

	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		
		if ((sockfd = socket(aip->ai_addr->sa_family, SOCK_STREAM, 0)) < 0)
			err_exit("can't create socket");
		
		if (connect(sockfd, aip->ai_addr, aip->ai_addrlen) < 0)
			err_exit("can't connect to remore");
		
		if ((fd_read = fdopen(sockfd, "r")) == NULL)
			err_exit("can't turn socket to stream");
		
		fputs(fgets(buf, ebufsz, fd_read), stdout);

		fclose(fd_read);
		exit(0);
		
		
		  	
	}
	
}


