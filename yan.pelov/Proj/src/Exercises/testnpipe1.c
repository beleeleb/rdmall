/*
 *  IPC exc: FIFO (named pipe) - makes a FIFO special file with name pathname.
 *			A FIFO special file is similar to a pipe, except that it is created
 *		   in a different way.  Instead of being an anonymous communications
 *		   channel, a FIFO special file is entered into the filesystem by
 *		   calling mkfifo().
 */


/* Libs */
#include <stdio.h>     /* printf() */
#include <unistd.h>    /* close(),read(),write() */
#include <fcntl.h>     /* open()   */
#include <sys/types.h> /* mkfifo() */
#include <sys/stat.h>  /* mkfifo() */


/* Functions */
void writer (const char* message, int fd);
void reader (int fd, int count);

/****************************/
/*** Main ****/

int main (int argc, char** argv,char** envp)
{

	/* create the FIFO (named pipe) */
	char* fifo = "/tmp/myfifo";
 	printf("return value myfifo: %d\n", mkfifo(fifo, 0666));
    int fd = open(fifo, 0666);
	if (fd == (-1)) return (-1);

	while (1)
	{
		writer ("pong", fd);
		reader (fd, 5);
	}

	/* Close our copy of read and write end of the file descriptor. */
	if (close (fd)) return (-1);

	 /* remove the FIFO */
	unlink(fifo);

	return (0);
}

/****************************/
/*** Functions implement ****/

/**************/

/*
 *  Write COUNT copies of MESSAGE to STREAM, pausing for a second
 *  between each.
 */

void writer (const char* message, int fd)
{
	/* Write the message to the stream, and send it off immediately. */

	write (fd, message , 5);
	sleep (1);			 /* Snooze a while. */
}

/**************/

/*
 * Read random strings from the stream as long as possible.
 */

void reader (int fd, int count)
{
	char buffer[30];

	read (fd, buffer, count);
	printf("%s from: %d\n", buffer,getpid());
	sleep (1);			 /* Snooze a while. */
}






