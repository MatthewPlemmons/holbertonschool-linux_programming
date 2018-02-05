#ifndef HLS_HEADER_
#define HLS_HEADER_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

#define FILE_COUNT 50
#define MAX_FILENAME_SIZE 256

/**
 * enum print_mode - keeps track of option flags for printing directory contents.
 *
 * @print_all: prints all directory contents
 * @almost_all: prints all directory contents but ignores `.` and `..`
 */
enum print_mode
{
	print_all = 1,
	almost_all = 2
};

/**
 * enum format - keeps track of option flags for formatting output.
 *
 * @one_per_line: prints one filename per line
 * @long_format: prints additional file information
 */
enum format
{
	one_per_line = 1,
	long_format = 2
};

void print_type(struct stat buf);
void print_permissions(struct stat buf);
void print_long_format(const char *file, char *path);
void print_files(const char **items, char *dir_path, enum format format);
int print_path_name(char *path);
/*void print_file_name(char *file); */
/*int print_items(const char **items);*/

const char **collect_names(char *items,
			   size_t file_count,
			   enum print_mode print_mode);
int free_ptr_array(const char **arr, size_t file_count);

int sort_items(const char **items);
int a_sort(const char *a, const char *b);

char **parse_args(size_t argc, char **argv);
int check_flags(char *flags, enum format *format, enum print_mode *print_mode);
int flag_count(char **argv, enum format *format, enum print_mode *print_mode);

char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strlen(char *s);

#endif
