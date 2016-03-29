#include <stdio.h>
#include "ring_buf.h"

extern void print_rbuf(rbuf_t* rbuffer);

extern iterator rbuf_temp(rbuf_t* rbuffer);

int main (int argc, char** argv, char** evpm)
{
	rbuf_t *mybuf = NULL;

	data_t *mydata = NULL;

	mybuf = rbuf_create(8);

	mydata = rbuf_read(mybuf);

	rbuf_write(mybuf, (void*)100);

	rbuf_write(mybuf, (void*)200);

	rbuf_write(mybuf, (void*)300);

	rbuf_write(mybuf, (void*)400);

	rbuf_write(mybuf, (void*)500);

	rbuf_write(mybuf, (void*)600);

	rbuf_write(mybuf, (void*)700);

	rbuf_write(mybuf, (void*)800);

	rbuf_write(mybuf, (void*)900);

	print_rbuf(mybuf);

	mydata = rbuf_read(mybuf);

	mydata = rbuf_read(mybuf);

	mydata = rbuf_read(mybuf); 

	mydata = rbuf_read(mybuf);

	mydata = rbuf_read(mybuf);

	mydata = rbuf_read(mybuf);

	mydata = rbuf_read(mybuf);

	mydata = rbuf_read(mybuf);

	mydata = rbuf_read(mybuf);

	printf("%ld", (long)mydata);

	rbuf_write(mybuf, (void*)900);

	rbuf_write(mybuf, (void*)1000);

	rbuf_write(mybuf, (void*)1100);

	rbuf_write(mybuf, (void*)1200);

	print_rbuf(mybuf);

	rbuf_erase(mybuf, rbuf_temp(mybuf));

	print_rbuf(mybuf);

	rbuf_destroy(mybuf);

	return 0;
}
