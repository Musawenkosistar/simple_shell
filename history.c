#include "shell.h"

/**
* get_history_file - Gets the history file
* @info: parameter struct
*
* Return: allocated string containg history file
*/
char *get_history_file(info_t *info)
{
char *buf, *dir;
dir = _getenv(info, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);
return (buf);
}
/**
* write_history - Creates a file, or appends to an existing file
* @info: the parameter struct
*
* Return: 1 on success, else -1
*/
int write_history(info_t *info)
{
ssize_t td;
char *filename = get_history_file(info);
list_t *node = NULL;
if (!filename)
return (-1);
td = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (td == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
_putsfd(node->str, td);
_putfd('\n', td);
}
_putfd(BUF_FLUSH, td);
close(td);
return (1);
}
/**
* read_history - Reads history from file
* @info: the parameter struct
*
* Return: histcount on success, 0 otherwise
*/
int read_history(info_t *info)
{
int f, last = 0, linecount = 0;
ssize_t td, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = get_history_file(info);
if (!filename)
return (0);
td = open(filename, O_RDONLY);
free(filename);
if (td == -1)
return (0);
if (!fstat(td, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(td, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(td);
for (f = 0; f < fsize; f++)
if (buf[f] == '\n')
{
buf[f] = 0;
build_history_list(info, buf + last, linecount++);
last = f + 1;
}
if (last != f)
build_history_list(info, buf + last, linecount++);
free(buf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
delete_node_at_index(&(info->history), 0);
renumber_history(info);
return (info->histcount);
}
/**
* build_history_list - Adds entry to a history linked list
* @info: Structure containing potential arguments. Used to maintain
* @buf: buffer
* @linecount: the history linecount, histcount
*
* Return: Always 0
*/
int build_history_list(info_t *info, char *buf, int linecount)
{
list_t *node = NULL;
if (info->history)
node = info->history;
add_node_end(&node, buf, linecount);
if (!info->history)
info->history = node;
return (0);
}
/**
* renumber_history - Renumbers the history linked list after changes
* @info: Structure containing potential arguments. Used to maintain
*
* Return: the new histcount
*/
int renumber_history(info_t *info)
{
list_t *node = info->history;
int f = 0;
while (node)
{
node->num = f++;
node = node->next;
}
return (info->histcount = f);
}

