#include "signals.h"

/**
 * main - Prints a signal description.
 *
 * @argc: argument count
 * @argv: argument vector
 */
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	printf("%s: %s\n", argv[1], strsignal(atoi(argv[1])));
	return (EXIT_SUCCESS);
}
