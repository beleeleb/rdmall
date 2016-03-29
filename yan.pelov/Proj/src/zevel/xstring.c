#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xstring.h"


size_t xstrlen(const char *s)
{
	assert(s);
		
	if(*s!='\0')
	{
		return xstrlen(++s) + 1;
	}
	
	return 0;
}

size_t xstrnlen(const char *s, size_t n)
{
	if(*s!='\0' && n > 0)
	{
		return xstrnlen(++s, --n) + 1;
	}

	return 0;
}

int xstrcmp (const char *s1, const char *s2)
{
	assert(s1);
	assert(s2);
	
	if((*s1 == *s2) && *s1 && *s2)
	{
		return xstrcmp(++s1, ++s2);
	}
	
	return (int)(*s1 - *s2);
}

int xstrncmp (const char *s1, const char *s2, size_t n)
{
	assert(s1);
	assert(s2);
	
	if((*s1 == *s2) && n > 1 && *s1 && *s2)
	{
		return xstrncmp(++s1, ++s2, --n);
	}

	return (int)(*s1 - *s2);
}

char *xstrcpy (char *dest, const char *src)
{
	assert(src);
	assert(dest);

	if((*dest = *src) && *dest && *src)
	{
		
		xstrcpy(++dest, ++src);
	}	

	return dest;	
}

char *xstrncpy (char *dest, const char *src, size_t n)
{
	assert(src);
	assert(dest);
	
	if((*dest = *src) && *dest && *src && n > 1 )
	{
		xstrncpy(++dest, ++src, --n);
	}
	
	return dest;
}

char *xstrstr (const char *haystack, const char *needle)
{
	assert(haystack);
	assert(needle);

	if(!*needle) return (char *)haystack;

	if(xstrlen(haystack) < xstrlen(needle)) return NULL;

	if(0 == xstrncmp(haystack, needle, xstrlen(needle)))
	{
		return (char*)haystack;	
	}

	else
	{
		return xstrstr(++haystack, needle);
	}

}

char *xstrnstr(const char *haystack, const char *needle, size_t n)
{
	assert(haystack);
	assert(needle);

	if(!*needle) return (char *)haystack;

	if(xstrlen(haystack) < xstrlen(needle)) return NULL;

	if(0 == xstrncmp(haystack, needle, n))
	{
		return (char*)haystack;	
	}

	else
	{
		--n;
		return xstrnstr(++haystack, needle, n);
	}
}

char *xstrcat (char *dest, const char *src)
{
	assert(dest);
	assert(src);

	if(*dest != '\0')
	{
		xstrcat(++dest, src);
	}

	else xstrcpy(dest, src);

	
	return (char*)dest - 1;
  
   
}

char *xstrncat (char *dest, const char *src, size_t n)
{
    
	assert(dest);
	assert(src);

	if(*dest != '\0')
	{
		xstrncat(++dest, src, n);
	}

	else xstrncpy(dest, src, n);

	
	return (char*)dest - 1;  
}

char *xstrdup (const char *s)
{	
	char *str = (char*)malloc(sizeof(char) * (xstrlen(s) + 1));

	xstrcpy(str, s);
	
	return str;
}

char *xstrndup (const char *s, size_t n)
{
	char *str = (char*)malloc(sizeof(char) * n);

	xstrncpy(str, s, n);
	
	return str;
}

size_t xstrspn (const char *s, const char *accept)
     
/* start*/
{
	if(*s && *accept)
	{
		if(*s == *accept)
		{
			return xstrspn(s+1, accept) + 1; 
		}

		if ( xstrspn( s , accept+1) ) 
		{
			return xstrspn( s+1 , accept) + 1;
		}
		else
		{
			return 0;
		}

	}
	return 0;
}
/*
const char * temp = NULL;
*/
/* s      = acakfkavlks
	accept= wzac
*/
/*	return 0;


	temp = accept;

		while(*accept)
		{
			if(*s == *accept)
			{
				return xstrspn(++s, temp) + 1;
			}
	
			else ++accept;
		}

		return 0;
	}

	else return 0;
}
*/
/*
size_t xstrcspn(const char *str1, const char *str2)
{
	const char * temp = NULL;

	if(*str1)
	{

	temp = str2;

		while(*str2)
		{
			if(*str1 == *str2)
			{
				return 0;
			}
	
			else
			{
				++str2;

			}

			return xstrcspn(++str1, temp) + 1;
		}

	}
	
}

*/


