#include "shell.h"
/**
* is_cmd - Determines if a file is an workable command
* @info: the info struct
* @path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int is_cmd(info_t *info, char *path)
{
struct stat st;
(void)info;
if (!path || stat(path, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}
/**
* dup_chars - Copies characters
* @pathstr: the PATH string
* @start: starting index
* @stop: stopping index
*
* Return: Pointer to new buffer
*/
char *dup_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int f = 0, x = 0;
for (x = 0, f = start; f < stop; f++)
if (pathstr[f] != ':')
buf[x++] = pathstr[f];
buf[x] = 0;
return (buf);
}
/**
* find_path - finds this cmd in the PATH string
* @info: the info struct
* @pathstr: the PATH string
* @cmd: the cmd to find
*
* Return: full path of cmd if found or NULL
*/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int f = 0, curr_pos = 0;
char *path;
if (!pathstr)
return (NULL);
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_cmd(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[f] || pathstr[f] == ':')
{
path = dup_chars(pathstr, curr_pos, f);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_cmd(info, path))
return (path);
if (!pathstr[f])
break;
curr_pos = f;
}
f++;
}
return (NULL);
}
