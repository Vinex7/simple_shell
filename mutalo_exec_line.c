#include "shell.h"

/**
 * exec_line - Executes a command line in the shell.
 * @datash: Pointer to the data structure containing shell information.
 * Return: Returns the status of the executed command or built-in function.
 */
int exec_line(data_shell *datash)
{
int (*builtin)(data_shell *datash);

if (datash->args[0] == NULL)
return (1);

builtin = get_builtin(datash->args[0]);

if (builtin != NULL)
return (builtin(datash));

return (cmd_exec(datash));
}
