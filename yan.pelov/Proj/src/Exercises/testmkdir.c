/*
 * testmkdir.c
 *
 *  Created on: Dec 14, 2014
 *      Author: student
 */


#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	if(mkdir("yan", 0) != 0)
	{
		printf("can't lock");
	}

	printf("lock hash been set\n");
	sleep(20);
	rmdir("/home/student/yan");

	return 0;
}
