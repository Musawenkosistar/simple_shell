#include "shell.h"
/**
**_strncpy - duplicates a string
*@dest: the destination string to be copied to
*@src: the source string
*@n: the amount of characters to be copied
*Return: the concatenated string
*/
char *_strncpy(char *dest, char *src, int n)
{
int f, t;
char *s = dest;
f = 0;
while (src[f] != '\0' && f < n - 1)
{
dest[f] = src[f];
f++;
}
if (f < n)
{
t = f;
while (t < n)
}
dest[t] = '\0';
t++;
}
}
return (s);
}
/**
**_strncat - focuses two strings
*@dest: the first string
*@src: the second string
*@n: the amount of bytes to be maximally used
*Return: the concatenated string
*/
char *_strncat(char *dest, char *src, int n)
{
int f, t;
char *s = dest;
f = 0;
t = 0;
while (dest[f] != '\0')
f++;
while (src[t] != '\0' && t < n)
{
dest[f] = src[t];
f++;
t++;
}
if (t < n)
dest[f] = '\0';
return (s);
}
/**
**_strchr - locates a character in a string
*@s: the string to be parsed
*@c: the character to look for
*Return: (s) a pointer to the memory area s
*/
char *_strchr(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');
return (NULL);
}
