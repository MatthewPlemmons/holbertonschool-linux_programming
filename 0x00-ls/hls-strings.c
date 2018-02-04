#include "hls.h"

/**
 * _strcpy - copies a string to a buffer.
 *
 * @dest: buffer
 * @src: string to copy
 * Return: char pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
        int i = 0;

        while (src[i] != '\0')
        {
                dest[i] = src[i];
                i++;
        }
        dest[i] = '\0';
        return (dest);
}

/**
 * _strcat - concatenate two strings.
 *
 * @dest: string input
 * @src: string to concatenate to dest
 * Return: char pointer to resulting string dest.
 */
char *_strcat(char *dest, char *src)
{
        char *s;

        s = dest;
        while (*dest != '\0')
                dest++;

        while (*src != '\0')
                *dest++ = *src++;

        *dest = '\0';
        return (s);

}

/**
 * _strlen - find string length.
 *
 * @s: string
 * Return: int length in bytes.
 */
int _strlen(char *s)
{
        int i;

        i = 0;
        while (s[i])
                i++;
        return (i);
}
