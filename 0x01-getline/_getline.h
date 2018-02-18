#ifndef _GETLINE_H
#define _GETLINE_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define READ_SIZE 4096
#define OPEN_MAX 20

/**
 * struct fdbuf_t - Contains file descriptor information.
 * @fd: file descriptor
 * @cur_len: current bytes read from the buffer
 * @len: total length of buffer in bytes
 * @buf: buffer containing bytes read from fd
 */
typedef struct fdbuf_t
{
	int fd;
	ssize_t cur_len;
	ssize_t len;
	char *buf;
} fdbuf_t;

char *_getline(const int fd);

#endif
