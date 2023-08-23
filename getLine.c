#include "shell.h"

/**
* input_buf - buffers chained commands
* @info: parameter struct
* @buf: address of buffer
* @len: address of len var
*
* Return: bytes read
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t len_p = 0;

	if (!*len) 
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		x = getline(buf, &len_p, stdin);
#else
		x = _getline(info, buf, &len_p);
#endif
		if (x > 0)
		{
			if ((*buf)[x - 1] == '\n')
			{
				(*buf)[x - 1] = '\0'; 
				x--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = x;
				info->cmd_buf = buf;
			}
		}
	}
	return (x);
}
/**
* get_input - gets a line minus the newline
* @info: parameter struct
*
* Return: bytes read
*/
ssize_t get_input(info_t *info)
{
	static char *buf; 
	static size_t f, j, len;
	ssize_t x = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	x = input_buf(info, &buf, &len);
	if (x == -1) /* EOF */
		return (-1);
	if (len)	
	{
		j = f; 
		p = buf + f;

		check_chain(info, buf, &j, f, len);
		while (j < len) 
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		f = j + 1; 
		if (f >= len) 
		{
			f = len = 0; 
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; 
		return (_strlen(p)); 
	}

	*buf_p = buf; 
	return (x); 
}

/**
* read_buf - reads a buffer
* @info: parameter struct
* @buf: buffer
* @i: size
*
* Return: x
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t x = 0;

	if (*i)
		return (0);
	x = read(info->readfd, buf, READ_BUF_SIZE);
	if (x >= 0)
		*i = x;
	return (x);
}
/**
* _getline - gets the next line of input from STDIN
* @info: parameter struct
* @ptr: address of pointer to buffer, preallocated or NULL
* @length: size of preallocated ptr buffer if not NULL
*
* Return: y
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t f, len;
	size_t v;
	ssize_t x = 0, y = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		y = *length;
	if (f == len)
		f = len = 0;

	x = read_buf(info, buf, &len);
	if (x == -1 || (x == 0 && len == 0))
		return (-1);

	c = _strchr(buf + f, '\n');
	v = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, y, y ? y + v : v + 1);
	if (!new_p) 
		return (p ? free(p), -1 : -1);

	if (y)
		_strncat(new_p, buf + f, v - f);
	else
		_strncpy(new_p, buf + f, v - f + 1);

	y += v - f;
	f = v;
	p = new_p;

	if (length)
		*length = y;
	*ptr = p;
	return (y);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
