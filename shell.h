#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/**
 * struct data_shell - Data structure to hold shell information.
 * @av: Array of strings containing command-line arguments.
 * @input: Pointer to the input string.
 * @args: Array of strings containing command arguments.
 * @status: Exit status of the last command.
 * @counter: Counter for the number of commands executed.
 * @_environ: Array of strings containing the environment variables.
 * @pid: Process ID converted to string.
 */
typedef struct data_shell
{
char **av;
char *input;
char **args;
int status;
int counter;
char **_environ;
char *pid;
} data_shell;

/**
 * struct sep_list - Node structure for separating operators (;, |, &).
 * @separator: Separating operator.
 * @next: Pointer to the next separator node.
 */typedef struct sep_list_s
{
char separator;
struct sep_list_s *next;
} sep_list;

/**
 * struct line_list - Node structure for holding lines of commands.
 * @line: Pointer to a line of command.
 * @next: Pointer to the next line node.
 */typedef struct line_list_s
{
char *line;
struct line_list_s *next;
} line_list;

/**
 * struct r_var - Node structure for holding replaced variables.
 * @len_var: Length of the variable name.
 * @val: Value of the variable.
 * @len_val: Length of the variable value.
 * @next: Pointer to the next replaced variable node.
 */typedef struct r_var_list
{
int len_var;
char *val;
int len_val;
struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Structure for built-in commands.
 * @name: Name of the built-in command.
 * @f: Pointer to the corresponding function.
 */
typedef struct builtin_s
{
char *name;
int (*f)(data_shell *datash);
} builtin_t;


#endif
