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
        case S_IFBLK: printf("b"); break;
        case S_IFCHR: printf("c"); break;
        case S_IFDIR: printf("d"); break;
        case S_IFIFO: printf("p"); break;
        case S_IFLNK: printf("l"); break;
        case S_IFREG: printf("-"); break;
        case S_IFSOCK: printf("s"); break;
        default: printf("?"); break;
        }

        return;
}

/**
 * print_permissions - print file permissions
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
        return;
}


/**
 * print_items - print items found in the directory.
 * @dir_items:
 * Return:
 */
/*
int print_items(const char **dir_items)
{
        size_t i;

        for (i = 0; dir_items[i]; ++i)
        {
		if (fmt & all_fmt)
		{
			if (dir_items[i][0] == '.')
			{
				printf("%s", dir_items[i]);
				if (fmt & one_per_line)
					putchar('\n');
				else if (dir_items[i + 1])
					printf("  ");
				continue;
			}
		}
		if (fmt & almost_all)
		{
			if (dir_items[i][0] == '.' && !dir_items[i][1])
				continue;
			if (dir_items[i][0] == '.' && dir_items[i][1] == '.')
				continue;
		}

                printf("%s", dir_items[i]);
		if (fmt & one_per_line)
			putchar('\n');
		else if (dir_items[i + 1])
			printf("  ");
		else
			putchar('\n');
        }
        return (0);
}
*/

/*
void print_file_name(char *file)
{
	switch (format)
	{
	case all_fmt:
		printf("%s", file);
		break;
	case almost_all:
		if (file[0] == '.' && file[1] == NULL)
			break;
		if (file[0] == '.' && file[1] == '.' && file[2] == NULL)
			break;
	}
}
*/

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

	pathlen = _strlen((char *) file) + _strlen(path) + 1;
	fullpath = malloc(sizeof(char) * pathlen);
	_strcpy(fullpath, path);
	_strcat(fullpath, "/");
	_strcat(fullpath, (char *) file);

	lstat(fullpath, &buf);
	free(fullpath);

	print_type(buf);
	print_permissions(buf);

	pwd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	printf(" %s %s ", pwd->pw_name, grp->gr_name);
	printf("%d ", (int) buf.st_size);

	/* print time */
	time = ctime(&(buf.st_mtime));
	printf("%s ", time);
	printf("%s", file);
}

/**
 * print_files - print file names
 *
 * @dir_items: list of files names in the directory
 * @dir_path: directory path
 */
void print_files(const char **dir_items, char *dir_path)
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
			putchar('\n');
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
 */
int print_path_name(char *path)
{
	printf("%s:\n", path);
	return (0);
}
