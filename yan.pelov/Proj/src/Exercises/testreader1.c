/*
 *  IPC exc: message queue -
 *
 * 	Name: Noam Moshe
 *	Date: 29.12.14
 *	reviewr: Alex Briskin
 *
 */


/* Libs */
#include <stdio.h>      /* printf()					*/
#include <unistd.h>     /* close(),read(),write()	*/
#include <fcntl.h>      /* open()   				*/
#include <sys/msg.h> 	/* msqid()					*/
#include <stddef.h>		/* 							*/

/* Functions */
void writer (const char* message, int fd);
void reader (int fd, int count);

struct msgbuf
{
    long mtype;
    char message[20];

}msgbuf;

/****************************/
/*** Main ****/

int main (int argc, char** argv,char** envp)
{
	/* path for createing a uniqe key for ftok() */
	const char *path = "/home/student/Desktop/message q/create.c";

	/* create a uniqe key for mssget() function */
	key_t key = ftok (path, 5);

	/* connect to a queue */
	int msqid = msgget (key, 0666);

	/**************/

	/* decleration of queue message struct  */
	struct msgbuf msgbuf_ptr;

	/* first read */
	msgrcv(msqid, &msgbuf_ptr, sizeof(msgbuf) - sizeof(long), 1, 0);
	printf("%s\n", msgbuf_ptr.message);

	/* second read */
	/*msgrcv(msqid, &msgbuf_ptr, sizeof(msgbuf) - sizeof(long), 2, 0);
	printf("%s\n", msgbuf_ptr.message);*/

	/* third read */
	/*msgrcv(msqid, &msgbuf_ptr, sizeof(msgbuf) - sizeof(long), 3, 0);
	printf("%s\n", msgbuf_ptr.message);*/

	return (0);
}

/****************************/
