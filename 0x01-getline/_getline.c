#include "_getline.h"

/**
 * read_into_buffer - Read from fd into buffer.
 * @fd: file descriptor
 * @buf: buffer
 * Return: 0 if successful, otherwise -1.
 */
char *read_into_buffer(const int fd, char *buf)
{
	static ssize_t curr_len;
	ssize_t len, needed;
	char *ptr;

/*	ptr = buf;*/
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
			ptr = realloc(buf, needed);
			if (!ptr)
			{
				free(ptr);
				return (NULL);
			}
			buf = ptr;
		}
		curr_len += len;
		if (len < READ_SIZE)
		{
			buf[curr_len] = '\0';
			break;
		}
	}
	ptr = realloc(buf, curr_len + 1);
	if (!ptr)
	{
		free(ptr);
		return (NULL);
	}
	buf = ptr;
	buf[curr_len] = '\0';
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
		buf = malloc(sizeof(char) * READ_SIZE);
		if (!buf)
		{
			free(buf);
			return (NULL);
		}

		if ((buf = read_into_buffer(fd, buf)) == NULL)
		{
			free(buf);
			return (NULL);
		}
	}

	/* for (i=0; buf[cur_len + i]; ++i)*/
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
			/*lineptr = buf + cur_len;*/
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
