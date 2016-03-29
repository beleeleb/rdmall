#define _POSIX_C_SOURCE 200112L

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "wd.h"
#include <errno.h>

struct sched_data
{
	char path[20];
	pid_t pid;
};

extern void *sched_func(void * arg);

void ping(int num, siginfo_t * info, void * data)
{
	printf("ping\n");
	sleep(1);
}

static int set_signal_handler(int signal , void(*handler_func)(int, siginfo_t *, void *) )
{
    struct sigaction act;
    memset (&act, '\0', sizeof(act));

    act.sa_sigaction = handler_func;
    act.sa_flags = SA_SIGINFO;

    if ( sigaction( signal , &act , NULL ) )
    {
        perror ("sigaction setting failed");
        return 1;
    }

    return 0;
}

int main(void)
{

	/*setenv("name1", "./testwd.out", 1);*/

	set_signal_handler(SIGUSR1, &ping);

	char path[20];
	struct sched_data *mydata;
	mydata = (struct sched_data *)malloc(sizeof(struct sched_data));
	mydata->pid = getppid();

	strcpy(mydata->path, getenv("name1"));
	printf("%s\n", mydata->path);
	printf("\tI am test wd\n");
	printf("\tparent pid: %d my pid: %d\n", getppid(), getpid());
	sched_func((void*)mydata);
	return 0;
}

