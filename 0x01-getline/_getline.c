#include "_getline.h"


/**
 * read_into_buffer - Read from fd into buffer.
 * @fd: file descriptor
 * @buf: buffer
 * Return: 0 if successful, otherwise -1.
 */
int read_into_buffer(const int fd, char *buf)
{
	ssize_t len;
	char *ptr;

	while ((len = read(fd, buf, READ_SIZE)) > 0)
	{
		if (len == -1)
		{
			free(buf);
			return (-1);
		}
		if (len == READ_SIZE)
		{
			ptr = realloc(buf, READ_SIZE * 2 + 1);
			if (!ptr)
			{
				free(buf);
				return (-1);
			}
		}
	}
	return (0);
}


/**
 * _getline - Read from fd and return lines.
 *
 * @fd: file descriptor
 * Return: Null-terminated string, or NULL on failure.
 */
char *_getline(const int fd)
{
	size_t i;
	static size_t cur_len;
	static char *buf;
	char *ptr;

	if (!buf)
	{
		buf = malloc(sizeof(char) * READ_SIZE);
		if (!buf)
		{
			/* factor out these two lines in a free_mem func */
			free(buf);
			return (NULL);
		}

		/* read all bytes from fd and store them in buffer */
		/* re-size buffer if needed */

		if ((read_into_buffer(fd, buf)) == -1)
			return (NULL);
	}

	/* find and return lines */
	for (i = 0; buf[i]; ++i)
	{
		if (buf[i] == '\n')
		{
			cur_len += i + 1;
			ptr = malloc(sizeof(char) * i + 1);
			memcpy(ptr, buf, i);
			buf += i + 1;
			ptr[i] = '\0';
			return (ptr);
		}
	}

	buf -= cur_len;
	free(buf);
	return (NULL);
}
