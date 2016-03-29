/*
 * shmvs.c
 *
 *  Created on: Jan 1, 2015
 *      Author: student
 */

#include "shmvs.h"
#include "vmb.h"
#include "fcntl.h"


#include <semaphore.h>
#include <sys/types.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

struct shmv_header
{
	int semid;
	int key;
	unsigned short int max_clients;
	int yyy;
};

struct shmv_block_header
{
	size_t offset;
};

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *__buf;
};

static int sem_create(int semid, unsigned short int max_clients);
static int sem_attach(int semid);
static int sem_detach(int semid);
static int write_lock(int semid, unsigned short int max_clients);
static int write_unlock(int semid, unsigned short int max_clients);
static int read_lock(int semid);
static int read_unlock(int semid);

shmvs_p shmvs_create (size_t size, char * id, unsigned short int max_clients)
{
	assert(size && max_clients);

	size_t mysize = size + sizeof(struct shmv_header);

	if(size <= 0)
	{
			return NULL;
	}

	char * dir_path = "/tmp";
	char * str = NULL;

	if(id == NULL)
	{
		id = "stam.txt";
	}

	str = malloc(strlen(dir_path) + 1 + strlen(id)+1);
	str = strcat(str, dir_path);
	str = strcat(str, "/");
	str = strcat(str, id);

	int fd = open(str, O_RDWR | O_CREAT , 0777);
	close(fd);

	key_t mykey = ftok(str, 3);

	if(mykey < 0)
	{
		perror("ftok");
		return NULL;
	}

	int semid = semget(mykey, 2,  0777 | IPC_CREAT | IPC_EXCL);

	if(semid < 0)
		{
			if(errno != EEXIST)
			{
				perror("semget");
				return -1;
			}

			else
			{
				semid = semget(mykey, 2,  0777 | IPC_CREAT);
				if(semid < 0)
				{
					perror("semget");
					return -1;
				}
			}
		}

		else
		{
			if(sem_create(semid, max_clients) < 0)
			{
				return -1;
			}
		}

		shmvs_p myptr = NULL;
		shmvid_t myshmid =  shmget(mykey, mysize, IPC_CREAT | IPC_EXCL| 0777);

		if(myshmid < 0)
		{
			if(errno == EEXIST)
			{
				myshmid =  shmget(mykey, mysize, IPC_CREAT | 0777);
				{
					if(myshmid < 0)
					{
						perror("shmget");
						return -1;
					}

					else
					{
						/* I need to do a check of semaphore before attachment*/
						myptr = shmat(myshmid, NULL, 0);

						if(myptr == (void*)-1)
						{
							perror("shmat");
							return -1;
						}

						sem_attach(semid);

						return myptr;
					}
				}


			}

			else
			{
				perror("shmget");
				return -1;
			}

		}


		myptr = shmat(myshmid, NULL, 0);

		if(myptr == (void*)-1)
		{
			perror("shmat");
			return -1;
		}

		sem_attach(semid);

		struct shmv_header my_shm;
		my_shm.semid = semid;
		my_shm.key = mykey;
		my_shm.max_clients = max_clients;
		*(struct shmv_header*)myptr = my_shm;

		write_lock(semid, max_clients);
		vmb_init(myptr + sizeof(struct shmv_header), mysize - sizeof(struct shmv_header));
		write_unlock(semid, max_clients);

		return myptr;

}

void shmvs_destroy (shmvs_p seg)
{
	unsigned short int values[2];

	if(seg == NULL)
	{
		return;
	}

	struct shmv_header temp_header = (*(struct shmv_header*)seg);

	shmvs_detach(seg);

	if(semctl(temp_header.semid, 0, GETALL, &values) < 0)
	{
		perror("semctl:");
		return;
	}

	struct sembuf sbuf = { 0, -(temp_header.max_clients), SEM_UNDO};

	if(semop(temp_header.semid, &sbuf, 1) < 0)
	{
		perror("semop");
		return;
	}

	if(semctl(temp_header.semid, 0, IPC_RMID)<0)
	{
		perror("semctl");
		return;
	}

	shmvid_t id = shmget(temp_header.key, 0, 0);

	if(shmctl(id, IPC_RMID, 0) < 0)
	{
		perror("shmctl");
		return;
	}

	return;
}

