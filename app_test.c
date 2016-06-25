#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "app.h"
#include "roman.h"

/* ===== app_name() ========================================================= */

START_TEST (test_app_returns_name)
{
    char *name;

    name = app_name();
    ck_assert_str_eq(name, "app");
}
END_TEST

/* ===== app_exec() ========================================================= */

START_TEST (test_app_exec_succeeds_for_conversion_of_good_decimal_number)
{
    char    *exename;
    char    *decimal_value;
    char    *argv[2];
    int     returnValue;

    exename = "app.exe";
    decimal_value = "1984";

    argv[0] = exename;
    argv[1] = decimal_value;

    returnValue = app_exec(2, argv);  /* 0 = success */

    ck_assert_int_eq(returnValue, 0);
}
END_TEST

START_TEST (test_app_exec_fails_conversion_of_bad_decimal_number_1)
{
    char    *exename;
    char    *decimal_value;
    char    *argv[2];
    int     returnValue;

    exename = "app.exe";
    decimal_value = "-1";

    argv[0] = exename;
    argv[1] = decimal_value;

    returnValue = app_exec(2, argv);  /* 0 = success */

    ck_assert_int_ne(returnValue, 0);
}
END_TEST

START_TEST (test_app_exec_fails_conversion_of_bad_decimal_number_2)
{
    char    *exename;
    char    decimal_value[8];
    char    *argv[2];
    int     returnValue;

    exename = "app.exe";
    sprintf(decimal_value, "%d", ROMAN_MAX_NUMBER + 1);

    argv[0] = exename;
    argv[1] = decimal_value;

    returnValue = app_exec(2, argv);  /* 0 = success */

    ck_assert_int_ne(returnValue, 0);
}
END_TEST

START_TEST (test_app_exec_succeeds_for_conversion_of_good_roman_number)
{
    char    *exename;
    char    *roman_value;
    char    *argv[2];
    int     returnValue;

    exename = "app.exe";
    roman_value = "MCMLXXXIV";

    argv[0] = exename;
    argv[1] = roman_value;

    returnValue = app_exec(2, argv);  /* 0 = success */

    ck_assert_int_eq(returnValue, 0);
}
END_TEST

START_TEST (test_app_exec_fails_conversion_of_bad_roman_number_1)
{
    char    *exename;
    char    *roman_value;
    char    *argv[2];
    int     returnValue;

    exename = "app.exe";
    roman_value = "MMMMCMXCIX";

    argv[0] = exename;
    argv[1] = roman_value;

    returnValue = app_exec(2, argv);  /* 0 = success */

    ck_assert_int_ne(returnValue, 0);
}
END_TEST

START_TEST (test_app_exec_fails_conversion_of_bad_roman_number_2)
{
    char    *exename;
    char    *roman_value;
    char    *argv[2];
    int     returnValue;

    exename = "app.exe";
    roman_value = "XVX";

    argv[0] = exename;
    argv[1] = roman_value;

    returnValue = app_exec(2, argv);  /* 0 = success */

    ck_assert_int_ne(returnValue, 0);
}
END_TEST

START_TEST (test_app_exec_succeeds_for_addition)
{
    char    *exename;
    char    *operation;
    char    roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
    char    roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
    char    *argv[4];
    int     returnValue;

    exename = "app.exe";
    operation = "+";
    strncpy(roman_value1, "xiv", ROMAN_MAX_STRING_LENGTH);
    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';
    strncpy(roman_value2, "lx", ROMAN_MAX_STRING_LENGTH);
    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';

    argv[0] = exename;
    argv[1] = roman_value1;
    argv[2] = operation;
    argv[3] = roman_value2;

    returnValue = app_exec(4, argv);  /* 0 = success */

    ck_assert_int_eq(returnValue, 0);
}
END_TEST

START_TEST (test_app_exec_succeeds_for_subtraction)
{
    char    *exename;
    char    *operation;
    char    roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
    char    roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
    char    *argv[4];
    int     returnValue;

    exename = "app.exe";
    operation = "-";
    strncpy(roman_value1, "lxxiv", ROMAN_MAX_STRING_LENGTH);
    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';
    strncpy(roman_value2, "lx", ROMAN_MAX_STRING_LENGTH);
    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';

    argv[0] = exename;
    argv[1] = roman_value1;
    argv[2] = operation;
    argv[3] = roman_value2;

    returnValue = app_exec(4, argv);  /* 0 = success */

    ck_assert_int_eq(returnValue, 0);
}
END_TEST

START_TEST (test_app_exec_does_not_succeed)
{
    char    *exename;
    char    *operation;
    char    roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
    char    roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
    char    *argv[4];
    int     returnValue;

    exename = "app.exe";
    operation = "+";
    strncpy(roman_value1, "xiv", ROMAN_MAX_STRING_LENGTH);
    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';
    strncpy(roman_value2, "lx", ROMAN_MAX_STRING_LENGTH);
    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';

    argv[0] = exename;
    argv[1] = roman_value1;
    argv[2] = operation;
    argv[3] = roman_value2;

    returnValue = app_exec(3, argv);  /* 0 = success */

    ck_assert_int_ne(returnValue, 0);
}
END_TEST

/* ===== Test Suite ========================================================= */

Suite * test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("app test suite");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_app_returns_name);

    tcase_add_test(tc_core, test_app_exec_succeeds_for_conversion_of_good_decimal_number);
    tcase_add_test(tc_core, test_app_exec_fails_conversion_of_bad_decimal_number_1);
    tcase_add_test(tc_core, test_app_exec_fails_conversion_of_bad_decimal_number_2);

    tcase_add_test(tc_core, test_app_exec_succeeds_for_conversion_of_good_roman_number);
    tcase_add_test(tc_core, test_app_exec_fails_conversion_of_bad_roman_number_1);
    tcase_add_test(tc_core, test_app_exec_fails_conversion_of_bad_roman_number_2);

    tcase_add_test(tc_core, test_app_exec_succeeds_for_addition);
    tcase_add_test(tc_core, test_app_exec_succeeds_for_subtraction);

    tcase_add_test(tc_core, test_app_exec_does_not_succeed);

    suite_add_tcase(s, tc_core);

    return s;
}

/* ===== Test Driver ======================================================== */

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    puts("-------------------------------------------------------------------------------");

    s = test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    puts("-------------------------------------------------------------------------------");

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
