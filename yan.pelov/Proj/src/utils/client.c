/*
 * client.c
 *
 *  Created on: Dec 16, 2014
 *      Author: student
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "file_safe.h"
#include "client.h"


void client_sig_handler(int signo, siginfo_t *info, void *context)
{
	printf("client\n");
	kill(info->si_pid, SIGUSR1);
}

/*void client_sig_handler(pid_t param*)
{
	if(getenv("MYFLAG") == NULL)
	{
		printf("\t\tping\n");
	}

	else
	{
		printf("ping\n");

		kill(atoi(getenv("MYFLAG")), SIGUSR1);
	}
}*/


void create_file(int argc, char ** argv, char **envp, char* dir_path, char* file_path, pid_t pid)
{
	sf_create(dir_path, file_path);

	char* str = malloc(strlen("/tmp/student/app_name") + strlen(file_path)+1);
	str = strcat(str, "/tmp/student/app_name");
	str = strcat(str, "/");
	str = strcat(str, file_path);

	int fd = sf_open(str);

	int i = 0;

	char argc_num[5];

	sprintf(argc_num, "%d", argc);
	char *info =  malloc(sizeof(char)*5000);
	memset(info, 0, sizeof(char)*5000);
	strcpy(info, argc_num);
	strcat(info, "\n\n");

	for(i = 0; i < argc; ++i)
	{
		if(i > 0) strcat(info, "\n");
		strcat(info, argv[i]);
	}

	strcat(info, "\n\n");



	for(i = 0; envp[i] != NULL; ++i)
	{
		if(i > 0) strcat(info, "\n");
		strcat(info, envp[i]);
	}

	strcat(info, "\n\n");
	char env_counter[5];
	sprintf(env_counter, "%d", i);


	strcat(info, env_counter);

	strcat(info,"\n");
	strcat(info,"\0");


	char ch = 0;

	i = 0;

	for(i = 0; i < strlen(info); ++i)
	{
		ch = info[i];
		write(fd, &ch, 1);
	}
    free(info);
    free(str);
    
	sf_close(fd);
}

int create_wd(int argc, char ** argv, char **envp)
{
	struct sigaction act;
	act.sa_sigaction = &client_sig_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	/*memset (&act, '\0', sizeof(act));*/

	pid_t pid = getpid();
	char pid_num[10];
	sprintf(pid_num, "%d", (int)pid);
	char* file_path = malloc(sizeof(char)*30);
	strcpy(file_path, pid_num);
	strcat(file_path, ".info");
	create_file(argc, argv, envp, "/tmp/student/app_name", file_path, pid);

	/*wd exist check*/

	if(strcmp(argv[argc - 1], "flag" )!=0)
	{

		pid = fork();

		if (pid < 0)
		{
			 printf("Failed to fork()\n");
			 return -1;
		}

		else if (pid == 0)
		{
			execlp("./testwatch.out" , pid_num, file_path, (char *)0);
			/*execlp("./testwatch.out" ,"./testwatch.out");*/
		}

		else
		{

			while(1)
			{
				printf("%s\t%s\n", argv[0], argv[1]);
				sleep(1);
			}

		}

	}

	else
	{
		while(1)
		{
			printf("%s\t%s\n", argv[0], argv[1]);
			sleep(1);
		}
	}

    return 0;
}

int destroy_wd()
{
	return 0;
}
