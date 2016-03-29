/****************************************************************************************
 * This program tests the following 4 functions: dlopen(), dlsym(),  dlclose() and
 dlerror()                                                                              *
 * implement the interface to the dynamic linking loader.								*
 *																						*
 * 	1. function dlerror():
 	   returns a human readable string describing the									*
 *     most recent error that occurred from dlopen(),dlsym() or dlclose()			    *
 *     It returns NULL if no errors have occurred since initialization or since it		*
 *     was last called.																	*
 *																						*
 *  2. function dlclose():
 	   decrements the reference count on the dynamic
       library handle. If the reference count drops to zero and no
       other loaded libraries use symbols in it, then the dynamic library is
       unloaded.
       The function dlclose() returns 0 on success, and non-zero on error.
       
    3. function dlsym():
       takes a "handle" of a dynamic library returned by dlopen() and the 
       null-terminated symbol name, returning the address where that symbol
       is loaded into memory. 
     
    4. function dlopen():  
       The function dlopen() loads the dynamic library file named by the null-
       terminated  string  filename  and  returns  an  opaque "handle" for the
       dynamic library. If filename is NULL, then the returned handle is  for
       the  main  program.   If	 filename  contains  a slash ("/"), then it is
       interpreted as a pathname.  
 
    5. RTLD_LAZY == resolve undefined symbols as code from the dynamic library is executed

	6. gcc -rdynamic -o loader runtime_loader.c -ldl
       
 ***************************************************************************************/


#include <stdio.h>
#include <dlfcn.h>	/* needed for: dlopen(),dlsym(),dlclose(),dlerror() */

int main(int argc, char **argv, char **env) 
{
	void *lib_handle;
	void (*fn)(void);
	char *error;
	lib_handle = dlopen("~/work/Proj/src/Exercises/libmyfirstso.so", RTLD_LAZY);
	if (!lib_handle)
	{
		perror("dlopen");
		return -1;
	}

	fn = dlsym (lib_handle, "myfoo");
	if ((error = dlerror()) != NULL)
    {
        perror("dlerror");
        return -1;
    }
    
	fn();

	sleep(500); 

	dlclose(lib_handle);

	return 0;
}
