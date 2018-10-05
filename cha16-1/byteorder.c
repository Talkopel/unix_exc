# include <arpa/inet.h>
# include <stdlib.h>
# include <stdio.h>


int main(int argc, char *argv[]) {
	
	uint32_t net, host;

	host = 31;
	
	net = htonl(host);

	if (host != net) printf("little endian\n");
	else printf("big endian\n");
	

}
