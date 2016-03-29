#include "file_safe.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>



int sf_create(char* dir_path, char* file_path)
{
	char * str = malloc(strlen(dir_path) + strlen(file_path)+1);
	str = strcat(str, dir_path);
	str = strcat(str, "/");
	str = strcat(str, file_path);

	char tmp_str[200];

	int i = 1;
	int j = 1;
	tmp_str[0] = '/';
	while(dir_path[i]!='\0')
	{

		while(dir_path[i]!='/' && dir_path[i]!='\0')
		{
			tmp_str[j] = dir_path[i];
			++j;
			++i;
		}

		tmp_str[j] = '\0';
		mkdir(tmp_str, 0777);
		/*printf("%s\n", tmp_str);*/
		tmp_str[j] = '/';
		++j;
		if(dir_path[i]!='\0') ++i;
	}


		int fd = open(str, O_RDWR | O_CREAT , 0777);
		if(fd < 0)
		{
			return -2;
		}

		else
		{
			free(str);
			close(fd);
			return 0;
		}

}

int sf_destroy(char* path)
{
	return remove(path);
}


int sf_open(char* path)
{
	return open(path, O_RDWR , 0777);
}

int sf_close(int fd)
{
	return close(fd);
}


int sf_wlock(int fd)
{
    if (fd == -1)
    {
        return -1;
    }

    struct flock f1;
    
    f1.l_type = F_WRLCK;
	f1.l_whence = SEEK_SET;
	f1.l_start = 0;
	f1.l_len = 0;
    return fcntl(fd, F_SETLK, &f1);
}


int sf_wunlock(int fd)
{
    if (fd == -1)
    {
        return -1;
    }
    
    struct flock f1;
    
    f1.l_type = F_UNLCK;
	f1.l_whence = SEEK_SET;
	f1.l_start = 0;
	f1.l_len = 0;
    return fcntl(fd, F_SETLKW, &f1);
}

int sf_rlock(int fd)
{
    if (fd == -1)
    {
        return -1;
    }
    
    struct flock f1;
    
    f1.l_type = F_RDLCK;
	f1.l_whence = SEEK_SET;
	f1.l_start = 0;
	f1.l_len = 0;
    return fcntl(fd, F_SETLKW, &f1);
}

int sf_runlock(int fd)
{
    if (fd == -1)
    {
        return -1;
    }
    
    struct flock f1;
    
    f1.l_type = F_UNLCK;
	f1.l_whence = SEEK_SET;
	f1.l_start = 0;
	f1.l_len = 0;
    return fcntl(fd, F_SETLKW, &f1);
}



