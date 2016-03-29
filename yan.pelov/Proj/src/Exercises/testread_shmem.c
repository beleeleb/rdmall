/*
 *  IPC exc: message queue -
 *
 * 	Name: Yael Ben Shalom
 *	Date: 29.12.14
 *	reviewr:
 *
 */


/* Libs */
#include <stdio.h>	/* printf() */
#include <sys/ipc.h>	/* shmat() */
#include <sys/shm.h>	/* shmat() */
#include <stdlib.h>

/****************************/
/**** Main ****/

int main (int argc, char** argv,char** envp)
{
	size_t size = 500;
	/* path for createing a uniqe key for ftok() */
	const char *path = "/home/student/eclipse/exe/ping-pong/pipe.c";

	/* create a uniqe key for mssget() function */
	key_t key = ftok (path, 5);

	int mem_id = 0;
	void* mem_ptr;

	/* creates a handle to the memory segment */
	if ((mem_id = shmget (key, size, IPC_CREAT | 0666)) == (-1))	return (-1);

	/* turns the handle to a pointer to the mem */
	if ((mem_ptr = shmat(mem_id, (void *)0, 0)) == (char*)(-1))		return (-1);

	printf("in the memory: %s\n", (char*)mem_ptr);

	return (0);
}

