/*
 * shmvs.h
 *
 *  Created on: Jan 1, 2015
 *      Author: student
 */

#ifndef SHMVS_H_
#define SHMVS_H_

#include <stdlib.h>

typedef void* shmvs_p;
typedef int shmvid_t;

shmvs_p shmvs_create (size_t size, char * id, unsigned short int max_clients);

void shmvs_destroy (shmvs_p seg);

shmvs_p shmvs_attach (shmvid_t shmid);

int shmvs_detach (shmvs_p seg);

void* shmvs_alloc (shmvs_p seg, size_t size);

void shmvs_free (void* data);

#endif /* SHMVS_H_ */
