/*
 * testwatch.c
 *
 *  Created on: Dec 16, 2014
 *      Author: student
 */
#include "watch.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "file_safe.h"

volatile sig_atomic_t counter = 0;

void sig_handler_live()
{
	counter = 0;
	printf("\tWD\n");
	sleep(1);
}

void sig_handler_die(pid_t param)
{
	/*kill(getppid(), SIGTERM);*/
	printf("parent process was killed\n");
    /*waitpid(getppid(), NULL, 0);*/
}

char** read_file(pid_t pid, char* file_name)
{
	char* str = malloc(strlen("/tmp/student/app_name") + strlen(file_name)+1);
	str = strcat(str, "/tmp/student/app_name");
	str = strcat(str, "/");
	str = strcat(str, file_name);

	int fd = sf_open(str);

	char **info = malloc(sizeof(char*) * 4);

	info[0] = malloc(sizeof(char)*10);
	memset(info[0], 0, sizeof(char)*10);
	info[1] = malloc(sizeof(char)*1000);
	memset(info[1], 0, sizeof(char)*1000);
	info[2] = malloc(sizeof(char)*4000);
	memset(info[2], 0, sizeof(char)*4000);
	info[3] = malloc(sizeof(char)*10);
		memset(info[3], 0, sizeof(char)*10);
	int i = 0, j = 0;
	char ch;
	lseek(fd, 0, SEEK_SET);

	for(; j < 4; )
	{
		read(fd, &ch, 1);

		if(ch == '\n')
		{

			read(fd, &ch, 1);

			if(ch == '\n')
			{
				++j;
				i = 0;
				read(fd, &ch, 1);
				if(j == 4) break;

			}

			else
			{
				info[j][i] = '\n';
				++i;
			}
		}

		info[j][i] = ch;
		++i;
	}



	printf("\ninfo[0]: %s\ninfo[1]: %s\ninfo[2]: %s\ninfo[3]: %s\n", info[0], info[1], info[2], info[3]);
	sf_close(fd);
	return info;
}

int main(int argc, char ** argv, char ** envp)
{

	signal(SIGUSR1, sig_handler_live);
	/*signal(SIGUSR2, sig_handler_die);*/

	pid_t pid = atoi(argv[0]);

	printf("%d\t%d\t%d\n\n\n", pid, getpid(), getppid());


	int i = 0, j = 0, x = 0;

	char ** path = read_file(pid, argv[1]);

	int val1 = atoi(path[0]);
	int val2 = atoi(path[3]);


	char **args = malloc(sizeof(char*) * (val1 + 1));
	printf("%d", val1);
	/*char **envpp = malloc(sizeof(char*) * val2);*/



	strcat(path[1], "\0");

	for(i = 0; i < val1; ++i)
	{
		args[i] = malloc(sizeof(char)*100);

		for(j = 0; path[1][x]!='\n' && path[1][x]!='\0' ; ++j, ++x)
		{
			args[i][j] = path[1][x];
			printf("%s\n", args[i]);
		}

		args[i][j] = '\0';

		j = 0;
		++x;
	}

	args[i] = malloc(sizeof(char)*100);
	char flag[] = "flag";
	for(j = 0; j < 5; ++j)
	{
		args[i][j] = flag[j];
	}
	/*for(i = 0; i < 2; ++i)
	{
		envpp[i] = malloc(sizeof(char)*100);
		for(j = 0, x = 0; path[2][x]!='\n'; ++j, ++x)
		{
			printf("%c", path[2][x]);
		}
	}*/

	/*for(i = 0; i < 2; ++i)
	{

		envpp[i] = malloc(sizeof(char)*100);
		for(j = 0, x = 0; path[2][x]!='\n' ; ++j, ++x)
		{

			args[i][j] = path[2][x];
		}
		envpp[i][j] = '\0';


		j = 0;
		++x;

	}*/

	/*for(i = 0; i < atoi(path[0]); ++i)
	{

		args[i] = malloc(sizeof(char)*100);
		for(j = 0, x = 0; path[1][x]!='\n' ; ++j, ++x)
		{

			args[i][j] = path[1][x];
		}
		args[i][j] = '\0';


		j = 0;
		++x;

	}*/

	printf("args[0]: %s\targs[1]: %s\n", args[0], args[1]);

	/*printf("aaaaaa\n%s\n", path[0]);*/

	/*char *envp_ar = malloc(sizeof(char*) * atoi(path[3]));*/

	i = 0;

	while(1) {

       kill(pid, SIGUSR1);
       sleep(2);
       printf("%d\n", counter);
       ++counter;

       if(counter == 5)
        {
    	    printf("counter == 5\n");
    	    counter++;
            kill(pid, SIGTERM);
            waitpid(pid, NULL, 0);

            pid = fork();

            if (pid < 0)
            {
            	printf("Failed to fork()\n");
            	return -1;
            }

            else if (pid == 0)
            {
            	/*execvpe("./testclient.out", args, envp);*/
            	execve("./testclient.out", args,envp);
            }

        }

    }


	return 0;
}
