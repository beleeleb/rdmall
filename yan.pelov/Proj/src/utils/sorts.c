#include "sorts.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "cdlist.h"

static void swap(void *a, void *b, size_t size)
{
	void *temp = malloc(size);
	memcpy(temp, b, size);
	memcpy(b, a, size);
	memcpy(a, temp, size);	
	free(temp);
}

static size_t biggest(void* data, size_t n_members,
		    size_t member_sz, cmp cmp_f)
{
	int i = 0;
	void* biggest = NULL;
	
	biggest = data;
	for(i = 1; i < n_members; ++i)
	{
		if(cmp_f(biggest, data + i*member_sz)<0)
		{

			biggest = data + i*member_sz;
			
		}
	}
	
	return (size_t)(*(int*)biggest);
}

void bubble_sort(void* data, size_t n_members, size_t member_sz, cmp cmp_f)
{
	int i, j;
	
	for(i = n_members - 1; i > 1; --i)
	{
		for(j = 0; j < i; ++j)
		{
			
			if(cmp_f((data+j*member_sz),(data+(j+1)*member_sz)) > 0)
			{
				swap((data+j*member_sz), (data+(j+1)*member_sz), member_sz);
			}	
			
		}
	}

	return;
}

void radix_sort(void* data, size_t n_members,
		   size_t member_sz, cmp cmp_f)
{

	int i, exp = 1;
	size_t b[n_members];
	size_t big = biggest(data, n_members,member_sz, cmp_f);

    while (big / exp > 0)
    {

		int bucket[10] = { 0 };
	 
		for (i = 0; i < n_members; i++)
		{
			bucket[((*(int*)(data+i * member_sz)) / exp) % 10]++;
		}
	 	
		for (i = 1; i < 10; i++)
		{
			bucket[i] += bucket[i - 1]; 
		}
	 
		for (i = n_members - 1; i >= 0; i--)
		{
			b[--bucket[((*(int*)(data+i*member_sz)) / exp) % 10]] = 
							 *(size_t*)(data+i * member_sz);
		}

		for (i = 0; i < n_members; i++)
		{
			*(int*)(data+i * member_sz) = b[i];
	 	}

		exp *= 10;
	}
    
}


void insertion_sort(void* data, size_t n_members,
		      size_t member_sz, cmp cmp_f)
{
	int i, j;

	for(i = 1; i < n_members; ++i)
	{
		j = i;
	
			for(j = i; j > 0 && cmp_f(data+(j-1) * member_sz, 
										data+(j) * member_sz) >0; --j)
			{
				 swap((data+ (j-1) * member_sz), (data + (j) * member_sz), member_sz);
			}

		
	}
	return;
}

void bucket_sort(void* data, size_t n_members,
		    size_t member_sz, cmp cmp_f)
{
    cdl_node_t** table = (cdl_node_t**)malloc(sizeof(cdl_node_t*) * n_members);
    memset(table, 0, sizeof(cdl_node_t*) * n_members);

    int i, j;
	size_t index = 0;
	void *elem = NULL;
	size_t size_arr = 0;

	size_arr = biggest(data, n_members,member_sz, cmp_f);

    for(i =0; i< n_members; ++i)
    {
        elem = (data + i * member_sz);

        index = ( (*(int*)elem) * n_members) / (size_arr + 1) ;
        table[index] = cdlist_insert_after(table[index], elem);
    }

    cdl_node_t *node = NULL;
   

    for(i = 0; i < n_members; i++)
    {
        node = table[i];

        for(j = 0; j < cdlist_size(table[i]); ++j)
        {
            elem = cdlist_get_data(node);
            node = cdlist_next(node);
        }
    }

    cdl_iterator temp = NULL;
	cdl_iterator prev = NULL;

    int long_array[n_members];
    int long_array_counter = 0;

    for(i = 0; i < n_members; ++i)
    {
        void* array[cdlist_size(table[i])];
        int j = 0;

        temp = table[i];
		
        if(!cdlist_is_empty(temp))
        {   
			/* create short temp array*/
            do
            {
                array[j] = cdlist_get_data(temp);
                temp = cdlist_next(temp);
                ++j;       
            } while (temp != table[i]);

			/* internally Bubble sort the short temp array*/
            int x, y;
            for (x = 0; (x < cdlist_size(table[i]) - 1); ++x)
            {
				for (y = 0; (y < cdlist_size(table[i]) - x - 1); ++y)
                {
                     if (*((int*)array[y]) > *((int*)(array[y + 1])))
                    {
                         void* tmp = array[y];
                         array[y] = array[y + 1];
                         array[y + 1] = tmp;
                     }
                 }
             }

			/* add each short temp array to long temp array*/
            int cnt = 0;
            for (cnt = 0; (cnt < cdlist_size(table[i])); ++cnt)
            {
                long_array[long_array_counter] = *((int*)array[cnt]);
                ++long_array_counter;
            }
        }
    }

    int k;

	/* return data from long temp array to main*/
    for (k = 0; k < n_members; ++k)
    {
		(*((int*)(data + k * member_sz))) = long_array[k];
    }

	/* free all memory */
	for(i = 0; i < n_members; ++i)
    {     
        temp = table[i];
                               								
        if(!cdlist_is_empty(temp))
        {   
            do
            {             
				prev = temp;
                temp = cdlist_next(temp);
                free(prev);       
            } while (temp != table[i]);
        }
	}

	free(table);

    return;   
}

