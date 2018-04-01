#include "signals.h"

/**
 * sigint_handler - Handle the SIGINT signal.
 *
 * @signum: integer value of the signal
 */
void sigint_handler(int signum)
{
	printf("Caught %i\n", signum);
}

/**
 * set_sigint_handler - Set signal handler for SIGINT.
 *
 */
void set_sigint_handler(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);
}

/**
 * main - Waits for a signal to be received.
 *
 */
int main(void)
{
	struct sigaction sa;

	set_sigint_handler();
       	pause();

	if (sigaction(SIGINT, NULL, &sa) == -1)
		exit(EXIT_FAILURE);
	else
	{
		printf("Signal received\n");
		exit(EXIT_SUCCESS);
	}
}
