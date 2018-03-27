#include "signals.h"

/**
 * sigint_handler - Print PID of signal sender.
 *
 * @sig: integer value of the signal
 * @info: struct containing more information on the signal
 * @ucontext: struct containing signal context information
 */
void sigquit_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig, (void) ucontext;
	printf("SIGQUIT sent by %i\n", info->si_pid);
}

/**
 * handle_sigaction - Handle received signal.
 *
 * Return: 0 on success, -1 on error.
 */
int trace_signal_sender(void)
{
	struct sigaction sa;

	sa.sa_sigaction = sigquit_handler;
	sa.sa_flags = SA_SIGINFO;

	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		return (-1);
	return (0);
}
