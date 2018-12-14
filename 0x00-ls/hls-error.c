#include "hls.h"

/**
 * build_error_string - build an error message for `perror()`
 *
 * @error: error message
 * @path: path string
 * Return: pointer to new error string
 */
char *build_error_string(char *error, char *path)
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

	return (errstr);
}
