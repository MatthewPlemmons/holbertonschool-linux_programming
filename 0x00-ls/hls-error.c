#include "hls.h"

/**
 * print_error - build an error message and call `perror()`
 *
 * @error: error message
 * @path: path string
 */
void print_error(char *error, char *path)
{
	char *errstr, *errmsg;
	int len;

	len = _strlen(error) + 1;
	errmsg = _calloc(sizeof(char), len);
	_strcpy(errmsg, error);

	errstr = _calloc(sizeof(char), MAX_PATH_SIZE + len);
	_strcpy(errstr, errmsg);
	free(errmsg);

	_strcat(errstr, path);

	perror(errstr);
	free(errstr);
}

/**
 * error_handler - detect which error occured and print its error message
 *
 * @err: errno value
 * @path: directory path
 */
void error_handler(int err, char *path)
{
	if (err == EACCES)
		print_error("hls: cannot open directory ", path);
	if (err == ENOENT)
		print_error("hls: cannot access ", path);
}
