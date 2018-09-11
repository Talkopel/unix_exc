# include <stdio.h>
# include <sys/utsname.h>
# include <stdlib.h>

# ifdef _GNU_SOURCE 
const char *printformat = "sysname: %s\n nodename: %s\n release: %s\n version %s\n machine: %s\n domain name: %s\n";
# else
const char *printformat = "sysname: %s\n nodename: %s\n release: %s\n version %s\n machine: %s\n";
# endif

int main(int argc, char **argv) {

	struct utsname buf;

	if (uname(&buf) == -1)
		exit(-1);

	# ifdef _GNU_SOURCE
	printf(printformat, buf.sysname, buf.nodename, buf.release, buf.version, buf.machine, buf.domainname);
	# else 
	printf(printformat, buf.sysname, buf.nodename, buf.release, buf.version, buf.machine);
	# endif
}
