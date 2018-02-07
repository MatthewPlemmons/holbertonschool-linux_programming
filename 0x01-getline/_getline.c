#include "_getline.h"

/**
 * _getline - Read line to a buffer.
 *
 * @fd: file descriptor
 * Return: Null-terminated string, or NULL on failure.
 */
char *_getline(const int fd)
{
	ssize_t len;
	char *buf;

	buf = malloc(sizeof(char) * READ_SIZE);
	if (!buf)
	{
		free(buf);
		return (NULL);
	}

	len = read(fd, buf, READ_SIZE);
	if (len == -1)
	{
		free(buf);
		return (NULL);
	}
	if (len == 0)
	{
		free(buf);
		return (NULL);
	}

	return (buf);
}
