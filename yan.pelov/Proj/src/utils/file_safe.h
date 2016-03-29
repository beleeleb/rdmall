#ifndef __FILE_SAFE_H__
#define __FILE_SAFE_H__

/*
 * Create a file safe in the given path.
 *
 * 	Values:
 *		path    - a string to where to create the safe.
 *  Return value:
 *		success/fail.
 */
int sf_create(char* dir_path, char* file_path);

/*
 * Destroy a file safe in the given path.
 *
 * 	Values:
 *		path  - a string to the safe.
 *  Return value:
 *		success/fail.
 */
int sf_destroy(char* path);

/*
 * Open the file safe in the given path.
 *
 * 	Values:
 *		path  - a string to the safe.
 *  Return value:
 *		file discriptor (in case of failure the function return -1).
 */
int sf_open(char* path);

/*
 * Open the file safe with a given file discriptor.
 *
 * 	Values:
 *		fd  - file discriptor.
 *  Return value:
 *		success/fail.
 */
int sf_close(int fd);

/*
 * Lock the file to write and read and allow whom how called the
 * function permission to write.
 *
 * 	Values:
 *		fd  - file discriptor.
 *  Return value:
 *		success/fail.
 */
int sf_wlock(int fd);

/*
 * Unlock the file from permission to write.
 *
 * 	Values:
 *		fd  - file discriptor.
 *  Return value:
 *		success/fail.
 */
int sf_wunlock(int fd);

/*
 * Lock the file to write and allow whom how called the
 * function permission to read.
 *
 * 	Values:
 *		fd  - file discriptor.
 *  Return value:
 *		success/fail.
 */
int sf_rlock(int fd);

/*
 * Unlock the file from permission to read.
 *
 * 	Values:
 *		fd  - file discriptor.
 *  Return value:
 *		success/fail.
 */
int sf_runlock(int fd);


#endif /* __FILE_SAFE_H__ */

