#ifndef __UTILS_H__
#define __UTILS_H__

#include <assert.h>
#include <string.h>

#define DEBUG_CHECK(x) assert((__FILE__ && __LINE__) && x)
#define BAD_DATA 0XDEADBEEF

#ifdef NDEBUG
#define DEBUG_ZAP_PTR(x)
#else
#define DEBUG_ZAP_PTR(x) memset(x,~0,sizeof(*x))
#endif


#endif

