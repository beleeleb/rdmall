#include "fmb_alloc.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define ALIGNMENT sizeof(size_t)
#define ALIGN(size) ((size)+(ALIGNMENT-1)) & ~(ALIGNMENT-1)

typedef struct seg_header
{
	size_t next_free;
	size_t block_size;
	size_t n_block;
} seg_header;

typedef struct blk_header
{
#ifdef DEBUG
	size_t offset;
#endif /*DEBUG*/
	size_t next;
}blk_header;


int fmb_init(fmb_p seg_ptr, size_t seg_size, size_t block_size)
{
	if(seg_ptr == NULL) return -1;

	if(seg_size < (sizeof(seg_header) + sizeof(blk_header) + block_size))
	{
		return -1;
	}

	else
	{
		seg_header *myseg = NULL;
		myseg = (seg_header*)malloc(sizeof(seg_header));
		myseg->next_free = sizeof(seg_header);
		myseg->block_size = block_size;
		int max = (seg_size - sizeof(seg_header)) / (ALIGN(sizeof(blk_header) + myseg->block_size));

		myseg->n_block = max;
		/*memcpy(seg_ptr, myseg, sizeof(seg_header));*/

		*(size_t*)(seg_ptr) = myseg->next_free;
		*(size_t*)(seg_ptr + ALIGNMENT) = myseg->block_size;
		*(size_t*)(seg_ptr + (2*ALIGNMENT)) = myseg->n_block;


		int i = 0;

		blk_header **myblk = (blk_header**)malloc(sizeof(blk_header*) * myseg->n_block);

		for(i = 0; i < (myseg->n_block - 1) ; ++i)
		{

			myblk[i] = (blk_header*)malloc(sizeof(blk_header));
			myblk[i]->next = sizeof(seg_header) + (sizeof(blk_header) + block_size) * (i + 1);
			*(size_t*)(seg_ptr + sizeof(seg_header) + (sizeof(blk_header) + myseg->block_size) * i) = myblk[i]->next;
#ifdef DEBUG
	myblk[i]->offset = sizeof(seg_header) + (sizeof(blk_header) + myseg->block_size) * i;
	*(size_t*)(seg_ptr + sizeof(seg_header) + (sizeof(blk_header) + myseg->block_size) * i + ALIGNMENT) = myblk[i]->offset;
#endif /*DEBUG*/
		}

		myblk[i] = (blk_header*)malloc(sizeof(blk_header));
		myblk[i]->next =  -1;
		*(size_t*)(seg_ptr + sizeof(seg_header) + (sizeof(blk_header) + myseg->block_size) * i) = myblk[i]->next;
#ifdef DEBUG
		myblk[i]->offset = sizeof(seg_header) + (sizeof(blk_header) + myseg->block_size) * i;
		*(size_t*)(seg_ptr + sizeof(seg_header) + (sizeof(blk_header) + myseg->block_size) * i + ALIGNMENT) = myblk[i]->offset;
#endif /*DEBUG*/
	}
	return 0;
}

void* fmb_alloc(fmb_p seg_ptr)
{
	size_t temp = *(size_t*)(seg_ptr);

	if(temp == -1)
	{
		return NULL;
	}
	/**(size_t*)(seg_ptr) = *(size_t*)(seg_ptr + sizeof(seg_header) + (sizeof(blk_header) + (*(size_t*)(seg_ptr + ALIGNMENT))) * temp);
	*(size_t*)(seg_ptr + sizeof(seg_header) + (sizeof(blk_header) + (*(size_t*)(seg_ptr + ALIGNMENT))) * temp) = temp;

	return (seg_ptr + sizeof(seg_header) + (sizeof(blk_header) + (*(size_t*)(seg_ptr + ALIGNMENT))) * (temp)) + sizeof(blk_header);*/
	*(size_t*)(seg_ptr) = *(size_t*)(seg_ptr + temp);
	*(size_t*)(seg_ptr + temp) = temp;
	return seg_ptr + temp + sizeof(blk_header);
}

void fmb_free(void* block_ptr)
{
    long temp = *(long*)(block_ptr - sizeof(blk_header));
    void *head = block_ptr - sizeof(blk_header) - temp;
    *(long*)(block_ptr - sizeof(blk_header)) = *(long*)(head);
    *(long*)(head) = temp;
    /*memset(block_ptr, 0, *(size_t*)(head + ALIGNMENT));*/
    *(long*)block_ptr = 0;
    /*void * ptr = block_ptr - (sizeof(blk_header)) * (temp + 1) - (ALIGNMENT * temp) - sizeof(seg_header);
    *(size_t*)(block_ptr - sizeof(blk_header)) = *(size_t*)(ptr);
    *(size_t*)(ptr) = temp;*/
    return;
}

size_t calc_me(size_t n_blocks, size_t block_size)
{
	return (sizeof(seg_header) + (sizeof(blk_header) + ALIGN(block_size)) * n_blocks);
}
