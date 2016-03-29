#include "client.h"
#include <stdio.h>
#include <signal.h>



int main(int argc, char ** argv, char ** envp)
{
	create_wd(argc, argv, envp);
	return 0;
}
