#ifndef __XSTRING_H__
#define  __XSTRING_H__

typedef unsigned long size_t;

size_t xstrlen(const char *s);
size_t xstrnlen(const char *s, size_t n);
int xstrcmp (const char *s1, const char *s2);
int xstrncmp (const char *s1, const char *s2, size_t n);
char *xstrcpy (char *dest, const char *src);
char *xstrncpy (char *dest, const char *src, size_t n);
char *xstrstr (const char *haystack, const char *needle);
char *xstrnstr(const char *haystack, const char *needle, size_t n);
char *xstrcat (char *dest, const char *src);
char *xstrncat (char *dest, const char *src, size_t n);
char *xstrdup (const char *s);
char *xstrndup (const char *s, size_t n);
size_t xstrspn (const char *s, const char *accept);
size_t xstrcspn(const char *str1, const char *str2);

#endif


