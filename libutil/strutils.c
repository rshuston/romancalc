#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "strutils.h"



char *strutils_name(void)
{
    return "strutils";
}



/*
 * Trim the leading and trailing whitespace from a string
 *
 * Returns pointer to the trimed string
 *
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
 *
 * Returns pointer to the lowercase string
 *
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
 *
 * Returns pointer to the uppercase string
 *
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



/*
 * Test if a string consists of only chars in a given character set
 *
 * Returns "C" logical true if successful, "C" logical false otherwise
 */

int strConsistsOfCharSet(char *s, char *charSet)
{
    int success = 0;

    if (s != NULL && charSet != NULL)
    {
        if ( strlen(s) && strlen(charSet) )
        {
            char *strChr;

            success = !0;  /* "C" logical true */

            strChr = s;
            while (*strChr)
            {
                char *setChr;
                int found;

                found = 0;
                setChr = charSet;
                while (*setChr)
                {
                    if (*setChr++ == *strChr)
                    {
                        found = 1;
                        break;
                    }
                }

                if (!found)
                {
                    success = 0;
                    break;
                }

                strChr++;
            }
        }
    }

    return success;
}