shmvs_p shmvs_attach (shmvid_t shmid)
{
	shmvs_p myptr = shmat(shmid, NULL, 0);

	if(myptr == (void*)-1)
	{
		perror("shmat");
		return (void*)-1;
	}

	sem_attach((*(struct shmv_header*)myptr).semid);

	return myptr;
}

int shmvs_detach (shmvs_p seg)
{
	int temp = (*(struct shmv_header*)seg).semid;
	if(shmdt(seg) < 0)
	{
		perror("shmdt");
		return -1;
	}

	sem_detach(temp);

	return 0;
}

void* shmvs_alloc (shmvs_p seg, size_t size)
{
	if(seg == NULL)
	{
		return NULL;
	}

	int temp = (*(struct shmv_header*)seg).semid;
	void * ptr = NULL;

	write_lock(temp, (*(struct shmv_header*)seg).max_clients);
	ptr = vmb_alloc(seg + sizeof(struct shmv_header), size + sizeof(struct shmv_block_header));

	write_unlock(temp, (*(struct shmv_header*)seg).max_clients);

	if(ptr == NULL)
	{
		return NULL;
	}

	*(size_t*)(ptr) = ptr - seg;
	return ptr + sizeof(struct shmv_block_header);

}

void shmvs_free (void* data)
{
	if(data == NULL)
	{
		return;
	}

	void * shm_blk_head = data - sizeof(struct shmv_block_header);
	void * shm_seg = shm_blk_head - *(size_t*)(shm_blk_head);
	int temp = (*(struct shmv_header*)shm_seg).semid;


	unsigned short int max_clients = (*(struct shmv_header*)shm_seg).max_clients;
	write_lock(temp, max_clients);
	vmb_free(shm_blk_head);
	write_unlock(temp, max_clients);
	return;

}

static int sem_create(int semid, unsigned short int max_clients)
{
	union semun arg;
	unsigned short values[2];
	values[0] = max_clients;
	values[1] = max_clients;
	arg.array = values;

	if(semctl(semid, 0, SETALL, arg) < 0)
	{
		perror("semctl:");
		return -1;
	}

    return 0;
}

static int sem_attach(int semid)
{

	struct sembuf sbuf = { 0, -1, SEM_UNDO};

	if(semop(semid, &sbuf, 1) < 0)
	{
		perror("semop");
		return -1;
	}

	return 0;
}

static int sem_detach(int semid)
{
	struct sembuf sbuf = { 0, 1, SEM_UNDO};

	if(semop(semid, &sbuf, 1) < 0)
	{
		perror("semop");
		return -1;
	}

	return 0;
}

static int write_lock(int semid, unsigned short int max_clients)
{
	struct sembuf sbuf = { 1, -max_clients, SEM_UNDO};

	if(semop(semid, &sbuf, 1) < 0)
	{
		perror("semop");
		return -1;
	}

	/*unsigned short int values[2];

	if(semctl(semid, 0, GETALL, &values) < 0)
	{
		perror("semctl:");
		return -1;
	}

	printf("sem1[0] = %d/tsem2[1] = %d", values[0], values[1]);*/

	return 0;
}

static int write_unlock(int semid, unsigned short int max_clients)
{
	struct sembuf sbuf = { 1, max_clients, SEM_UNDO};

		if(semop(semid, &sbuf, 1) < 0)
		{
			perror("semop");
			return -1;
		}

		return 0;

}

static int read_lock(int semid)
{
	struct sembuf sbuf = { 1, -1, SEM_UNDO};

		if(semop(semid, &sbuf, 1) < 0)
		{
			perror("semop");
			return -1;
		}

		return 0;
}

static int read_unlock(int semid)
{
	struct sembuf sbuf = { 1, 1, SEM_UNDO};

		if(semop(semid, &sbuf, 1) < 0)
		{
			perror("semop");
			return -1;
		}

		return 0;
}
