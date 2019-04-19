#include "hls.h"

/**
 * _calloc - allocate and zero out memory.
 *
 * @nmemb: number of elements
 * @size: size of each `nmemb` element
 * Return: pointer to allocated memory, or NULL on failure.
 */
void *_calloc(size_t nmemb, size_t size)
{
	/* malloc */
	/* zero out memory */
	/* return pointer to zero'd out memory */

	void *ptr;
	char *cur;
	size_t i, total_bytes;

	total_bytes = nmemb * size;
	ptr = malloc(total_bytes);
	if (!ptr)
		return (NULL);

	cur = ptr;
	for (i = 0; i < total_bytes; i++)
	{
		cur[i] = 0;
	}

	return (ptr);
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
