#include "../headers.h"

int main ()
{
	int status = system( "pwd; ls -al > foo");

	if ( status == -1 )
		perror("Call to system failed");
	else
		printf("Command exit status was %d\n", status);
}
