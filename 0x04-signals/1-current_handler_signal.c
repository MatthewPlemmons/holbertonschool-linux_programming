#include "signals.h"

/**
 * current_handler_signal - Get the handler for SIGINT.
 *
 *
 */
void (*current_handler_signal(void))(int)
{
	typedef void (*sighandler_t)(int);
	sighandler_t handler;

	handler = signal(SIGINT, SIG_IGN);
	signal(SIGINT, handler);
	return (handler);
}
