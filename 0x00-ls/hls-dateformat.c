#include "hls.h"

#define DATE_STRING_MAX 64

/**
 * date_format - reformat the string output from `ctime()`.
 *
 * @time: string that was output by the `ctime()` function
 * Return: altered `time` string.
 */
char *date_format(char *time)
{
	char *date, *fmt_date;
	size_t n;

	date = _calloc(sizeof(char), DATE_STRING_MAX);
	_strcpy(date, time + 4);

	n = _strlen(date);
	_strcpy(date + (n - 1), "\0");

	fmt_date = _calloc(sizeof(char), DATE_STRING_MAX);
	_strcpy(fmt_date, date);
	free(date);
	return (fmt_date);
}
