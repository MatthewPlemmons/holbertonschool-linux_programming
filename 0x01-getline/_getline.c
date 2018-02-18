#include "_getline.h"

/**
 * _realloc - Reallocates memory by size bytes.
 *
 * @ptr: pointer to the memory block being reallocated
 * @size: size of new allocation
 * Return: Pointer to reallocated block of memory.
 */
char *_realloc(char *ptr, ssize_t size)
{
	char *tmp, *buf;
	ssize_t i, size_offset;

	tmp = malloc(sizeof(char) * size);
	if (!tmp)
		return (NULL);

	if (size <= READ_SIZE)
		size_offset = 0;
	else
		size_offset = READ_SIZE;

	for (i = 0; i < size - size_offset; ++i)
		tmp[i] = ptr[i];

	buf = malloc(sizeof(char) * size);
	if (!buf)
	{
		free(tmp);
		return (NULL);
	}
	for (i = 0; i < size; ++i)
		buf[i] = tmp[i];

	free(tmp);
	free(ptr);
	return (buf);
}

/**
 * read_into_buffer - Read bytes from fd into buffer.
 *
 * @fd: file descriptor
 * @buf: buffer
 * @fds: pointer array for fdbuf_t structures
 * Return: Buffer containing bytes read in from fd, or NULL on failure.
 */
char *read_into_buffer(const int fd, char *buf, struct fdbuf_t **fds)
{
	static ssize_t curr_len;
	ssize_t len, needed;

	curr_len = 0;
	needed = READ_SIZE;
	while ((len = read(fd, buf + curr_len, READ_SIZE)) > 0)
	{
		if (len == -1)
			return (NULL);
		if (len == READ_SIZE)
		{
			needed += READ_SIZE;
			buf = _realloc(buf, needed);
			if (!buf)
				return (NULL);
		}
		curr_len += len;
		if (len < READ_SIZE)
			break;
	}

	buf = _realloc(buf, curr_len + 1);
	if (!buf)
		return (NULL);

	buf[curr_len] = '\0';
	fds[fd]->len = curr_len;
	return (buf);
}

/**
 * allocate_buffer - Allocate space for a buffer to store data from fd.
 *
 * @fd: file descriptor
 * @fds: pointer array to fd structures
 * Return: Buffer containing bytes read in from fd, or NULL on failure.
 */
fdbuf_t *allocate_buffer(const int fd, struct fdbuf_t **fds)
{
	char *buf;

	buf = malloc(sizeof(char) * READ_SIZE);
	if (!buf)
		return (NULL);

	fds[fd] = malloc(sizeof(struct fdbuf_t));
	if (!fds[fd])
	{
		free(buf);
		return (NULL);
	}

	buf = read_into_buffer(fd, buf, fds);
	if (!buf)
	{
		free(fds[fd]);
		free(buf);
		return (NULL);
	}

	fds[fd]->fd = fd;
	fds[fd]->cur_len = 0;
	fds[fd]->buf = buf;
	return (fds[fd]);
}

/**
 * _getline - Read from fd and return lines.
 *
 * @fd: file descriptor
 * Return: Null-terminated string, or NULL on failure.
 */
char *_getline(const int fd)
{
	ssize_t i, j;
	char *ptr;
	static struct fdbuf_t *fds[OPEN_MAX];

	if (fd == -1)
	{
		for (i = 0; i < OPEN_MAX; ++i)
		{
			if (fds[i] == NULL)
				continue;
			fds[i]->buf -= fds[i]->cur_len;
			fds[i]->cur_len = 0;

			for (j = 0; j < fds[i]->len - 1; ++j)
				fds[i]->buf[j] = '\0';

			free(fds[i]->buf);
			fds[i]->buf = NULL;
			free(fds[i]);
			fds[i] = NULL;
		}
		return (NULL);
	}
	if (fds[fd] == NULL)
	{
		fds[fd] = allocate_buffer(fd, fds);
		if (!fds[fd])
			return (NULL);
	}

	for (i = 0; fds[fd]->buf[i]; ++i)
	{
		if (fds[fd]->buf[i] == '\n')
		{
			ptr = malloc(sizeof(char) * i + 1);
			if (!ptr)
			{
				free(ptr);
				break;
			}
			memcpy(ptr, fds[fd]->buf, i);
			ptr[i] = '\0';
			fds[fd]->buf += i + 1;
			fds[fd]->cur_len += i + 1;
			return (ptr);
		}
	}

	fds[fd]->buf -= fds[fd]->cur_len;
	fds[fd]->cur_len = 0;
	return (NULL);
}
