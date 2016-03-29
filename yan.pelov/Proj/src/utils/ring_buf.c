#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "ring_buf.h"

struct rbuf
{
	size_t size;
	void** data;  
	size_t start;
	size_t n_elems;
};

enum result
{
SUCCESS = 0, FAIL = 1
};

/*----------------------------------------------------------------------------*/

rbuf_t* rbuf_create(size_t size)
{
	rbuf_t* new_buff = NULL; 
	new_buff = (rbuf_t*)malloc(sizeof(rbuf_t));
	assert(new_buff);
	memset(new_buff, 0, sizeof(rbuf_t));
	
	new_buff->data = (void**)malloc(sizeof(data_t) * size); 
	assert(new_buff->data);
	memset(new_buff->data, 0, sizeof(data_t) * size);

	new_buff->size = size;
    new_buff->start = 0;
    new_buff->n_elems = 0;

	return new_buff;
}

/*----------------------------------------------------------------------------*/

void rbuf_destroy (rbuf_t* rbuffer)
{
    assert(rbuffer);
	memset(rbuffer->data, 0, sizeof(data_t) * (rbuffer->size)); 
	free(rbuffer->data);
	memset(rbuffer, 0, sizeof(rbuf_t)); 
	free(rbuffer);
	rbuffer = NULL;
}

/*----------------------------------------------------------------------------*/

size_t rbuf_capacity (rbuf_t* rbuffer)
{
	return (rbuffer->size);
}
	
/*----------------------------------------------------------------------------*/


size_t rbuf_in_use(rbuf_t* rbuffer)
{
	return(rbuffer->n_elems);	
}

/*----------------------------------------------------------------------------*/

size_t rbuf_available(rbuf_t* rbuffer)
{
	return(rbuffer->size - rbuffer->n_elems);	
}

/*--------------------------------------------------------------------------*/
int rbuf_write(rbuf_t* rbuffer, data_t data)
{
	size_t index = (rbuffer->start + rbuffer->n_elems)%(rbuffer->size);
	if(rbuf_available(rbuffer)!=0)	
	{
		rbuffer->data[index] = data;
		/*printf("rbuf_write: %ld\n", (long)rbuffer->data[index]);*/
		++(rbuffer->n_elems);
		return SUCCESS;
	}

	else 
	{
		printf("Not enough space - read some data first...\n");
		return FAIL;
	}
	
}
/*--------------------------------------------------------------------------*/
data_t rbuf_read (rbuf_t* rbuffer)
{
	size_t last = (rbuffer->start)%(rbuffer->size); 
	data_t return_data = NULL; 

	if(rbuf_in_use(rbuffer) != 0)
	{
		return_data = rbuffer->data[last]; 
		rbuffer->data[last] = NULL;			
		++rbuffer->start;
		rbuffer->start %= rbuffer->size;					
		--(rbuffer->n_elems);
		rbuffer->n_elems %= rbuffer->size;				
		return return_data;	
	}

	else
	{
		printf("Buffer is empty\n");
		return NULL;
	}
}

/*--------------------------------------------------------------------------*/

data_t rbuf_erase (rbuf_t* rbuffer, iterator iter)
{
	iterator i = NULL;
	data_t return_data = *iter;
	
	if(rbuf_in_use(rbuffer) != 0)
	{
		if(iter == rbuf_end(rbuffer)) 	
		{
			--(rbuffer->n_elems);
			rbuffer->n_elems %= rbuffer->size;
			return return_data;
		}

		for(i = iter; i != rbuf_end(rbuffer) + 1; i = rbuf_next(rbuffer, i)) 
		{
			*i = *(rbuf_next(rbuffer,i));
		}
		
		--(rbuffer->n_elems);
		rbuffer->n_elems %= rbuffer->size;
		return return_data;
	}
	
	else
	{
		printf("Buffer is empty - Can't Erase\n");
		return 0;
	}
}

/*--------------------------------------------------------------------------*/

iterator rbuf_start (rbuf_t* rbuffer)
{
	return rbuffer->data + rbuffer->start;	
	
} 

/*--------------------------------------------------------------------------*/

data_t rbuf_get_data(iterator iter)
{
	return *iter;
}

/*--------------------------------------------------------------------------*/
extern iterator rbuf_temp(rbuf_t* rbuffer)
{
	return rbuffer->data;
}

iterator rbuf_end (rbuf_t* rbuffer)
{
	return rbuffer->data + (rbuffer->start + rbuffer->n_elems - 1) % rbuffer->size;  /*change the entire return "rbuffer->data + rbuffer->n_elems"*/
}

/*--------------------------------------------------------------------------*/

iterator rbuf_next (rbuf_t* rbuffer, iterator iter)
{
	if(rbuf_in_use(rbuffer) != 0)
	{	
		if(iter == (rbuffer->data + rbuffer->size - 1)) 	
		{
			return rbuffer->data;
		}

		else return iter + 1;
	}

	else
	{
		printf("No next - Buffer is empty\n");
		return NULL; /*change to null*/
	}

}

/*--------------------------------------------------------------------------*/

iterator rbuf_prev (rbuf_t* rbuffer, iterator iter)
{
	if(rbuf_in_use(rbuffer) != 0)
	{	
		if(iter == (rbuffer->data + rbuffer->start)) 	
		{
			if(rbuf_end(rbuffer) != 0)
			{
				return rbuf_end(rbuffer);	
			}

			else
			{
				printf("Can't move, prev is null\n");
				return iter + 1; /*change to null*/
			}
		}
		
		else return iter - 1;
	}

	else
	{
		printf("No prev - Buffer is empty\n");
		return iter - 1; /*change to null*/
	}
}

/*--------------------------------------------------------------------------*/

void print_rbuf(rbuf_t* rbuffer) 
{
	int i;

	printf("\nbuffer data:\n");
	for(i = 0; i < rbuffer->size; ++i)
	{
		printf("%ld\n", (long int)rbuffer->data[i]);
	}

	return;

}










