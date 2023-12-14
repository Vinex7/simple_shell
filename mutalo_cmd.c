#include "shell.h"

/**
 * read_line - Reads a line from the standard input.
 * @i_eof: Pointer to an integer variable to store the getline return value.
 * It is set to -1 if an error occurs, 0 if EOF is reached, and
 * the number of characters read (including newline) otherwise.
 * Return:pointer to the dynamically allocated buffer containing input line.
 * It needs to be freed by the caller using free() when no longer needed.
 */
char *read_line(int *i_eof)
{
char *input = NULL;
size_t bufsize = 0;
*i_eof = getline(&input, &bufsize, stdin);

return (input);
}
