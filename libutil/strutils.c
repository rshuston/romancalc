#include <ctype.h>
#include <stdio.h>

#include "strutils.h"



char *strutils_name(void)
{
    return "strutils";
}



/*
 * Trim the leading and trailing whitespace from a string
 * Note: The original string is modified
 */

char *trim(char *s)
{
    char    *front = NULL;

    if (s != NULL)
    {
        char    *blank = NULL;
        char    *cp;

        for (cp = s; *cp; cp++)
        {
            if ( isspace(*cp) )
            {
                if (blank == NULL)
                {
                    blank = cp;
                }
            }
            else
            {
                blank = NULL;
                if (front == NULL)
                {
                    front = cp;
                }
            }
        }

        if (blank)
        {
            *blank = '\0';
        }

        if (front == NULL)
        {
            front = s;
        }
    }

    return front;
}



/*
 * Convert a string to lowercase
 * Note: The original string is modified
 */

char *lowercase(char *s)
{
    if (s != NULL)
    {
        char *cp = s;

        while (*cp)
        {
            *cp = tolower(*cp);
            cp++;
        }
    }
    return s;
}



/*
 * Convert a string to uppercase
 * Note: The original string is modified
 */

char *uppercase(char *s)
{
    if (s != NULL)
    {
        char *cp = s;

        while (*cp)
        {
            *cp = toupper(*cp);
            cp++;
        }
    }
    return s;
}
