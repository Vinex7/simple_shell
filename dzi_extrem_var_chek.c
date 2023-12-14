#include "shell.h"

/**
 * check_env - Checks for environment variables.
 * @h: Pointer to the head of the r_var linked list.
 * @in: Input string to check for environment variables.
 * @data: Pointer to the data_shell structure.
 * Return: Void.
 */
void check_env(r_var **h, char *in, data_shell *data)
{
int row, chr, j, lval;
char **_envr;

_envr = data->_environ;
for (row = 0; _envr[row]; row++)
{
for (j = 1, chr = 0; _envr[row][chr]; chr++)
{
if (_envr[row][chr] == '=')
{
lval = _strlen(_envr[row] + chr + 1);
add_rvar_node(h, j, _envr[row] + chr + 1, lval);
return;
}

if (in[j] == _envr[row][chr])
j++;
else
break;
}
}

for (j = 0; in[j]; j++)
{
if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
break;
}

add_rvar_node(h, j, NULL, 0);
}

/**
 * check_vars - Checks for special variables (e.g., $? and $$).
 * @h: Pointer to the head of the r_var linked list.
 * @in: Input string to check for special variables.
 * @st: The string representation of the status variable.
 * @data: Pointer to the data_shell structure.
 * Return: The number of characters checked.
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
int i, lst, lpd;

lst = _strlen(st);
lpd = _strlen(data->pid);

for (i = 0; in[i]; i++)
{
if (in[i] == '$')
{
if (in[i + 1] == '?')
add_rvar_node(h, 2, st, lst), i++;
else if (in[i + 1] == '$')
add_rvar_node(h, 2, data->pid, lpd), i++;
else if (in[i + 1] == '\n' || in[i + 1] == '\0'
|| in[i + 1] == ' ' || in[i + 1] == '\t' || in[i + 1] == ';')
add_rvar_node(h, 0, NULL, 0);
else
check_env(h, in + i, data);
}
}

return (i);
}

/**
 * replaced_input - Replaces variables in the input string.
 * @head: Pointer to the head of the r_var linked list.
 * @input: Input string to replace variables.
 * @new_input: Buffer to store the replaced input string.
 * @nlen: Length of the new_input buffer.
 * Return: The replaced input string.
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
r_var *indx;
int i, j, k;

indx = *head;
for (j = i = 0; i < nlen; i++)
{
if (input[j] == '$')
{
if (!(indx->len_var) && !(indx->len_val))
{
new_input[i] = input[j];
j++;
}
else if (indx->len_var && !(indx->len_val))
{
for (k = 0; k < indx->len_var; k++)
j++;
i--;
}
else
{
for (k = 0; k < indx->len_val; k++)
{
new_input[i] = indx->val[k];
i++;
}
j += (indx->len_var);
i--;
}
indx = indx->next;
}
else
{
new_input[i] = input[j];
j++;
}
}

return (new_input);
}

/**
 * rep_var - Replaces variables in the input string.
 * @input: Input string to replace variables.
 * @datash: Pointer to the data_shell structure.
 * Return: The replaced input string.
 */
char *rep_var(char *input, data_shell *datash)
{
r_var *head, *indx;
char *status, *new_input;
int olen, nlen;

status = aux_itoa(datash->status);
head = NULL;

olen = check_vars(&head, input, status, datash);

if (head == NULL)
{
free(status);
return (input);
}

indx = head;
nlen = 0;
while (indx != NULL)
{
nlen += (indx->len_val - indx->len_var);
indx = indx->next;
}

nlen += olen;

new_input = malloc(sizeof(char) * (nlen + 1));
new_input[nlen] = '\0';

new_input = replaced_input(&head, input, new_input, nlen);

free(input);
free(status);
free_rvar_list(&head);

return (new_input);
}
