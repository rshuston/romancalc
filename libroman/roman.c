#include <stdio.h>

#include "roman.h"



static char *_digit2symbol(char *buff, unsigned digit, char max, char mid, char min);

static int _symbol2number(char symbol);



char *roman_name(void)
{
    return "roman";
}


/*
 * Converts an unsigned integer year to a roman string year
 *
 * Returns "C" logical true if successful, "C" logical false otherwise
 */

int number2roman(unsigned number, char *roman)
{
    int success = 0;

    if (number <= ROMAN_MAX_NUMBER_YEAR && roman != NULL)
    {
        char        *cp = roman;
        unsigned    ones = number % 10;
        unsigned    tens = (number / 10) % 10;
        unsigned    hundreds = (number / 100) % 10;
        unsigned    thousands = (number / 1000) % 10;
        int         n;

        for (n = 0; n < thousands; n++)
        {
            *cp++ = 'M';
        }

        cp = _digit2symbol(cp, hundreds, 'M', 'D', 'C');
        cp = _digit2symbol(cp, tens, 'C', 'L', 'X');
        cp = _digit2symbol(cp, ones, 'X', 'V', 'I');
        *cp = '\0';  /* Put an elephant in Cairo */

        success = !0;
    }

    return success;
}



static char *_digit2symbol(char *buff, unsigned digit, char decade, char half, char unit)
{
    char    *cp = buff;
    int     n;

    switch (digit) {
        case 9:
            *cp++ = unit;
            *cp++ = decade;
            break;
        case 8:
        case 7:
        case 6:
        case 5:
            *cp++ = half;
            for (n = 0; n < digit - 5; n++)
            {
                *cp++ = unit;
            }
            break;
        case 4:
            *cp++ = unit;
            *cp++ = half;
            break;
        case 3:
        case 2:
        case 1:
            for (n = 0; n < digit; n++)
            {
                *cp++ = unit;
            }
            break;
        default:
            break;
    }

    return cp;
}



/*
 * Converts a roman string year to an unsigned integer year
 *
 * Returns "C" logical true if successful, "C" logical false otherwise
 */

int roman2number(char *roman, unsigned *number)
{
    int success = 0;

    if (roman != NULL && number != NULL)
    {
        int         prevSymbolValue = 1000;  /* max possible value = M */
        int         symbolValue = 0;
        unsigned    numberValue = 0;
        char        *cp = roman;

        while (*cp)
        {
            symbolValue = _symbol2number(*cp++);
            numberValue += symbolValue;
            if (symbolValue > prevSymbolValue)
            {
                numberValue -= 2 * prevSymbolValue;
            }
            prevSymbolValue = symbolValue;
        }

        if (numberValue <= ROMAN_MAX_NUMBER_YEAR)
        {
            *number = numberValue;
            success = !0;
        }
    }

    return success;
}



static int _symbol2number(char symbol)
{
    int digit = 0;

    switch (symbol)
    {
        case 'I':
            digit = 1;
            break;
        case 'V':
            digit = 5;
            break;
        case 'X':
            digit = 10;
            break;
        case 'L':
            digit = 50;
            break;
        case 'C':
            digit = 100;
            break;
        case 'D':
            digit = 500;
            break;
        case 'M':
            digit = 1000;
            break;
        default:
            digit = 0;
            break;
    }

    return digit;
}
