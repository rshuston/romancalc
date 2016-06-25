#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"
#include "roman.h"
#include "strutils.h"

char *app_name(void)
{
    return "app";
}

int app_exec(int argc, char *argv[])
{

    int returnValue = 1;  /* 0 = success */

    /* Usage:
     *   exename decimal_number
     *   exename roman_number
     *   exename roman_number1 + roman_number2
     *   exename roman_number1 - roman_number2
     */

    switch (argc)
    {
        case 2:
            if ( strConsistsOfCharSet(argv[1], "mMdDcClLxXvViI") )
            {
                char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
                unsigned    decimal_value;

                strncpy(roman_value, argv[1], ROMAN_MAX_STRING_LENGTH);
                roman_value[ROMAN_MAX_STRING_LENGTH] = '\0';
                trim(roman_value);
                uppercase(roman_value);

                if ( roman2number(roman_value, &decimal_value) )
                {
                    returnValue = 0;
                    printf("%s => %u\n", roman_value, decimal_value);
                }
            }
            else if ( strConsistsOfCharSet(argv[1], "0123456789") )
            {
                if ( strlen(argv[1]) <= 4 )
                {
                    int     decimal_value;
                    char    roman_value[ROMAN_MAX_STRING_LENGTH + 1];

                    decimal_value = atoi(argv[1]);

                    if (decimal_value > 0)
                    {
                        if ( number2roman((unsigned)decimal_value, roman_value) )
                        {
                            returnValue = 0;
                            printf("%d => %s\n", decimal_value, roman_value);
                        }
                    }
                }
            }
            break;
        case 4:
            if ( strlen(argv[1]) <= ROMAN_MAX_STRING_LENGTH && strlen(argv[2]) == 1 && strlen(argv[3]) <= ROMAN_MAX_STRING_LENGTH )
            {
                char operation = *argv[2];

                if (operation == '+' || operation == '-')
                {
                    char    roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
                    char    roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
                    char    roman_value3[ROMAN_MAX_STRING_LENGTH + 1];
                    int     success;

                    strncpy(roman_value1, argv[1], ROMAN_MAX_STRING_LENGTH);
                    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';
                    trim(roman_value1);
                    uppercase(roman_value1);

                    strncpy(roman_value2, argv[3], ROMAN_MAX_STRING_LENGTH);
                    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';
                    trim(roman_value2);
                    uppercase(roman_value2);

                    if (operation == '+')
                    {
                        success = romanAdd(roman_value1, roman_value2, roman_value3);
                    }
                    else
                    {
                        success = romanSub(roman_value1, roman_value2, roman_value3);
                    }
                    if (success)
                    {
                        returnValue = 0;
                        printf("%s %c %s = %s\n", roman_value1, operation, roman_value2, roman_value3);
                    }
                }
            }
            break;
        default:
            break;
    }

    if (returnValue != 0)
    {
        printf("Usage:\n");
        printf("  %s decimal_number\n", argv[0]);
        printf("  %s roman_number\n", argv[0]);
        printf("  %s roman_number1 + roman_number2\n", argv[0]);
        printf("  %s roman_number1 - roman_number2\n", argv[0]);
        printf("Maximum Roman number is MMMCMXCIX (3999). Addition cannot exceed this value,\n");
        printf("and subtraction cannot be such that the operation would produce a negative.\n");
        printf("result.\n");
    }

    return returnValue;
}
