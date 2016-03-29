#include "file_safe.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

int main(int argc, char ** argv)
{

 int fd = 0;
    srand(time(NULL));
	sf_create("/home/student/Dropbox/progs/Proj/src/utils/home", "123.txt");
    fd = sf_open("/home/student/Dropbox/progs/Proj/src/utils/home/123.txt");

    if(rand()%1 == 0)
    printf("lock result: %d\n", sf_wlock(fd));
    else
    printf("lock result: %d\n", sf_rlock(fd));

    getchar();
    int i;
    int ch = 0;
    char mystr[6];
    for(i = 0; i < 5; ++i)
    {
    	write(fd, argv[1], 1);
    	printf("%c wrote\n", argv[1][0]);
    	sleep(rand()%4);
    }

    lseek(fd, 0, SEEK_SET);

    for(i = 0; i < 5; ++i)
    {
    	read(fd, &ch, 1);
    	mystr[i] = ch;
    }

    mystr[5] = '\0';

    printf("string: %s\n", mystr);

    printf("unlock result: %d\n", sf_wunlock(fd));

    sf_close(fd);
    sf_destroy("/home/student/Dropbox/progs/Proj/src/utils/home/123.txt");

	return 0;
}

