# include <stdio.h>
# include <errno.h>
# include <shadow.h>

void list_users();

int main(int argc, char **argv) {
	
	list_users();
	return 0;

}


void list_users() {
	
	struct spwd* pwd;
	
	setspent(); /* rewind user database */	
	
	while ((pwd = getspent()) != 0)
		printf("User: %s		pwd: %s\n",pwd->sp_namp, pwd->sp_pwdp);
	
	endspent();	
}
