#include "shell.h"

/**
 * get_sigint - Signal handler function for handling the SIGINT (Ctrl+C).
 * @sig: The signal number.
 */
void get_sigint(int sig)
{
    (void)sig
    write(STDOUT_FILENO, "\n^-^ ", 5);
}
