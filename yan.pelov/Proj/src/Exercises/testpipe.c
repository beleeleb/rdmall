/*
 * IPC exc: PIPE - Using a Pipe to Communicate with a Child Process
 *           (A pipe is a communication device that permits unidirectional
 *		      communication).
 *
 *  Created on: Dec 29, 2014
 *      Author: Yael Ben Shalom
 */


/* Libs */
#include <stdlib.h>    /*  */
#include <stdio.h>     /*  */
#include <unistd.h>    /*  */
#include <sys/types.h>

/* Functions */
void writer (const char* message, int fd);
void reader (int fd, int count);


/****************************/
/*** Main ****/

int main (int argc, char** argv,char** envp)
{
/*
 * Create a pipe. File descriptors for the two ends of the pipe are
 * placed in fds.
 * pipe fd: fd[0] - read fd, fd[1] - write fd
 */

	int fds[2];
	if (pipe (fds)) return (1);			/* pipe returns 0 on success */

	pid_t pid = fork ();   /* Forks a child process. */

	if (pid == (pid_t) 0)   /* child */
	{
		while (1)
		{
			reader (fds[0], 5);
			writer ("pong", fds[1]);
		}

		/* Close our copy of read and write end of the file descriptor. */
		close (fds[0]);
		close (fds[1]);
	}
	else                     /* parent */
	{
		while (1)
		{
			writer ("ping",fds[1]);
			reader (fds[0], 5);
		}

		/* Close our copy of read and write end of the file descriptor. */
		close (fds[0]);
		close (fds[1]);
	}

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
	write (fd, message , 5);
	sleep (1);												 /* Snooze a while. */
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
	sleep (1);												 /* Snooze a while. */
}
