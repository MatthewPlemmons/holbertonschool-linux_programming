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
size_t n_dir_args, file_count;

enum print_mode
{
	print_all = 1,
	almost_all = 2
};
enum print_mode print_mode;

enum format
{
	one_per_line = 1,
	long_format = 2
};
enum format format;

void print_type(struct stat buf);
void print_permissions(struct stat buf);
void print_long_format(const char *file, char *path);
void print_files(const char **items, char *dir_path);
int print_path_name(char *path);
/*void print_file_name(char *file); */
/*int print_items(const char **items);*/

const char **collect_names(char *items);
int free_ptr_array(const char **arr);

int sort_items(const char **items);
int a_sort(const char *a, const char *b);

char **parse_args(size_t argc, char **argv);
int check_flags(char *flags);
int flag_count(char **argv);

char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strlen(char *s);

#endif