static void merge_me(void *data, size_t n_members,
                     size_t member_sz, cmp cmp_f)
{
	void* array = malloc(member_sz * n_members);

	memset(array, 0, member_sz * n_members);

	void* ptr = (char*)(data)+member_sz*((n_members+1)/2);

	int i;

	void* data_start = data;
	void * data_end_left = ptr ;
	void * data_end_right = (char*)(data) + (member_sz * n_members);
	void * array_start = array;

	for(i = 0; i < n_members; ++i)
	{
		if((cmp_f(data, ptr) > 0 || (data == data_end_left)) && (ptr != data_end_right))
		{
			memcpy(array, ptr, member_sz);
			ptr = (char*)(ptr) + member_sz;	
			
		}

		else if((cmp_f(data, ptr) <= 0 || ptr == data_end_right) && (data != data_end_left))
		{
			memcpy(array, (char*)data, member_sz);
			data = (char*)(data) + member_sz;
		}

	array = (char*)array + member_sz;

	}

	memcpy(data_start, array_start, n_members * member_sz);
	
}


void merge_sort(void* data, size_t n_members, size_t member_sz, cmp cmp_f)
{

	if((char*)data < (char*)data + member_sz*(n_members-1))
	{
			merge_sort(((char*)data), (n_members+1)/2, member_sz, cmp_f);
			merge_sort(((char*)data) + member_sz*((n_members+1)/2) , (n_members) / 2, member_sz, cmp_f);

		merge_me((char*)data, n_members , member_sz, cmp_f);
	}

	return;
}


static void heapify(void* data, size_t n_members, size_t member_sz, cmp cmp_f)
{
	void * num1 = NULL;
	void * num2 = NULL;
	void * num3 = NULL;

	int i;

	for(i = 0; i < n_members / 2; )
	{
		
	num1 = (char*)data + member_sz* (n_members - 1 - i*2);
	num2 = (char*)data + member_sz* (n_members - 2 - i*2);
	num3 = NULL;

		if(cmp_f(num1, num2) > 0)
		{	
			if((n_members - 1 - i*2)%2 == 0)
			{
				num3 = (char*)data + member_sz* ((n_members - 1 - 1 - i*2)/2);
				if(cmp_f(num1, num3) > 0)
				{
					swap(num1, num3, member_sz);
					i++;
				}
		
				else i++;
			}	

			else
			{
				num3 = (char*)data + member_sz* ((n_members - 1 - i*2)/2);
				if(cmp_f(num1, num3) > 0)
				{
					swap(num1, num3, member_sz);
					i++;
				}
				
				else i++;
			
			}		
		}

		else
		{
			if((n_members - 1 - i*2)%2 == 0)
			{
				num3 = (char*)data + member_sz* ((n_members - 1 - 1 - i*2)/2);
				if(cmp_f(num2, num3) > 0)
				{
					swap(num2, num3, member_sz);
					i++;
				}

				else i++;
			
			}	

			else
			{
				num3 = (char*)data + member_sz* ((n_members - 1 - i*2)/2);
				if(cmp_f(num2, num3) > 0)
				{
					swap(num2, num3, member_sz);
					i++;
				}

				else i++;
			
			}		

		}
	} 
	
}

static void fix_heap(void* data, size_t n_members, size_t member_sz, cmp cmp_f)
{
    void * num1 = NULL;
	void * num2 = NULL;
	void * num3 = NULL;

	int i;

	for(i = 0; i < n_members / 2; i++)
	{
		
	num1 = (char*)data + member_sz* (n_members - 1 - i*2);
	num2 = (char*)data + member_sz* (n_members - 2 - i*2);
	num3 = (char*)data + member_sz* (n_members - 3 - i*2);

		if(cmp_f(num1, num2) > 0)
		{	
			swap(num1, num2, member_sz);
		}

		if(cmp_f(num2, num3) > 0)
		{
			swap(num2, num3, member_sz);
		}

	}

}


void heap_sort(void* data, size_t n_members, size_t member_sz, cmp cmp_f)
{
    heapify(data, n_members, member_sz, cmp_f);
    fix_heap(data, n_members, member_sz, cmp_f);
    return;
}

void quick_sort(void* data, size_t n_members, size_t member_sz, cmp cmp_f)
{

	size_t i = 0;
	size_t j = n_members - 1;

	void *pivot = (char*)data + member_sz * j;

	if(n_members <= 1)
	return;

	while(i < j)
	
	{
			if(cmp_f(data + member_sz * i, pivot) < 0)
			{
			
				i++;
			}
			
			else
			{
				swap(data + member_sz * i, pivot - member_sz, member_sz);
				swap(pivot, pivot - member_sz, member_sz);
				j--;
				
				pivot = pivot - member_sz;
			}
	}
    
	quick_sort(data, j, member_sz, cmp_f);
	quick_sort(data + (j + 1) * member_sz, n_members - j - 1 , member_sz, cmp_f);
    
    return;
}
