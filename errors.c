#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int f = 0;

	if (!str)
		return;
	while (str[f] != '\0')
	{
		_eputchar(str[f]);
	    f++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int f;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || f >= WRITE_BUF_SIZE)
	{
		write(2, buf, f);
		f = 0;
	}
	if (c != BUF_FLUSH)
		buf[f++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int f;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || f >= WRITE_BUF_SIZE)
	{
		write(fd, buf, f);
		f = 0;
	}
	if (c != BUF_FLUSH)
		buf[f++] = c;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int f = 0;

	if (!str)
		return (0);
	while (*str)
	{
		f += _putfd(*str++, fd);
	}
	return (f);
}
