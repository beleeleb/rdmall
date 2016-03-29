#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#

int main(int argc, char ** argv)
{
	char * path = argv[1];
	int fd;
	struct flock lock;
	printf("\nthe file is: %s\n", path);

	fd = open(path, O_WRONLY);
    
	printf("locking begins\n");
	memset(&lock, 0, sizeof(lock));
	lock.l_type = F_WRLCK; /*or F_WRLCK*/
	fcntl(fd, F_SETLKW, &lock);
    getchar();
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &lock);
    printf("File unlocked\n");

	close(fd);
	return 0;
}
