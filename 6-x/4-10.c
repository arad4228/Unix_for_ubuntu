#include <shadow.h>
#include <stdio.h>

int main(void) 
{
	struct spwd *spw;
	
	spw = getspnam("jeong-gyeongjae");
	printf("Login Name : %s\n", spw->sp_namp);
	printf("Passwd : %s\n", spw->sp_pwdp);
	printf("Last Change : %ld\n", spw->sp_lstchg);

	return 0;
}
