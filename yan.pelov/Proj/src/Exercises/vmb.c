/*
 * vmb.c
 *
 *  Created on: Dec 23, 2014
 *      Author: student
 */

#include "vmb.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#ifdef DEBUG
#include "dbgmode.h"
#endif

#define ALIGNMENT sizeof(size_t)

#define ALIGN(size) ((size)+(ALIGNMENT-1)) & ~(ALIGNMENT-1)

enum seg_type { VMB, FMB }; /* Variable, Fixed, General */

struct seg_header
{
	size_t size;
};

typedef struct blk_header /*need to use block */
{
	long blk_sz;

#ifdef DEBUG
	size_t offset;
#endif

};

vmb_p vmb_init(vmb_p seg_ptr, size_t seg_size)
{
	struct seg_header my_struct;

	struct blk_header * blk = NULL;/**/
	blk = (struct blk_header *)malloc(sizeof(struct blk_header));
	blk->blk_sz = 0; /**/

#ifdef DEBUG
	blk->offset = sizeof(struct seg_header);
#endif

	my_struct.size = seg_size;
    
	*(size_t*)(seg_ptr) = my_struct.size;

	blk->blk_sz = sizeof(struct seg_header) + (2 * ALIGNMENT) - seg_size;

#ifdef DEBUG
	blk->offset = sizeof(struct seg_header);
#endif

	/*
	*(long*)(seg_ptr + ALIGNMENT) = sizeof(struct seg_header) + (2 * ALIGNMENT) - seg_size;
    *(size_t*)(seg_ptr + 2 * ALIGNMENT) = sizeof(struct seg_header);
    */
	*(long*)(seg_ptr + ALIGNMENT) = blk->blk_sz;
#ifdef DEBUG
	*(size_t*)(seg_ptr + 2 * ALIGNMENT) = blk->offset;
#endif
	return seg_ptr;
}

static void merge_free(vmb_p seg_ptr, vmb_iter curr, vmb_iter next, size_t seg_sz)
{
	while((next < seg_ptr + seg_sz) && (*(long*)(next) < 0))
	{
		long temp_val = *(long*)(next);
		*(long*)(next) = 0;
		*(long*)(next + ALIGNMENT) = 0;
		*(long*)(curr) = *(long*)(curr) + temp_val - sizeof(struct blk_header);
		next = next + abs(temp_val) + 2 * ALIGNMENT;
	}

}

vmb_iter vmb_alloc(vmb_p seg_ptr, size_t block_size)
{
	vmb_p next_ptr = seg_ptr + ALIGNMENT;
	size_t seg_size = *(size_t*)(seg_ptr);
	vmb_p temp_ptr = NULL;
	long blk_size = 0;

	while(1)
	{
		blk_size = *(long*)(next_ptr);

		temp_ptr = next_ptr + abs(blk_size) + sizeof(struct blk_header);

		if(*(long*)(next_ptr) < 0)
		{
			if((temp_ptr < seg_ptr + seg_size) && (*(long*)(temp_ptr) < 0)) /*check if the next block is in segment and free)*/ /*case yes - merge*/
			{
				merge_free(seg_ptr, next_ptr, temp_ptr, seg_size);
				blk_size = *(long*)(next_ptr);
			}

			/*else
			{*/
				if(block_size <= abs(blk_size + 2 * ALIGNMENT))
				{
					*(long*)(next_ptr) = ALIGN(block_size);
					temp_ptr = next_ptr + *(long*)(next_ptr) + sizeof(struct blk_header);
					*(long*)(temp_ptr) = *(long*)(next_ptr) + blk_size;
					*(long*)(temp_ptr + ALIGNMENT) = *(long*)(next_ptr + ALIGNMENT) + *(long*)(next_ptr) + sizeof(struct blk_header);
					return next_ptr + sizeof(struct blk_header);
				}

				else
				{
					if(temp_ptr >= seg_ptr + seg_size)
					{
						return NULL;
					}

					else
					{
						next_ptr = temp_ptr;
						continue; /* not finisheddddd*/
					}
				}
			/* } case no*/

		}

		else
		{
			if(temp_ptr >= seg_ptr + seg_size)
			{
				return NULL; /*exit upon reaching end of segment*/
			}

			else
			{
				next_ptr = temp_ptr; /*go to next block and repeat check*/
				continue;
			}
		}


	}

}

