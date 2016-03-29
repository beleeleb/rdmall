/*
 * testflock1.c
 *
 *  Created on: Dec 11, 2014
 *      Author: student
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "flock1.h"
#include <string.h>
#include <sys/file.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char ** argv)
{
	int fd = open("123.txt", O_RDWR);
	if(fd == -1) return 1;

	srand(time(NULL));
	int i;

	sleep(rand()%2);

	while(flock(fd, LOCK_EX) == -1)
	{
		printf("process %c couldn't lock file\n", argv[1][0]);
	}

	printf("process %c locked the file\n", argv[1][0]);

	for(i = 0; i < 10; ++i)
	{
		write(fd, argv[1], 1);
		printf("process %c wrote to file\n", argv[1][0]);
		sleep(rand()%2);
	}

	while(flock(fd, LOCK_UN) == -1)
	{
		printf("process %c couldn't unlock file\n", argv[1][0]);
	}

	printf("process %c unlocked the file\n", argv[1][0]);

	close(fd);
	return 0;
}


