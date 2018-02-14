#ifndef _GETLINE_H
#define _GETLINE_H

#define READ_SIZE 4096

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

char *_getline(const int fd);

#endif
