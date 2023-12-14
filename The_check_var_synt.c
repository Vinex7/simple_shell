#include "shell.h"
/**
 * repeated_char - Count the number of repeated characters.
 * @input: Input string.
 * @i: Counter for repeated characters.
 * Return: Number of repeated characters.
 */
int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - Check for syntax errors related to separators.
 * @input: Input string.
 * @i: Current position in the input string.
 * @last: Last encountered separator.
 * Return: Position of the syntax error, if any.
 */
int error_sep_op(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - Find the position of the first non-whitespace character.
 * @input: Input string.
 * @i: Pointer to the position variable.
 * Return: 0 if a non-whitespace character is found, -1 otherwise.
 */
int first_char(char *input, int *i)
{
	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - Print a syntax error message to STDERR.
 * @datash: Pointer to the data_shell structure.
 * @input: Input string.
 * @i: Position of the syntax error.
 * @bool: Flag indicating the type of syntax error.
 * Return: No return value.
 */
void print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\"unexpected\n";
	counter = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
if (error == 0)
	;
{
free(counter);
return;
}
_strcpy(error, datash->av[0]);
_strcat(error, ": ");
_strcat(error, counter);
_strcat(error, msg2);
_strcat(error, msg);
_strcat(error, msg3);
_strcat(error, "\0");

write(STDERR_FILENO, error, length);
free(error);
free(counter);
}

/**
 * check_syntax_error - Check for syntax errors in the input string.
 * @datash: Pointer to the data_shell structure.
 * @input: Input string.
 * Return: 0 if no syntax errors are found, 1 otherwise.
 */
int check_syntax_error(data_shell *datash, char *input)
{
int begin = 0;
int f_char = 0;
int i = 0;

f_char = first_char(input, &begin);
if (f_char == -1)
{
print_syntax_error(datash, input, begin, 0);
return (1);
}

i = error_sep_op(input + begin, 0, *(input + begin));
if (i != 0)
{
print_syntax_error(datash, input, begin + i, 1);
return (1);
}

return (0);
}
