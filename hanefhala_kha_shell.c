#include "shell.h"

/**
 * exit_shell - Handles the "exit" command in the shell.
 * @datash: The shell data structure.
 * Return: 0 if no argument is provided or the argument is a valid exit status,
 * 1 if there is an error in the exit status argument.
 */
int exit_shell(data_shell *datash)
{
unsigned int ustatus;
int is_digit;
int str_len;
int big_number;

if (datash->args[1] != NULL)
{
ustatus = _atoi(datash->args[1]);

is_digit = _isdigit(datash->args[1]);

str_len = _strlen(datash->args[1]);

big_number = ustatus > (unsigned int)INT_MAX;

if (!is_digit || str_len > 10 || big_number)
{
get_error(datash, 2);

datash->status = 2;

return (1);
}

datash->status = (ustatus % 256);
}

return (0);
}
