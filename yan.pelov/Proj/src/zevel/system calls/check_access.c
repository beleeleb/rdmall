#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int res;

	res = access(argv[1], F_OK);

	printf("\nres: %d\n", res);

	if(errno == ENOENT) printf("the file doesn't exist\n");
	else if(errno == EACCES) printf("no access to file\n");

	res = access(argv[1], R_OK);

	if(res == 0) printf("\nfile is readble\n");
	else printf("\nfile isn't readble\n");

	res = access(argv[1], W_OK);

	if(res == 0) printf("\nfile is writeble\n");
	else if(errno == EACCES) printf("\nfile isn't writeble\n");
	else if(errno == EROFS) printf("\nfile isn't writeble, read only file system\n");

	
	return 0;
}
