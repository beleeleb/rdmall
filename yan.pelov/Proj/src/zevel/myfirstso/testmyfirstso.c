/* This program is intended to examine how .so works and how different vars are set in the VM


1. gcc -c -Wall -fPIC myfirstso.c 	-----> compiles the source file independenly

2. gcc -shared -o libfoo.so myfirstso.c		-----> creates the shared library

3. gcc -L /home/student/Dropbox/os/sharedobject/ -Wall testmyfirstso.c -o testmyfirstso -lfoo	-----> compiles the main

4. echo $LD_LIBRARY_PATH = /home/student/Dropbox/os/sharedobject/:$LD_LIBRARY_PATH	-----> tells the compiler where the s.lib is

5. export LD_LIBRARY_PATH=/home/student/work/svn/os/shared_object:$LD_LIBRARY_PATH	-----> exports the s.lib

6. ./test	-----> run


****when changes are made, no need to compile the regular way (3) only 1+2 and then run (6)*****/

int var1;
int var2 = 0;
static int var3;
static int var4 = 0;

int main(int argc, char** argv, char** envp)
{
	int var5;
	int var6 = 1;
	static int var7;
	static int var8 = 1;
	myfoo();
	
	return 0;
}
