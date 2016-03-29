
#include "fmb_alloc.h"
#include <stdlib.h>
#include <string.h>
int main()
{

	fmb_p myseg = NULL;
	myseg = (fmb_p)malloc(sizeof(char) * 200);
	memset(myseg, 0, sizeof(char) * 200);
	fmb_init(myseg, 200, 8);
	void* res = fmb_alloc(myseg);
	res = fmb_alloc(myseg);
	res = fmb_alloc(myseg);
	res = fmb_alloc(myseg);
	return 0;
}

