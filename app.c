#include <stdio.h>
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
    int     returnValue = 1;

    /* Usage:
     *   exename roman_number1 + roman_number2
     *   exename roman_number1 - roman_number2
     */

    if (argc == 4)
    {
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
                uppercase(roman_value1);

                strncpy(roman_value2, argv[3], ROMAN_MAX_STRING_LENGTH);
                roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';
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
    }

    if (returnValue != 0)
    {
        printf("Usage:\n");
        printf("  %s roman_number1 + roman_number2\n", argv[0]);
        printf("  %s roman_number1 - roman_number2\n", argv[0]);
        printf("Maximum Roman number is MMMCMXCIX. Addition cannot exceed this value, and\n");
        printf("subtraction cannot be such that the operation would produce a negative result.\n");
    }

    return returnValue;
}
