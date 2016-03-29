#include "shmfs.h"
#include <semaphore.h>
#include <sys/types.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "fmb_alloc.h"
#include <stdio.h>

#define ALIGNMENT sizeof(size_t)

#define ALIGN(size) ((size)+(ALIGNMENT-1)) & ~(ALIGNMENT-1)

static int write_lock(int semid, unsigned short int max_clients);
static int write_unlock(int semid, unsigned short int max_clients);

static int read_lock(int semid);
static int read_unlock(int semid);

static int sem_create(int semid, unsigned short int max_clients);

static int sem_attach(int semid);
static int sem_detach(int semid);

struct shm_header
{
	int		semid;
	key_t  key;
};


struct shm_block_header
{
	size_t offset;
};

union semun1{
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *__buf;
};


shmfs_p shmfs_create (size_t n_blocks, size_t block_size, char * id, unsigned short int max_clients/*, char * path ,int path_id*/)
{
	assert(n_blocks && block_size && max_clients);

	if(n_blocks <= 0 || block_size <= 0)
	{
		return -1;
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
		return -1;
	}

	size_t mysize = calc_me(n_blocks, ALIGN(block_size + sizeof(struct shm_block_header)));
	mysize = mysize + sizeof(struct shm_header);

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

	shmfs_p myptr = NULL;
	shmid_t myshmid =  shmget(mykey, mysize, IPC_CREAT | IPC_EXCL| 0777);

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

	/* I need to do a check the semaphore before attachment*/

	myptr = shmat(myshmid, NULL, 0);

	if(myptr == (void*)-1)
	{
		perror("shmat");
		return -1;
	}
    
	sem_attach(semid);

	struct shm_header my_shm;
	my_shm.semid = semid;
	my_shm.key = mykey;
	*(struct shm_header*)myptr = my_shm;

	write_lock(semid, max_clients);

	if(fmb_init(myptr + sizeof(struct shm_header), mysize - sizeof(struct shm_header), ALIGN(block_size + sizeof(struct shm_block_header))) < 0)
	{
		return -1;
	}

	write_unlock(semid, max_clients);

	return myptr;

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


void shmfs_destroy (shmfs_p seg)
{

	unsigned short int values[2];

    if(seg == NULL)
    {
        return;
    }

	struct shm_header temp_header = (*(struct shm_header*)seg);

	 shmfs_detach(seg);

	if(semctl(temp_header.semid, 0, GETALL, &values) < 0)
	{
		perror("semctl:");
		return;
	}

	struct sembuf sbuf = { 0, -20, SEM_UNDO};

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



	shmid_t id = shmget(temp_header.key, 0, 0);

	if(shmctl(id, IPC_RMID, 0) < 0)
	{
		perror("shmctl");
		return;
	}

	return;

}

shmfs_p shmfs_attach (shmid_t shmid)
{
	/* I need to do a check the semaphore before attachment*/

	shmfs_p myptr = shmat(shmid, NULL, 0);

	if(myptr == (void*)-1)
	{
		perror("shmat");
		return (void*)-1;
	}

	sem_attach((*(struct shm_header*)myptr).semid);

	return myptr;
}

int shmfs_detach (shmfs_p seg)
{
	int temp = (*(struct shm_header*)seg).semid;
	if(shmdt(seg) < 0)
	{
		perror("shmdt");
		return -1;
	}

	sem_detach(temp);

	return 0;
}


static int sem_create(int semid, unsigned short int max_clients)
{
	union semun1 arg;
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

void* shmfs_alloc (shmfs_p seg)
{
	if(seg == NULL)
	{
		return NULL;
	}

	int temp = (*(struct shm_header*)seg).semid;
	void * ptr = NULL;

	write_lock(temp, 20);
	ptr = fmb_alloc(seg + sizeof(struct shm_header));
	write_unlock(temp, 20);

	if(ptr == NULL)
	{
		return NULL;
	}

	*(size_t*)(ptr) = ptr - seg;
	return ptr + sizeof(struct shm_block_header);

}

void shmfs_free (void* data)
{
	if(data == NULL)
	{
		return;
	}

	void * shm_blk_head = data - sizeof(struct shm_block_header);
	int temp = (*(struct shm_header*)(shm_blk_head - *(size_t*)(shm_blk_head))).semid;
	write_lock(temp, 20);
	fmb_free(shm_blk_head);
	write_unlock(temp, 20);
	return;
}
