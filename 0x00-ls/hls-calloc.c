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