void vmb_free(vmb_iter block_ptr)
{
	if(block_ptr == NULL) return;

	if(*(long*)(block_ptr - (sizeof(struct blk_header))) < 0)
	{
		return;
	}

	else
	{
		*(long*)(block_ptr - (sizeof(struct blk_header))) = *(long*)(block_ptr - (sizeof(struct blk_header))) * (-1);
		/**(long*)(block_ptr - ALIGNMENT) = 0;*/
	}
}


#ifdef DEBUG
vmb_iter vmb_begin(vmb_p seg_ptr)
{
	if(seg_ptr == NULL) return NULL;

	vmb_iter curr = seg_ptr + sizeof(struct seg_header);
    vmb_iter end = seg_ptr + *(size_t*)(seg_ptr) + sizeof(char);
    
    while(curr!=end)
    {
        if(*(long*)(curr) > 0)
        {
            return curr;
        }
        
        else
        {
            curr += labs(*(long*)(curr)) + 2 * ALIGNMENT;
        }
    }
    
    return NULL;
}


vmb_iter vmb_end(vmb_p seg_ptr)
{
    if(seg_ptr == NULL)
    {
        return NULL;
    }
    
    vmb_iter curr = seg_ptr + sizeof(struct seg_header);
    vmb_iter end = seg_ptr + *(size_t*)(seg_ptr) + sizeof(char);
    vmb_iter temp = NULL;
    
    while(curr <= end)
    {
        if(*(long*)(curr) > 0)
        {
            temp = curr;
        }
        
        curr += labs(*(long*)(curr)) + 2 * ALIGNMENT;

    }

    return temp;
}

vmb_iter vmb_next(vmb_iter block_ptr)
{
	 if(block_ptr == NULL || (block_ptr - sizeof(struct blk_header)) == NULL)
	    {
	        return NULL;
	    }

	vmb_iter curr = block_ptr - sizeof(struct blk_header);
	vmb_iter next = curr + labs(*(size_t*)(curr)) + sizeof(struct blk_header);
	vmb_iter seg_start = curr - *(size_t*)(curr + ALIGNMENT);
	vmb_iter seg_end = seg_start + *(size_t*)(seg_start);

	vmb_iter temp = NULL;

	while(next <= seg_end)
	    {
			if(*(long*)(next) == 0)
			{
				return NULL;
			}

			else if(*(long*)(next) > 0)
	        {
	            temp = next;
	            break;
	        }

	        next += labs(*(long*)(next)) + 2 * ALIGNMENT;
	    }

	    return temp;
}


vmb_iter vmb_prev(vmb_iter block_ptr)
{
	 if(block_ptr == NULL || (block_ptr - sizeof(struct blk_header)) == NULL)
	{
		return NULL;
	}

	vmb_iter curr = block_ptr - sizeof(struct blk_header);
	vmb_iter seg_start = curr - *(size_t*)(curr + ALIGNMENT);
	vmb_iter prev = seg_start + ALIGNMENT;
	vmb_iter temp = NULL;

	while(prev <= curr)
	{
		if(prev == curr)
		{
			return temp;
		}

		else if(*(long*)(prev) > 0)
		{
			temp = prev;
		}

		prev += labs(*(long*)(prev)) + 2 * ALIGNMENT;
	}

	return temp;
}


void* vmb_get(vmb_iter block_ptr)
{
	return (void*)(block_ptr);
}

#endif

