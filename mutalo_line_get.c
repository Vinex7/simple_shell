#include "shell.h"

/**
 * bring_line - Updates the lineptr and n based on the input buffer.
 * @lineptr: Pointer to the pointer storing the input line.
 * @n: Pointer to the size of the input buffer.
 * @buffer: Buffer containing the input line.
 * @j: Size of the input line.
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{
if (*lineptr == NULL)
{
if (j > BUFSIZE
else
*n = BUFSIZE;
*lineptr = buffer;
}
else if (*n < j)
{
if (j > BUFSIZE)
*n = j;
else
*n = BUFSIZE;
*lineptr = buffer;
}
else
{
_strcpy(*lineptr, buffer);
free(buffer);
}
}

/**
 * get_line - Reads a line from the given stream (usually STDIN).
 * @lineptr: Pointer to the pointer that will store the input line.
 * @n: Pointer to the size of the input buffer.
 * @stream: File stream from which to read the input line.
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
int i;
static ssize_t input;
ssize_t retval;
char *buffer;
char t = 'z';

if (input == 0)
fflush(stream);
else
return (-1);
input = 0;

buffer = malloc(sizeof(char) * BUFSIZE);
if (buffer == 0)
return (-1);

while (t != '\n')
{
i = read(STDIN_FILENO, &t, 1);
if (i == -1 || (i == 0 && input == 0))
{
free(buffer);
return (-1);
}
if (i == 0 && input != 0)
{
input++;
break;
}
if (input >= BUFSIZE)
buffer = _realloc(buffer, input, input + 1);
buffer[input] = t;
input++;
}

buffer[input] = '\0';
bring_line(lineptr, n, buffer, input);
retval = input;

if (i != 0)
input = 0;

return (retval);
}
