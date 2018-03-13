#include "signals.h"

/**
 * sigint_handler - Handle the SIGINT signal.
 *
 * @signum: integer value of the signal1
 */
void sigint_handler(int signum)
{
	signal(signum, SIG_IGN);
	printf("Gotcha [%i]\n", signum);
	signal(signum, sigint_handler);
}

/**
 * handle_signal - Handle received signal.
 *
 * Return: 0 on success, -1 on error.
 */
int handle_signal(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		return (-1);
	return (0);
}
