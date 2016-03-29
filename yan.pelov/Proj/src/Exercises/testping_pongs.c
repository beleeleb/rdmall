
#include <stdio.h>
	#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	char ping[] = "ping";
	char pong[] = "pong";
    char buf1[6];
    char buf2[6];
	int fds[2];
    
    pid_t pid;
    
	pipe(fds);
    
	pid = fork();

    if(pid == -1)
    {
        return -1;
    }
	if(pid == 0)
	{
       /* close(fds[0]);*/
        while(1)
        {
            /*close(fds[0]);*/
            write(fds[1], ping, 5);
            sleep(1);
            /*open(fds[0]);*/
            /*read(fds[0], buf2, sizeof(buf2));
            printf("\t%s", buf2);*/
        }
        
		return 0;
	}

	else
	{
		
        while(1)
        {
            /*close(fds[1]);*/
            sleep(2);
            /*open(fds[1]);*/
            read(fds[0], buf1, sizeof(buf1));
            printf("%s\n", buf1);
            write(fds[1], pong, 5);
        }
	}

	return 0;

}

