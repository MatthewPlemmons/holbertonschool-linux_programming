#include "signals.h"

/**
 * main - Send a signal to a process.
 *
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, or EXIT_FAILURE otherwise.
 */
int main(int argc, char **argv)
{
	pid_t pid;

	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	pid = atoi(argv[1]);
	if (kill(pid, SIGINT) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
