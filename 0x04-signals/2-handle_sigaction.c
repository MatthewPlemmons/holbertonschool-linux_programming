#include "signals.h"

/**
 * sigint_handler - Handle the SIGINT signal.
 *
 * @signum: integer value of the signal
 */
void sigint_handler(int signum)
{
	printf("Gotcha [%i]\n", signum);
	/*signal(signum, sigint_handler);*/
}

/**
 * handle_signal - Handle received signal.
 *
 * Return: 0 on success, -1 on error.
 */
int handle_sigaction(void)
{
	struct sigaction new_action;

	new_action.sa_handler = sigint_handler;

	if (sigaction(SIGINT, &new_action, NULL) < 0)
		return (-1);
	return (0);
}
