#include "hls.h"

/**
 * print_type - print file type.
 *
 * @buf: stat structure
 */
void print_type(struct stat buf)
{
	switch (buf.st_mode & S_IFMT)
	{
	case S_IFBLK:
		printf("b");
		break;
	case S_IFCHR:
		printf("c");
		break;
	case S_IFDIR:
		printf("d");
		break;
	case S_IFIFO:
		printf("p");
		break;
	case S_IFLNK:
		printf("l");
		break;
	case S_IFREG:
		printf("-");
		break;
	case S_IFSOCK:
		printf("s");
		break;
	default:
		printf("?");
		break;
	}
}

/**
 * print_permissions - print file permissions.
 *
 * @buf: stat structure
 */
void print_permissions(struct stat buf)
{
	if (buf.st_mode & S_IRWXU)
	{
		printf("%c%c%c",
		       buf.st_mode & S_IRUSR ? 'r' : '-',
		       buf.st_mode & S_IWUSR ? 'w' : '-',
		       buf.st_mode & S_IXUSR ? 'x' : '-');
	}
	if (buf.st_mode & S_IRWXG)
	{
		printf("%s%s%s",
		       buf.st_mode & S_IRGRP ? "r" : "-",
		       buf.st_mode & S_IWGRP ? "w" : "-",
		       buf.st_mode & S_IXGRP ? "x" : "-");
	}
	if (buf.st_mode & S_IRWXO)
	{
		printf("%s%s%s",
		       buf.st_mode & S_IROTH ? "r" : "-",
		       buf.st_mode & S_IWOTH ? "w" : "-",
		       buf.st_mode & S_IXOTH ? "x" : "-");
	}
}

/**
 * print_long_format - print file names using long format via `-l` flag.
 *
 * @file: file name
 * @path: directory path
 */
void print_long_format(const char *file, char *path)
{
	struct stat buf;
	struct passwd *pwd;
	struct group *grp;
	char *fullpath, *time;
	int pathlen;

	pathlen = 0;
	pathlen = _strlen((char *) file) + _strlen(path) + 1;
	fullpath = _calloc(pathlen, sizeof(char));
	_strcpy(fullpath, path);
	_strcat(fullpath, (char *) file);

	lstat(fullpath, &buf);
	free(fullpath);

	print_type(buf);
	print_permissions(buf);

	/* print number of links */
	printf(" %lu", buf.st_nlink);

	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	if (pwd != NULL)
		printf(" %s ", pwd->pw_name);
	else
		printf(" %-8d ", buf.st_uid);
	if (grp != NULL)
		printf(" %s ", grp->gr_name);
	else
		printf(" %-8d ", buf.st_gid);
	printf("%d ", (int) buf.st_size);

	/* print time */
	time = ctime(&(buf.st_mtime));
	time = date_format(time);
	printf("%s ", time);
	free(time);
	printf("%s", file);
}

/**
 * print_files - print file names
 *
 * @dir_items: list of files names in the directory
 * @dir_path: directory path
 * @format: enum for formatting flags
 */
void print_files(const char **dir_items, char *dir_path, enum format format)
{
	size_t i;

	switch (format)
	{
	case one_per_line:
		for (i = 0; dir_items[i]; ++i)
			printf("%s\n", dir_items[i]);
		break;
	case long_format:
		for (i = 0; dir_items[i]; ++i)
		{
			print_long_format(dir_items[i], dir_path);
			printf("\n");
		}
		break;
	default:
		for (i = 0; dir_items[i]; ++i)
		{
			printf("%s%s",
			       dir_items[i],
			       dir_items[i + 1] ? "  " : "\n");
		}
	}
}

/**
 * print_path_name - print directory name
 *
 * @path: directory path name
 * Return: int 0 after execution
 */
int print_path_name(char *path)
{
	printf("%s:\n", path);
	return (0);
}
