/*#include "sched_prioq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

volatile sig_atomic_t counter = 0;

void pong(int num)
{
	fprintf(stderr ,"pong\n");
	counter = 0;
}

void ping(int num)
{
	fprintf(stderr ,"ping\n");
	counter = 0;
}

int func_signal1(void* param)
{
	if (10 == counter)
	{
		kill(*((pid_t*)param), SIGTERM);
		waitpid(*((pid_t*)param), NULL, 0);

		pid_t pid = fork();
		if (pid < 0)
		{
		     printf("Failed to fork()\n");
		}
		else if (pid == 0)
		{
			execlp("./testsched_process1.out", "./testsched_process1.out", "yan");
		}
		else
		{
			*((pid_t*)param) = pid;
		}

	++counter;
	printf ("P1 counter (send_signal) = %d\n", counter);


	}

	else
	{
		kill(*((pid_t*)param), SIGUSR2);
		++counter;
		printf ("P1 counter (send_signal) = %d\n", counter);
	}
	return 0;
}


int func_signal2( void* param)
{

	if (5 == counter)
	{

		kill(*((pid_t*)param), SIGTERM);
		waitpid(*((pid_t*)param), NULL, 0);

		pid_t pid = fork();
		if (pid < 0)
		{
		     printf("Failed to fork()\n");
		}
		else if (pid == 0)
		{
			execlp("./testsched_process1.out", "./testsched_process1.out", "sagi");
		}
		else
		{
			*((pid_t*)param) = pid;
		}

		++counter;

		printf ("P2 counter (send_signal) = %d\n", counter);

	}

	else
	{
		kill(*((pid_t*)param), SIGUSR1);
		++counter;
		printf ("P2 counter (send_signal) = %d\n", counter);
	}

	return 0;
}


int main(int argc , char** argv)
{
	signal(SIGUSR1 , pong);
	signal(SIGUSR2 , ping);

	pid_t* pid = NULL;

	pid = (pid_t*)malloc(sizeof(pid_t));

    if(argc == 1)
    {
    	*pid = fork();

    	if (*pid < 0)
		{
		     printf("Failed to fork()\n");
		}

		else if (*pid == 0)
		{
			execlp("./testsched_process1.out" ,"./testsched_process1.out" , "sagi");
		}

		else
		{

    	task_t* t1 = make_task(&func_signal1,(void*)pid);

    	size_t id1;

    	scheduler_t * sched;
    	sched = create_sched();

    	add_task(sched, t1, 1, &id1);

    	printf("process id: %d\t parent process pid: %d\n", getpid(), getppid());

    	run_sched(sched);

		}
	}

	else if(strcmp(argv[1], "sagi") == 0)
	{
	*pid = getppid();
	task_t* t1 = make_task(&func_signal2,(void*)pid);

	size_t id1;

	scheduler_t * sched;
	sched = create_sched();

	add_task(sched, t1, 5, &id1);

	printf("process id: %d\t parent process pid: %d\n", getpid(), getppid());

	run_sched(sched);

	}

	else if(strcmp(argv[1], "yan") == 0)
	{

	*pid = getppid();

	task_t* t1 = make_task(&func_signal2,(void*)pid);

	size_t id1;

	scheduler_t * sched;
	sched = create_sched();

	add_task(sched, t1, 5, &id1);

	printf("process id: %d\t parent process pid: %d\n", getpid(), getppid());

	run_sched(sched);

	}

	return 0;
}

*/

/*
 * sched_process1.c
 *
 *  Created on: Dec 1, 2014
 *      Author: student
 */
/*
 * sched_process1.c
 *
 *  Created on: Dec 1, 2014
 *      Author: student
 */

#include "sched_prioq.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>

volatile sig_atomic_t counter = 0;

void pong(int num)
{
	fprintf(stderr ,"pong\n");
	counter = 0;
}

void ping(int num)
{
	fprintf(stderr ,"ping\n");
	counter = 0;
}


int func_signal1( void* param)
{
	if (10 == counter)
	{
		counter++;

		kill(*((pid_t*)param), SIGTERM);

        waitpid(*((pid_t*)param), NULL, 0);

		pid_t pid = fork();

		if (pid < 0)
		{
		     printf("Failed to fork()\n");
             return -1;
		}

		else if (pid == 0)
		{
			execlp("./testsched_process1.out", "./testsched_process1.out", "sagi");
		}

		else
		{
			*((pid_t*)param) = pid;
		}

		printf ("P1 counter (send_signal) = %d\n", counter);
	}
	else
	{
		kill(*((pid_t*)param), SIGUSR1);
		++counter;
		printf ("P1 counter (send_signal) = %d\n", counter);
	}
	return 0;
}


int func_signal2( void* param)
{

	if (5 == counter)
	{
		counter++;

		kill(*((pid_t*)param), SIGTERM);
        waitpid(*((pid_t*)param), NULL, 0);
		pid_t pid = fork();

		if (pid < 0)
		{
		     printf("Failed to fork()\n");
		}

		else if (pid == 0)
		{
			execlp("./testsched_process1.out", "./testsched_process1.out", "yan");
		}

		else
		{
			*((pid_t*)param) = pid;
		}

		printf ("P1 counter (send_signal) = %d\n", counter);
	}
	else
	{
		kill(*((pid_t*)param), SIGUSR2);

		++counter;

		printf ("P2 counter (send_signal) = %d\n", counter);
	}

	return 0;
}


int main(int argc , char** argv)
{
	signal(SIGUSR1 , ping);
	signal(SIGUSR2 , pong);

	pid_t* pid = NULL;

	pid = (pid_t*)malloc(sizeof(pid_t));

    if (argc == 1)
    {
    	*pid = fork();

    	if (*pid < 0)
		{
		     printf("Failed to fork()\n");
             return -1;
		}

		else if (*pid == 0)
		{
			execlp("./testsched_process1.out" ,"./testsched_process1.out" , "sagi");
		}

		task_t* t1 = make_task(&func_signal1,(void*)pid);
		size_t id1;

		scheduler_t* sched;
		sched = create_sched();

		add_task(sched, t1, 1, &id1);

		printf("first run, process %d  parent process %d\n", getpid(), getppid());

		run_sched(sched);

	}

	else if( strcmp(argv[1], "sagi") == 0)
	{
		*pid = getppid();

		task_t* t1 = make_task(&func_signal1,(void*)pid);
		size_t id1;

		scheduler_t * sched;
		sched = create_sched();

		add_task(sched, t1, 5, &id1);

		printf("second run, process %d  parent process %d\n", getpid(), getppid());

		run_sched(sched);
	}

	else if( strcmp(argv[1], "yan") == 0)
	{
		*pid = getppid();

		task_t* t1 = make_task(&func_signal2,(void*)pid);
		size_t id1;

		scheduler_t * sched;
		sched = create_sched();

		add_task(sched, t1, 5, &id1);

		printf("second run, process %d  parent process %d\n", getpid(), getppid());

		run_sched(sched);
	}

	return 0;
}
