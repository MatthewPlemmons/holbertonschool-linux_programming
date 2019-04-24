#include "hls.h"

/**
 * extract_directory_paths - copy directory paths passed via command line.
 *
 * @dir_paths: list of directory paths
 * @argv: list of arguments entered from command line
 * Return: 1 or 2 on error, 0 otherwise.
 */
int extract_directory_paths(char **dir_paths, char *argv[])
{
	int i, n, index, err, exit_status;

	exit_status = 0;
	index = 0;
	for (i = 1; argv[i]; ++i)
	{
		if (argv[i][0] == '-')
			continue;

		err = is_valid_directory(argv[i]);
		if (err == 0)
		{
			/* Check if path string ends with a '/' */
			n = _strlen(argv[i]);
			if (n < MAX_PATH_SIZE - 1)
			{
				if (argv[i][n - 1] != '/')
					++n;
				dir_paths[index] = _calloc(sizeof(char),
							  MAX_PATH_SIZE);
				_strcpy(dir_paths[index], argv[i]);

				if (dir_paths[index][n - 1] != '/')
					_strcat(dir_paths[index], "/");
				++index;
			}
			else
				printf("directory path too long.\n");
		}
		else
			exit_status = err;
	}
	dir_paths[index] = NULL;
	return (exit_status);
}

/**
 * check_flags - check which command line option flags were set, if any.
 *
 * @flags: string containing possible option chars
 * @format: pointer to format enum
 * @print_mode: pointer to print_mode enum
 * Return: 0 if successful.
 */
size_t check_flags(char *flags,
		   enum format *format,
		   enum print_mode *print_mode)
{
	size_t i, count;

	count = 0;
	for (i = 1; flags[i]; ++i)
	{
		if (flags[i] == '1')
		{
			*format |= one_per_line;
			++count;
			continue;
		}
		if (flags[i] == 'l')
		{
			*format |= long_format;
			++count;
			continue;
		}
		if (flags[i] == 'a')
		{
			*print_mode |= print_all;
			++count;
			continue;
		}
		if (flags[i] == 'A')
		{
			*print_mode |= almost_all;
			++count;
			continue;
		}
		/* if flag not found, print an error message */
		printf("hls: invalid option -- '%c'\n", flags[i]);
		free(format);
		free(print_mode);
		exit(2);
	}

	return (count);
}


/**
 * is_valid_directory - check if the path string is a directory.
 *
 * @path: directory path to check
 * Return: 0 if `path` is a directory, else 2.
 */
int is_valid_directory(char *path)
{
	DIR *dir;
	int err;

	dir = opendir((const char *) path);
	if (!dir)
	{
		err = errno;
		error_handler(err, path);
		return (2);
	}
	if (closedir(dir) == -1)
	{
		perror("hls");
		return (2);
	}
	return (0);

}

/**
 * parse_args - parse command line arguments.
 *
 * @argv: list of command line arguments
 * @format: pointer to format enum
 * @print_mode: pointer to print_mode enum
 * Return: number of directory paths included in command line arguments.
 */
size_t parse_args(char **argv,
		  enum format *format,
		  enum print_mode *print_mode)
{
	size_t i, count;

	count = 0;
	for (i = 1; argv[i]; ++i)
	{
		if (argv[i][0] == '-')
		{
			check_flags(argv[i], format, print_mode);
		}
		else
		{
			++count;
		}
	}
	return (count);
}
