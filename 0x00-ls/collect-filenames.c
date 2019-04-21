#include "hls.h"


/**
 * init_file_list - allocate space to store file names.
 *
 * @dir_items: array for storing file name strings
 * @n_files: number of files in this directory
 */
void init_file_list(const char **dir_items, size_t n_files)
{
	size_t i;

	for (i = 0; i < n_files; ++i)
	{
		dir_items[i] = _calloc(MAX_FILENAME_SIZE, sizeof(char));
		if (!dir_items[i])
			exit(EXIT_FAILURE);
	}
}

/**
 * collect_all - collect all file names.
 *
 * @dir_items: array for storing file name strings
 * @dir: pointer to a directory stream
 */
void collect_all(const char **dir_items, DIR *dir)
{
	struct dirent *read;
	size_t i;

	i = 0;
	while ((read = readdir(dir)) != NULL)
	{
		_strcpy((char *) dir_items[i], read->d_name);
		++i;
	}
	dir_items[i] = NULL;
}

/**
 * collect_almost_all - collect all names, except the `.` and `..` directories.
 *
 * @dir_items: array for storing file name strings
 * @dir: pointer to a directory stream
 */
void collect_almost_all(const char **dir_items, DIR *dir)
{
	struct dirent *read;
	size_t i;

	i = 0;
	while ((read = readdir(dir)) != NULL)
	{
		if (read->d_name[0] == '.' && read->d_name[1] == '\0')
			continue;
		if (read->d_name[0] == '.'
		    && read->d_name[1] == '.'
		    && read->d_name[2] == '\0')
			continue;
		_strcpy((char *) dir_items[i], read->d_name);
		++i;
	}
	dir_items[i] = NULL;
}

/**
 * collect_default - collect filenames, except hidden files beginning with `.`.
 *
 * @dir_items: array for storing file name strings
 * @dir: pointer to a directory stream
 */
void collect_default(const char **dir_items, DIR *dir)
{
	struct dirent *read;
	size_t i;

	i = 0;
	while ((read = readdir(dir)) != NULL)
	{
		if (read->d_name[0] == '.')
			continue;
		_strcpy((char *) dir_items[i], read->d_name);
		++i;
	}
	dir_items[i] = NULL;
}

/**
 * collect_names - store filenames located in a directory.
 *
 * @path: directory path
 * @n_files: number of files in the directory
 * @print_mode: determines what file names to collect for printing
 * Return: array of file names collected.
 */
const char **collect_names(char *path,
			   size_t n_files,
			   enum print_mode print_mode)
{
	DIR *dir;
	const char **dir_items;

	dir_items = _calloc(n_files + 1, sizeof(char *));
	if (!dir_items)
		exit(EXIT_FAILURE);

	init_file_list(dir_items, n_files);

	dir = opendir(path);
	if (!dir)
		exit(EXIT_FAILURE);

	switch (print_mode)
	{
	case print_all:
		collect_all(dir_items, dir);
		break;
	case almost_all:
		collect_almost_all(dir_items, dir);
		break;
	default:
		collect_default(dir_items, dir);
	}
	closedir(dir);
	return (dir_items);
}
