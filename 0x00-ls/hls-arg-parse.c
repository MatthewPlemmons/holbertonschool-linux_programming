#include "hls.h"

/**
 * extract_directory_paths - copy directory paths passed via command line.
 *
 * @dir_paths: list of directory paths
 * @argv: list of arguments entered from command line
 * Return: sorted list of directory paths.
 */
void extract_directory_paths(char **dir_paths, char *argv[])
{
	int i, n, index;

	index = 0;
	for (i = 1; argv[i]; ++i)
	{
		if (argv[i][0] == '-')
			continue;

		if (is_valid_directory(argv[i]) == 0)
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
	}
	dir_paths[index] = NULL;
	/*return (dir_paths);*/
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
	for (i = 0; flags[i]; ++i)
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
		/* free `format` and `print_mode` and exit */
		/*flags[i]*/
	}

	return (count);
}


/**
 * check_valid_directory - check if the path string is a directory.
 *
 * @path: directory path to check
 * Return: 0 if `path` is a directory, else 1.
 */
size_t is_valid_directory(char *path)
{
	DIR *dir;
	int err;

	dir = opendir((const char *) path);
	if (!dir)
	{
		err = errno;
		error_handler(err, path);
		return (1);
	}
	if (closedir(dir) == -1)
	{
		perror("hls");
		return (1);
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
