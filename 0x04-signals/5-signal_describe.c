#include "signals.h"

/**
 * main - Prints a signal description.
 *
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, or EXIT_FAILURE otherwise.
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
