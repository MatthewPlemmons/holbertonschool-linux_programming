#include "hls.h"

/**
 * print_error - print error messages.
 *
 * @s: string that initiated error
 */
void print_error(const char *s)
{
	if (errno == ENOENT)
		perror(s);
	if (errno == EACCES)
		perror(s);
}

/**
 * count_files - count the number of files in a directory.
 *
 * @path: directory path
 * Return: number of files in directory.
 */
size_t count_files(char *path)
{
	struct dirent *read;
	DIR *dir;
	size_t file_count;

	file_count = 0;
	dir = opendir(path);

	if (!dir)
	{
		print_error((const char *) path);
		exit(EXIT_FAILURE);
	}

	while ((read = readdir(dir)) != NULL)
		++file_count;
	closedir(dir);
	return (file_count);
}

/**
 * collect_names - store filenames located in a directory.
 *
 * @path: directory path
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

	dir_items = malloc(sizeof(char *) * file_count + 1);
	for (i = 0; i < file_count; ++i)
	{
		dir_items[i] = malloc(sizeof(char) * MAX_FILENAME_SIZE);
	}

	dir = opendir(path);
	i = 0;

	switch (print_mode)
	{
	case print_all:
		while ((read = readdir(dir)) != NULL)
		{
			strcpy((char *) dir_items[i], read->d_name);
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
			strcpy((char *) dir_items[i], read->d_name);
			++i;
		}
		break;
	default:
		while ((read = readdir(dir)) != NULL)
		{
			if (read->d_name[0] == '.')
				continue;
			strcpy((char *) dir_items[i], read->d_name);
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
 * Return: 0 if successful.
 */
int free_ptr_array(const char **arr, size_t file_count)
{
	size_t i;

	for (i = 0; i < file_count; ++i)
		free((void *) arr[i]);
	free(arr);
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
	size_t i, n_dir_args, file_count;
	enum format format;
	enum print_mode print_mode;

	n_dir_args = (argc - 1) - flag_count(argv);
	if (!n_dir_args)
	{
		file_count = count_files(".");
		dir_items = collect_names(".", file_count, print_mode);
		sort_items(dir_items);
		print_files(dir_items, ".", format);
		free_ptr_array(dir_items, file_count);
	}
	else
	{
		dir_paths = parse_args(n_dir_args, argv);
		for (i = 0; dir_paths[i]; ++i)
		{
			file_count = count_files(dir_paths[i]);
			dir_items = collect_names(dir_paths[i],
						  file_count,
						  print_mode);
			sort_items(dir_items);

			if (n_dir_args > 1)
				print_path_name(dir_paths[i]);
			print_files(dir_items, dir_paths[i], format);

			if (dir_paths[i + 1])
				putchar('\n');
			free_ptr_array(dir_items, file_count);
		}
		for (i = 0; i < n_dir_args; ++i)
			free(dir_paths[i]);
		free(dir_paths);
	}

	return (0);
}
