#include <stdio.h>
#include "foo.h"

int main(int argc, char **argv, char **envp)
{
  
  int i = 4;
	
 printf("factorial sum = %d\n", factorial(i));

  for(i = 0; i < 10; i++) 
  printf("fibonaci sum = %d\n", fibo(10));
	
  return 0;
}
