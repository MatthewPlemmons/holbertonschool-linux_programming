#include "_getline.h"

/**
 * read_into_buffer - Read bytes from fd into buffer.
 *
 * @fd: file descriptor
 * @buf: buffer
 * Return: Buffer containing bytes read in from fd, or NULL on failure.
 */
char *read_into_buffer(const int fd, char *buf)
{
	static ssize_t curr_len;
	ssize_t len, needed;

	curr_len = 0;
	needed = READ_SIZE;
	while ((len = read(fd, buf + curr_len, READ_SIZE)) > 0)
	{
		if (len == -1)
		{
			return (NULL);
		}
		if (len == READ_SIZE)
		{
			needed += READ_SIZE;
			buf = realloc(buf, needed);
			if (!buf)
			{
				free(buf);
				return (NULL);
			}
		}
		curr_len += len;
		if (len < READ_SIZE)
		{
			buf[curr_len] = '\0';
			break;
		}
	}

	buf = realloc(buf, curr_len + 1);
	if (!buf)
	{
		free(buf);
		return (NULL);
	}

	buf[curr_len] = '\0';
	return (buf);
}

/**
 * allocate_buffer - Allocate space for a buffer to store data from fd.
 *
 * @fd: file descriptor
 * @buf: buffer
 * Return: Buffer containing bytes read in from fd, or NULL on failure.
 */
char *allocate_buffer(const int fd, char *buf)
{
	buf = malloc(sizeof(char) * READ_SIZE);
	if (!buf)
	{
		free(buf);
		return (NULL);
	}
	buf = read_into_buffer(fd, buf);
	if (!buf)
	{
		free(buf);
		return (NULL);
	}
	return (buf);

}

/**
 * _getline - Read from fd and return lines.
 *
 * @fd: file descriptor
 * Return: Null-terminated string, or NULL on failure.
 */
char *_getline(const int fd)
{
	static ssize_t cur_len;
	ssize_t i;
	static char *buf;
	char *ptr;

	if (!buf)
	{
		buf = allocate_buffer(fd, buf);
		if (!buf)
		{
			free(buf);
			return (NULL);
		}
	}

	for (i = 0; buf[i]; ++i)
	{
		if (buf[i] == '\n')
		{
			ptr = malloc(sizeof(char) * i + 1);
			if (!ptr)
			{
				free(ptr);
				break;
			}
			memcpy(ptr, buf, i);
			buf += i + 1;
			ptr[i] = '\0';
			cur_len += i + 1;
			return (ptr);
		}
	}

	buf -= cur_len;
	free(buf);
	return (NULL);
}
