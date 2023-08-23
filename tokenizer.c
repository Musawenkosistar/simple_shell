#include "shell.h"

/**
* **strtow - Splits a string into words. Repeat delimiters are ignored
* @str: the input string
* @d: the delimeter string
* Return: A pointer to an array of strings, or NULL on failure
*/
char **strtow(char *str, char *d)
{
int f, t, x, n, numwords = 0;
char **s;
if (str == NULL || str[0] == 0)
return (NULL);
if (!d)
d = " ";
for (f = 0; str[f] != '\0'; f++)
if (!is_delim(str[f], d) && (is_delim(str[f + 1], d) || !str[f + 1]))
numwords++;
if (numwords == 0)
return (NULL);
s = malloc((1 + numwords) * sizeof(char *));
if (!s)
return (NULL);
for (f = 0, t = 0; t < numwords; t++)
{
while (is_delim(str[f], d))
f++;
x = 0;
while (!is_delim(str[f + x], d) && str[f + x])
x++;
s[t] = malloc((x + 1) * sizeof(char));
if (!s[t])
{
for (x = 0; x < t; x++)
free(s[x]);
free(s);
return (NULL);
}
for (n = 0; n < x; n++)
s[t][n] = str[f++];
s[t][n] = 0;
}
s[t] = NULL;
return (s);
}
/**
* **strtow2 - Splits a string into words
* @str: the input string
* @d: the delimeter
* Return: A pointer to an array of strings, or NULL on failure
*/
char **strtow2(char *str, char d)
{
	int i, x, t, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (f = 0; str[f] != '\0'; f++)
		if ((str[f] != d && str[f + 1] == d) ||
		    (str[f] != d && !str[f + 1]) || str[f + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (f = 0, t = 0; t < numwords; t++)
	{
		while (str[f] == d && str[f] != d)
			f++;
		x = 0;
		while (str[f + x] != d && str[f + x] && str[f + x] != d)
			x++;
		s[t] = malloc((x + 1) * sizeof(char));
		if (!s[t])
		{
			for (x = 0; x < t; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < x; n++)
			s[t][n] = str[f++];
		s[t][n] = 0;
	}
	s[t] = NULL;
	return (s);
}
