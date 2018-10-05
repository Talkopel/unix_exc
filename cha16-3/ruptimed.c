#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>

#define BUFLEN	128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

extern int initserver(int, const struct sockaddr *, socklen_t, int);

void
serve(int sockfd)
{
	int		clfd;
	FILE	*fp;
	char	buf[BUFLEN];

	set_cloexec(sockfd);
	for (;;) {
		syslog(LOG_INFO, "accepting connections...");
		if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
			syslog(LOG_ERR, "ruptimed: accept error: %s",
			  strerror(errno));
			exit(1);
		}
		syslog(LOG_INFO, "got connection");
		set_cloexec(clfd);
		if ((fp = popen("/usr/bin/uptime", "r")) == NULL) {
			sprintf(buf, "error: %s\n", strerror(errno));
			send(clfd, buf, strlen(buf), 0);
		} else {
			while (fgets(buf, BUFLEN, fp) != NULL)
				send(clfd, buf, strlen(buf), 0);
			pclose(fp);
		}
		close(clfd);
	}
}

int
main(int argc, char *argv[])
{
	struct addrinfo	*ailist, *aip;
	struct addrinfo	hint;
	int				sockfd, err, n, npid; 
	char			*host;
	pid_t *pids;

	if (argc != 1)
		err_quit("usage: ruptimed");
	if ((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
		n = HOST_NAME_MAX;	/* best guess */
	if ((host = malloc(n)) == NULL)
		err_sys("malloc error");
	if (gethostname(host, n) < 0)
		err_sys("gethostname error");
	printf("host name: %s\n", host);	
	daemonize("ruptimed");
	memset(&hint, 0, sizeof(hint));
	hint.ai_flags = AI_CANONNAME;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if ((err = getaddrinfo(host, "ruptime", &hint, &ailist)) != 0) {
		syslog(LOG_ERR, "ruptimed: getaddrinfo error: %s",
		  gai_strerror(err));
		exit(1);
	}

	/* count possible endpoint, for each one - fork out */
	npid = 0;
	for (aip = ailist; aip != NULL; aip = aip->ai_next) 
		npid++;

	/* allocate array for all pids */
	pids = (pid_t *) malloc(sizeof(pid_t) * npid);
	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		
		syslog(LOG_INFO, "started ruptimed with %d aliases", npid);
		if ((pids[npid -1] = fork()) == 0) {
			/* serve current fd */
				
			if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr,
			  aip->ai_addrlen, QLEN)) >= 0) {
				serve(sockfd);
				exit(0);
			}
		}
		else if (-1 == pids[npid - 1]) {
			exit(-1);
		}
		npid--;
	}
	exit(1);
}
