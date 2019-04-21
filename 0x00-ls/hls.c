#include "hls.h"


/**
 * count_files - count the number of files in a directory.
 *
 * @path: directory path
 * @print_mode: print mode
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
 * init_dir_paths - allocate memory for storing directory path strings.
 *
 * @n_dirs: number of directories
 * Return: pointer to array for storing directory path strings
 */
char **init_dir_paths(size_t n_dirs)
{
	char **dir_paths;

	if (n_dirs == 0)
	{
		/* if no directories given, use `./` to search current dir */
		dir_paths = _calloc(2, sizeof(char *));
		dir_paths[0] = _calloc(MAX_PATH_SIZE, sizeof(char));
		_strcpy(dir_paths[0], "./");
		dir_paths[1] = NULL;
		return (dir_paths);
	}
	dir_paths = _calloc(n_dirs + 1, sizeof(char *));
	return (dir_paths);
}

/**
 * print_dirs - print contents of directories.
 *
 * @dir_paths: array of directory path strings
 * @n_dirs: number of directories
 * @format: print format
 * @print_mode: print mode
 */
void print_dirs(char **dir_paths,
		size_t n_dirs,
		enum format *format,
		enum print_mode *print_mode)
{
	const char **dir_items;
	size_t i, n_files;

	for (i = 0; dir_paths[i]; ++i)
	{
		n_files = count_files(dir_paths[i], *print_mode);
		dir_items = collect_names(dir_paths[i],
					  n_files,
					  *print_mode);
		/*sort_items(dir_items);*/
		if (n_dirs > 1)
			print_path_name(dir_paths[i]);
		print_files(dir_items, dir_paths[i], *format);
		if (dir_paths[i + 1])
			printf("\n");
		free_ptr_array(dir_items, n_files);
	}
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
	char **dir_paths;
	size_t i, n_dirs;
	enum format *format;
	enum print_mode *print_mode;
	int exit_status;

	(void) argc;

	format = _calloc(2, sizeof(enum format));
	if (!format)
		exit(EXIT_FAILURE);

	print_mode = _calloc(2, sizeof(enum print_mode));
	if (!print_mode)
		exit(EXIT_FAILURE);

	exit_status = 0;
	n_dirs = 0;

	/* `parse_args()` sets the `format` and `print_mode` */
	n_dirs = parse_args(argv, format, print_mode);
	dir_paths = init_dir_paths(n_dirs);

	if (n_dirs > 0)
		exit_status = extract_directory_paths(dir_paths, argv);
	else
		n_dirs = 1;

	/*exit_status = errno;*/
	print_dirs(dir_paths, n_dirs, format, print_mode);

	for (i = 0; i < n_dirs; ++i)
		free(dir_paths[i]);

	free(dir_paths);
	free(format);
	free(print_mode);
	return (exit_status);
}
