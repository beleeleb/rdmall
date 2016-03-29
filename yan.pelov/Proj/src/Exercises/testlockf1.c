#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lockf1.h"
#include <string.h>


int main(int argc, char ** argv)
{

	int fd;

	fd = open("123.txt", O_WRONLY);

	int i;

	srand(time(NULL));

	while(lockf(fd, F_TEST, 0) == 0)
	{
		printf("process %c couldn't lock file\n", argv[1][0]);
	}

	printf("process %c locked file\n", argv[1][0]);
	lockf(fd, F_LOCK, 0);
	for(i = 0; i < 10; ++i)
	{
		write(fd, argv[1], 1);
		printf("process %c wrote to file\n", argv[1][0]);
		sleep(rand()%4);
	}

	while(lockf(fd, F_ULOCK, 0) == -1)
	{
		printf("process %c couldn't unlock file\n", argv[1][0]);
	}

	printf("process %c unlocked file\n", argv[1][0]);

	return 0;
}

