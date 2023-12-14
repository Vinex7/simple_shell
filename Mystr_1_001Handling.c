#include <stddef.h>

/**
 * _strcat - Concatenates two strings.
 * @dest: Destination string.
 * @src: Source string to be appended.
 * Return: Pointer to the destination string.
 */
char *_strcat(char *dest, const char *src)
{
int i;
int j;


for (i = 0; dest[i] != '\0'; i++)
	;


for (j = 0; src[j] != '\0'; j++)
{
dest[i] = src[j];
i++;
}

dest[i] = '\0';
return (dest);
}

/**
 * _strcpy - Copies the contents of one string to another.
 * @dest: Destination string.
 * @src: Source string to be copied.
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest, char *src)
{
size_t a;

for (a = 0; src[a] != '\0'; a++)
{
dest[a] = src[a];
}

dest[a] = '\0';
return (dest);
}

/**
 * _strcmp - Compares two strings.
 * @s1: First string.
 * @s2: Second string.
 * Return:
 *   0 if the strings are equal.
 *   Positive value if s1 is greater than s2.
 *   Negative value if s1 is less than s2.
 */
int _strcmp(char *s1, char *s2)
{
int i;


for (i = 0; s1[i] == s2[i] && s1[i]; i++)
	;

if (s1[i] > s2[i])
return (1);
if (s1[i] < s2[i])
return (-1);

return (0);
}

/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @s: Input string.
 * @c: Character to locate.
 * Return: Pointer to the first occurrence of c in s, or NULL if not found.
 */
char *_strchr(char *s, char c)
{
unsigned int i = 0;

for (; *(s + i) != '\0'; i++)
if (*(s + i) == c)
return (s + i);

if (*(s + i) == c)
return (s + i);

return (NULL);
}

/**
 * _strspn - Calculates the length of the initial segment of a string
 * consisting of only characters from another string.
 * @s: Input string.
 * @accept: String containing characters to search for.
 * Return: Length of the initial segment of s that consists of characters
 * found in accept.
 */
int _strspn(char *s, char *accept)
{
int i, j, bool;


for (i = 0; *(s + i) != '\0'; i++)
{
bool = 1;


for (j = 0; *(accept + j) != '\0'; j++)
{
if (*(s + i) == *(accept + j))
{
bool = 0;
break;
}
}

if (bool == 1)
break;
}

return (i);
}
