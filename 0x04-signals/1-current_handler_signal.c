#include "signals.h"

/**
 * current_handler_signal - Get the handler for SIGINT.
 *
 */
void (*current_handler_signal(void))(int)
{
	void (*handler)(int);

	handler = signal(SIGINT, SIG_IGN);
	if (signal(SIGINT, handler) == SIG_ERR)
		return (NULL);
	return (handler);
}
