#include "foo.h"

#include <stdio.h>


void testfoo(void)
{
  foo("hello world");
}

void foo(char *cp)
{
  printf("%s\n", cp);
}
