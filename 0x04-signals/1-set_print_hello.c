#include "signals.h"

/**
 * print_hello - Handle the SIGINT signal.
 *
 * @signum: integer value of the signal1
 */
void print_hello(int signum)
{
	signal(signum, SIG_IGN);
	printf("Hello :)\n");
	signal(signum, print_hello);
}

/**
 * set_print_hello - Handle received signal.
 *
 * Return: 0 on success, -1 on error.
 */
void set_print_hello(void)
{
	signal(SIGINT, print_hello);
}
