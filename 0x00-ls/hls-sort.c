#include "hls.h"

/**
 * a_sort - sort filenames alphabetically
 *
 * @a: string to sort
 * @b: string to sort
 * Return: integer value based on string a comparison to string b.
 */
int a_sort(const char *a, const char *b)
{
	int r;

	r = strcasecmp(a, b);
	if (r)
		return (r);
	return (-strcmp(a, b));
}

/**
 * sort_items - sort filenames
 *
 * @dir_items: list of filenames in a directory
 * Return: int 0 on successful execution.
 */
int sort_items(const char **dir_items)
{
	char temp[MAX_FILENAME_SIZE];
	size_t i, j;

	for (i = 0; dir_items[i]; ++i)
	{
		for (j = i + 1; dir_items[j]; ++j)
		{
			if (a_sort(dir_items[i], dir_items[j]) > 0)
			{
				_strcpy(temp, (char *) dir_items[i]);
				_strcpy((char *) dir_items[i],
					(char *) dir_items[j]);
				_strcpy((char *) dir_items[j], temp);
			}
		}
	}
	return (0);
}
