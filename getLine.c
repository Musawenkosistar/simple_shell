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
ssize_t v = 0;
size_t len_p = 0;
if (!*len) 
{
/*bfree((void **)info->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
v = getline(buf, &len_p, stdin);
#else
v = _getline(info, buf, &len_p);
#endif
if (v > 0)
{
if ((*buf)[v - 1] == '\n')
{
(*buf)[v - 1] = '\0'; /* remove trailing newline */
v--;
}
info->linecount_flag = 1;
remove_comments(*buf);
build_history_list(info, *buf, info->histcount++);
/* if (_strchr(*buf, ';')) is this a command chain? */
{
*len = v;
info->cmd_buf = buf;
}
}
}
return (v);
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
static size_t x, f, len;
ssize_t v = 0;
char **buf_p = &(info->arg), *p;
_putchar(BUF_FLUSH);
v = input_buf(info, &buf, &len);
if (f == -1) 
return (-1);
if (len) 
{
f = x; 
p = buf + x; 
check_chain(info, buf, &f, x, len);
while (f < len) 
{
if (is_chain(info, buf, &f))
break;
f++;
}
x = f + 1; 
if (x >= len) 
{
x = len = 0;
info->cmd_buf_type = CMD_NORM;
}
*buf_p = p; 
return (_strlen(p)); 
}
*buf_p = buf; 
return (v); 
}
/**
* read_buf - reads a buffer
* @info: parameter struct
* @buf: buffer
* @i: size
*
* Return: v
*/
ssize_t read_buf(info_t *info, char *buf, size_t *x)
{
ssize_t v = 0;
if (*x)
return (0);
v = read(info->readfd, buf, READ_BUF_SIZE);
if (v >= 0)
*x = v;
return (v);
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
static size_t x, len;
size_t k;
ssize_t v = 0, y = 0;
char *p = NULL, *new_p = NULL, *c;
p = *ptr;
if (p && length)
y = *length;
if (x == len)
x = len = 0;
v = read_buf(info, buf, &len);
if (v == -1 || (v == 0 && len == 0))
return (-1);
c = _strchr(buf + v, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, y, y ? y + k : k + 1);
if (!new_p) 
return (p ? free(p), -1 : -1);
if (y)
_strncat(new_p, buf + x, k - x);
else
_strncpy(new_p, buf + x, k - x + 1);
y += k - x;
x = k;
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
