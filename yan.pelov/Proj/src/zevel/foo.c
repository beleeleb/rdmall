#include <stdio.h>
#include "foo.h"

unsigned int fibo(unsigned int num)
{
	
	if (num == 0)
	{
	    return 0;
    }

	if (num == 1)
	{
        return 1;
    }
	
	if(num > 1)
	{
		num = fibo(num-1) + fibo(num-2);
	}    

	return num;

}

unsigned int factorial(unsigned int n)
{
    if (n == 0) 
	{
        return 1;
    } 

	else 
	{
        return n * factorial(n - 1);
    }
}
