#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "fcntl1.h"
#include <time.h>
#include <string.h>

int main(int argc, char** argv)
{
	int fd, i;
	struct flock fl1;

	srand(time(NULL));

	fd = open("123.txt", O_RDWR);
	if(fd == -1) return 1;

	fl1.l_type = F_WRLCK;
	fl1.l_whence = SEEK_SET;
	fl1.l_start = 0;
	fl1.l_len = 0;

	sleep(rand()%5);

	while(fcntl(fd, F_SETLK, &fl1) == -1)
	{
		printf("process %c failed to lock the file\n", argv[1][0]);
		sleep(rand()%2);
	}

	printf("process %c locked the file\n", argv[1][0]);

	for(i = 0; i < 10 ; ++i)
	{
		if(write(fd, argv[1], 1))
		{
			printf("process %c wrote on file\n", argv[1][0]);
			sleep(rand()%2);
		}
	}

	fl1.l_type = F_UNLCK;
	if(fcntl(fd, F_SETLK, &fl1) == -1)
	{
		printf("process %c failed to unlock the file\n", argv[1][0]);
	}

	else printf("process %c unlocked the file\n", argv[1][0]);

	close(fd);

	return 0;

}
