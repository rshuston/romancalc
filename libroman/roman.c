#include <stdio.h>
#include <string.h>

#include "roman.h"



/*
 * Symbol set tables used for converting roman values to numbers
 */

#define NUM_ROMAN_DECADES           4
#define NUM_ROMAN_DECADE_SYMBOLS    9

static char *_RomanSymbolSets[NUM_ROMAN_DECADES][NUM_ROMAN_DECADE_SYMBOLS] =
{
  /*   9     8       7      6     5    4     3      2     1  */
    { "",   "",     "",    "",   "",  "",   "MMM", "MM", "M" }, /* 1000's */
    { "CM", "DCCC", "DCC", "DC", "D", "CD", "CCC", "CC", "C" }, /* 100's */
    { "XC", "LXXX", "LXX", "LX", "L", "XL", "XXX", "XX", "X" }, /* 10's */
    { "IX", "VIII", "VII", "VI", "V", "IV", "III", "II", "I" }  /* 1's */
};



static char *_digit2symbol(char *buff, unsigned digit, char max, char mid, char min);

static int _canGetDecadeDigit(char *roman, char *decadeCharSet);
static int _getDecadeDigit(char *roman, char *matchSet[], int matchSetSize, unsigned *digitValue);



char *roman_name(void)
{
    return "roman";
}



/*
 * Converts an unsigned integer value to a roman string value
 *
 * Returns "C" logical true if successful, "C" logical false otherwise
 */

int number2roman(unsigned number, char *roman)
{
    int success = 0;

    if (number <= ROMAN_MAX_NUMBER && roman != NULL)
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



/* Private function to convert numerical digit to roman symbol */
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
 * Converts a roman string value to an unsigned integer value
 *
 * Returns "C" logical true if successful, "C" logical false otherwise
 */

int roman2number(char *roman, unsigned *number)
{
    int success = 0;

    if (roman != NULL && number != NULL)
    {
        int         invalidSequence = 0;
        char        *cp = roman;
        unsigned    numberValue = 0;
        int         index;

        for (index = 0; index < NUM_ROMAN_DECADES; index++)
        {
            int     decade;
            char    *validDecadeCharSet;
            char    *invalidDecadeCharSet;
            char    **matchSet;

            switch (index)
            {
                case 0:
                    decade = 1000;
                    validDecadeCharSet = "M";
                    invalidDecadeCharSet = "";
                    break;
                case 1:
                    decade = 100;
                    validDecadeCharSet = "CD";
                    invalidDecadeCharSet = "M";
                    break;
                case 2:
                    decade = 10;
                    validDecadeCharSet = "XL";
                    invalidDecadeCharSet = "MCD";
                    break;
                default:
                    decade = 1;
                    validDecadeCharSet = "IV";
                    invalidDecadeCharSet = "MCDXL";
                    break;
            }
            matchSet = _RomanSymbolSets[index];
            if ( _canGetDecadeDigit(cp, validDecadeCharSet) )
            {
                unsigned digitValue;

                int matchWidth = _getDecadeDigit(cp, matchSet, NUM_ROMAN_DECADE_SYMBOLS, &digitValue);
                if (matchWidth)
                {
                    numberValue += digitValue * decade;
                    cp += matchWidth;
                }
                else
                {
                    /* If we get here, it's because the rest of the digit sequence is invalid */
                    invalidSequence = 1;
                    break;
                }
            }
            else if ( _canGetDecadeDigit(cp, invalidDecadeCharSet) )
            {
                /* Should not be able to decode from other decades */
                invalidSequence = 1;
                break;
            }
        }

        if (*cp)
        {
            /* Not all of the string was parsed! */
            invalidSequence = 1;
        }

        if (!invalidSequence && numberValue <= ROMAN_MAX_NUMBER)
        {
            *number = numberValue;
            success = !0;
        }
    }

    return success;
}



/* Private function to see if beginning of a roman value can be decoded for the given decade set */
static int _canGetDecadeDigit(char *roman, char *decadeCharSet)
{
    int canDo = 0;
    char *cp = decadeCharSet;

    while (*cp)
    {
        if (*cp++ == *roman)
        {
            canDo = 1;
            break;
        }
    }

    return canDo;
}



/* Private function to decode the decade digit of a roman value for a given match set */
static int _getDecadeDigit(char *roman, char *matchSet[], int matchSetSize, unsigned *digitValue)
{
    int matchWidth = 0;
    int index;

    for (index = 0; index < matchSetSize; index++)
    {
        if ( *matchSet[index] != '\0' )
        {
            char *foundPtr;

            foundPtr = strstr(roman, matchSet[index]);
            if (foundPtr == roman)
            {
                matchWidth = strlen(matchSet[index]);
                *digitValue = matchSetSize - index;
                break;
            }
        }
    }

    return matchWidth;
}



/*
 * Adds two roman string value values
 *
 * augend + addend = sum
 */

int romanAdd(char *augend, char *addend, char *sum)
{
    int success = 0;

    if (augend != NULL && addend != NULL && sum != NULL)
    {
        unsigned    augendValue;
        unsigned    addendValue;

        if ( roman2number(augend, &augendValue) && roman2number(addend, &addendValue) )
        {
            unsigned    sumValue;

            sumValue = augendValue + addendValue;
            if (sumValue <= ROMAN_MAX_NUMBER)
            {
                if ( number2roman(sumValue, sum) )
                {
                    success = !0;
                }
            }
        }
    }

    return success;
}


/*
 * Subtracts two roman string value values
 *
 * minuend - subtrahend = difference
 */

int romanSub(char *minuend, char *subrahend, char *difference)
{
    int success = 0;

    if (minuend != NULL && subrahend != NULL && difference != NULL)
    {
        unsigned    minuendValue;
        unsigned    subtrahendValue;

        if ( roman2number(minuend, &minuendValue) && roman2number(subrahend, &subtrahendValue) )
        {
            if (minuendValue >= subtrahendValue)
            {
                unsigned    differenceValue;

                differenceValue = minuendValue - subtrahendValue;
                if (differenceValue <= ROMAN_MAX_NUMBER)  /* should never really be false */
                {
                    if ( number2roman(differenceValue, difference) )
                    {
                        success = !0;
                    }
                }
            }
        }
    }

    return success;
}
