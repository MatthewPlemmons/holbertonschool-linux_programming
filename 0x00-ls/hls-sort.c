#include "hls.h"

/**
 * a_sort - sort filenames alphabetically
 *
 * @a:
 * @b:
 * Return:
 */
int a_sort (const char *a, const char *b) {
        int r = strcasecmp(a, b);
        if (r) return r;
        /* if equal ignoring case, use opposite of strcmp() result to get
         * lower before upper */
        return -strcmp(a, b);
}

/**
 * sort_items - sort filenames
 *
 * @dir_names:
 * Return:
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
                                strcpy(temp, (char *) dir_items[i]);
                                strcpy((char *) dir_items[i], dir_items[j]);
                                strcpy((char *) dir_items[j], temp);
                        }
                }
        }
        return (0);
}
