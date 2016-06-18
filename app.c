#include <stdio.h>

#include "app.h"
#include "roman.h"
#include "strutils.h"

char *app_name(void)
{
    return "app";
}

int app_exec(int argc, char *argv[])
{
    printf("app_exec()\n");

    printf("...%s\n", roman_name());
    printf("...%s\n", strutils_name());

    return 1;
}
