#include "hls.h"

/**
 * parse_args -
 *
 * @n_dir_args:
 * @argv:
 * Return:
 */
char **parse_args(size_t n_dir_args, char *argv[])
{
        int i, index;
        char **dir_paths;

        dir_paths = malloc(sizeof(char *) * n_dir_args + 1);

        /* Using two main counter variables on this loop, `index`
           and `i`, for `dir_paths` and `argv`. */
        index = 0;
        for (i = 1; argv[i]; ++i)
        {
                if (argv[i][0] == '-')
                        continue;

                dir_paths[index] = malloc(sizeof(char) * MAX_FILENAME_SIZE);
                strcpy(dir_paths[index], argv[i]);
                ++index;
        }
        dir_paths[index] = NULL;

        /* sort the directory path names */
        sort_items((const char **) dir_paths);

        return (dir_paths);
}

/**
 * check_flags -
 *
 * @flags:
 * Return:
 */
int check_flags(char *flags)
{
        size_t i;

        for (i = 0; flags[i]; ++i)
        {
                if (flags[i] == '1')
                {
                        format |= one_per_line;
                        continue;
                }
                if (flags[i] == 'l')
                {
                        format |= long_format;
                        continue;
                }
                if (flags[i] == 'a')
                {
                        print_mode |= print_all;
                        continue;
                }
                if (flags[i] == 'A')
                {
                        print_mode |= almost_all;
                        continue;
                }

        }
        return (0);
}

/**
 * flag_count -
 *
 * @argv:
 * Return:
 */
int flag_count(char **argv)
{
        int i, count;

        count = 0;
        for (i = 0; argv[i]; ++i)
        {
                if (argv[i][0] == '-')
                {
                        check_flags(argv[i]);
                        ++count;
                }
        }
        return (count);
}
