#include "hls.h"


/**
 * count_files - count the number of files in a directory.
 *
 * @path: directory path
 * Return: number of files in directory.
 */
size_t count_files(char *path, enum print_mode print_mode)
{
	struct dirent *read;
	DIR *dir;
	size_t file_count;

	file_count = 0;
	dir = opendir(path);
	if (!dir)
	{
		/*print_error((const char *) path);*/
	}

	while ((read = readdir(dir)) != NULL)
	{
		switch (print_mode)
		{
		case print_all:
			++file_count;
			break;
		case almost_all:
			if (_strcmp("..", read->d_name) == 0 ||
			    _strcmp(".", read->d_name) == 0)
				continue;
			++file_count;
			break;
		default:
			if (read->d_name[0] != '.')
				++file_count;
		}

	}
	closedir(dir);
	return (file_count);
}

/**
 * collect_names - store filenames located in a directory.
 *
 * @path: directory path
 * @file_count: number of files in directory
 * @print_mode: enum to keep track of print_mode options
 * Return: list of filenames in the directory.
 */
const char **collect_names(char *path,
			   size_t file_count,
			   enum print_mode print_mode)
{
	struct dirent *read;
	DIR *dir;
	const char **dir_items;
	size_t i;

	/* add error checking for this malloc call */
	dir_items = _calloc(file_count + 1, sizeof(char *));
	for (i = 0; i < file_count; ++i)
	{
		dir_items[i] = _calloc(MAX_FILENAME_SIZE, sizeof(char));
	}

	/* check `dir` for NULL */
	dir = opendir(path);
	i = 0;

	switch (print_mode)
	{
	case print_all:
		while ((read = readdir(dir)) != NULL)
		{
			_strcpy((char *) dir_items[i], read->d_name);
			++i;
		}
		break;

	case almost_all:
		while ((read = readdir(dir)) != NULL)
		{
			if (read->d_name[0] == '.' && read->d_name[1] == '\0')
			{
				continue;
			}
			if (read->d_name[0] == '.'
			    && read->d_name[1] == '.'
			    && read->d_name[2] == '\0')
			{
				continue;
			}
			_strcpy((char *) dir_items[i], read->d_name);
			++i;
		}
		break;
	default:
		while ((read = readdir(dir)) != NULL)
		{
			if (read->d_name[0] == '.')
				continue;
			_strcpy((char *) dir_items[i], read->d_name);
			++i;
		}
	}
	dir_items[i] = NULL;
	closedir(dir);
	return (dir_items);
}

/**
 * free_ptr_array - free space allocated for filenames.
 *
 * @arr: list of filenames
 * @file_count: number of files in directory
 * Return: 0 if successful.
 */
int free_ptr_array(const char **arr, size_t file_count)
{
	size_t i;

	for (i = 0; i < file_count; ++i)
		free((void *) arr[i]);
	free((void *) arr);
	return (0);
}

/**
 * main - custom implementation of the `ls` command.
 *
 * @argc: argument count
 * @argv: argument vector
 * Return: int 0 on successful execution.
 */
int main(int argc, char *argv[])
{
	const char **dir_items;
	char **dir_paths;
	/*char *dir_path;*/
	size_t i, n_dir_args, file_count;
	enum format *format;
	enum print_mode *print_mode;

	(void) argc;

	format = _calloc(2, sizeof(enum format));
	if (!format)
		exit(EXIT_FAILURE);

	print_mode = _calloc(2, sizeof(enum print_mode));
	if (!print_mode)
		exit(EXIT_FAILURE);

	n_dir_args = 0;

	/* `parse_args()` sets the `format` and `print_mode` */
	n_dir_args = parse_args(argv, format, print_mode);
	dir_paths = extract_directory_paths(n_dir_args, argv);
	if (n_dir_args == 0)
		n_dir_args = 1;

	for (i = 0; dir_paths[i]; ++i)
	{
		file_count = count_files(dir_paths[i], *print_mode);
		dir_items = collect_names(dir_paths[i],
					  file_count,
					  *print_mode);
		/*sort_items(dir_items);*/

		if (n_dir_args > 1)
			print_path_name(dir_paths[i]);
		print_files(dir_items, dir_paths[i], *format);

		if (dir_paths[i + 1])
			printf("\n");
		free_ptr_array(dir_items, file_count);
	}

	for (i = 0; i < n_dir_args; ++i)
		free(dir_paths[i]);

	free(dir_paths);
	free(format);
	free(print_mode);
	return (0);
}
