/*
 *  IPC exc: message queue -
 *
 * 	Name: Noam Moshe
 *	Date: 29.12.14
 *	reviewr: Alex Briskin
 *
 */


/* Libs */
#include <sys/msg.h> 	/* msqid() ,msgget() ,ftok()	*/
#include <string.h>		/* strcpy() 					*/

/* Functions */
void writer (const char* message, int fd);
void reader (int fd, int count);

struct msgbuf
{
    long mtype;
    char message[20];

}msgbuf;

/****************************/
/**** Main ****/

int main (int argc, char** argv,char** envp)
{
	/* path for createing a uniqe key for ftok() */
	const char *path = "/home/student/Desktop/message q/create.c";

	/* create a uniqe key for mssget() function */
	key_t key = ftok (path, 5);

	/* connect to a queue */
	int msqid = msgget (key, IPC_CREAT | 0666);

	/**************/

	/* decleration of queue message struct */
	struct msgbuf msg;

	/* first message */
	msg.mtype = 1;
	strcpy(msg.message,"1st message");
	msgsnd (msqid, &msg, (sizeof(msgbuf) - sizeof(long)), 0);

	/* second message */
	msg.mtype = 2;
	strcpy(msg.message,"2nd message");
	msgsnd (msqid, &msg, (sizeof(msgbuf) - sizeof(long)), 0);

	/* third message */
	msg.mtype = 3;
	strcpy(msg.message,"3rd message");
	msgsnd (msqid, &msg, (sizeof(msgbuf) - sizeof(long)), 0);


	return (0);
}

