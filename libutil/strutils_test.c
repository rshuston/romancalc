#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>

#include "strutils.h"

#define STANDARD_LINE_LENGTH    80

/* ===== strutils_name() ==================================================== */

START_TEST (test_strutils_returns_name)
{
    char *name;

    name = strutils_name();
    ck_assert_str_eq(name, "strutils");
}
END_TEST

/* ===== trim() ============================================================= */

START_TEST (test_trim_handles_NULL_pointer)
{
    char    *output;

    output = trim(NULL);

    ck_assert_ptr_eq(output, NULL);
}
END_TEST

START_TEST (test_trim_handles_empty_string)
{
    char    input[STANDARD_LINE_LENGTH + 1];
    char    *output;

    input[0] = '\0';

    output = trim(input);

    ck_assert_str_eq(output, "");
    ck_assert_ptr_eq(output, input);
    ck_assert_int_eq(strlen(output), strlen(input));
}
END_TEST

START_TEST (test_trim_strips_leading_spaces)
{
    char    input[STANDARD_LINE_LENGTH + 1];
    char    *output;

    strncpy(input, "   hello, world", STANDARD_LINE_LENGTH);
    input[STANDARD_LINE_LENGTH] = '\0';  /* Put an elephant in Cairo */

    output = trim(input);

    ck_assert_str_eq(output, "hello, world");
}
END_TEST

START_TEST (test_trim_strips_trailing_spaces)
{
    char    input[STANDARD_LINE_LENGTH + 1];
    char    *output;

    strncpy(input, "hello, world   \n", STANDARD_LINE_LENGTH);
    input[STANDARD_LINE_LENGTH] = '\0';  /* Put an elephant in Cairo */

    output = trim(input);

    ck_assert_str_eq(output, "hello, world");
}
END_TEST

START_TEST (test_trim_strips_leading_and_trailing_spaces)
{
    char    input[STANDARD_LINE_LENGTH + 1];
    char    *output;

    strncpy(input, "\n   hello, world   \n", STANDARD_LINE_LENGTH);
    input[STANDARD_LINE_LENGTH] = '\0';  /* Put an elephant in Cairo */

    output = trim(input);

    ck_assert_str_eq(output, "hello, world");
}
END_TEST

START_TEST (test_trim_does_not_alter_normal_string)
{
    char    input[STANDARD_LINE_LENGTH + 1];
    char    *output;

    strncpy(input, "hello, world", STANDARD_LINE_LENGTH);
    input[STANDARD_LINE_LENGTH] = '\0';  /* Put an elephant in Cairo */

    output = trim(input);

    ck_assert_str_eq(output, "hello, world");
    ck_assert_ptr_eq(output, input);
    ck_assert_int_eq(strlen(output), strlen(input));
}
END_TEST

/* ===== lowercase() ======================================================== */

START_TEST (test_lowercase_handles_NULL_pointer)
{
    char    *output;

    output = lowercase(NULL);

    ck_assert_ptr_eq(output, NULL);
}
END_TEST

START_TEST (test_lowercase_handles_empty_string)
{
    char    input[STANDARD_LINE_LENGTH + 1];
    char    *output;

    input[0] = '\0';

    output = lowercase(input);

    ck_assert_str_eq(output, "");
    ck_assert_ptr_eq(output, input);
    ck_assert_int_eq(strlen(output), strlen(input));
}
END_TEST

START_TEST (test_lowercase_converts_all_letters_to_lowercase)
{
    char    input[STANDARD_LINE_LENGTH + 1];
    char    *output;

    strncpy(input, "  Yeah, this is a Great 1st Test!  \n", STANDARD_LINE_LENGTH);
    input[STANDARD_LINE_LENGTH] = '\0';  /* Put an elephant in Cairo */

    output = lowercase(input);

    ck_assert_str_eq(output, "  yeah, this is a great 1st test!  \n");
}
END_TEST

/* ===== uppercase() ======================================================== */

START_TEST (test_uppercase_handles_NULL_pointer)
{
    char    *output;

    output = uppercase(NULL);

    ck_assert_ptr_eq(output, NULL);
}
END_TEST

START_TEST (test_uppercase_handles_empty_string)
{
    char    input[STANDARD_LINE_LENGTH + 1];
    char    *output;

    input[0] = '\0';

    output = uppercase(input);

    ck_assert_str_eq(output, "");
    ck_assert_ptr_eq(output, input);
    ck_assert_int_eq(strlen(output), strlen(input));
}
END_TEST

START_TEST (test_uppercase_converts_all_letters_to_uppercase)
{
    char    input[STANDARD_LINE_LENGTH + 1];
    char    *output;

    strncpy(input, "  Yeah, this is a Great 1st Test!  \n", STANDARD_LINE_LENGTH);
    input[STANDARD_LINE_LENGTH] = '\0';  /* Put an elephant in Cairo */

    output = uppercase(input);

    ck_assert_str_eq(output, "  YEAH, THIS IS A GREAT 1ST TEST!  \n");
}
END_TEST

/* ===== strConsistsOfCharSet() ============================================= */

START_TEST (test_strConsistsOfCharSet_returns_true_for_consisting_of_char_set_1)
{
    int result;

    result = strConsistsOfCharSet("1984", "0123456789");

    ck_assert_int_ne(result, 0);
}
END_TEST

START_TEST (test_strConsistsOfCharSet_returns_true_for_consisting_of_char_set_2)
{
    int result;

    result = strConsistsOfCharSet("MCMLIIIIV", "MDCLXVI");

    ck_assert_int_ne(result, 0);
}
END_TEST

START_TEST (test_strConsistsOfCharSet_returns_false_for_NULL_string)
{
    int result;

    result = strConsistsOfCharSet(NULL, "0123456789");

    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST (test_strConsistsOfCharSet_returns_false_for_empty_string)
{
    int result;

    result = strConsistsOfCharSet("", "0123456789");

    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST (test_strConsistsOfCharSet_returns_false_for_NULL_char_set)
{
    int result;

    result = strConsistsOfCharSet("MCMLIIIIV", NULL);

    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST (test_strConsistsOfCharSet_returns_false_for_empty_char_set)
{
    int result;

    result = strConsistsOfCharSet("MCMLIIIIV", "");

    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST (test_strConsistsOfCharSet_returns_false_for_not_consisting_of_char_set_1)
{
    int result;

    result = strConsistsOfCharSet("1984", "MDCLXVI");

    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST (test_strConsistsOfCharSet_returns_false_for_not_consisting_of_char_set_2)
{
    int result;

    result = strConsistsOfCharSet("MCMLIIIIV", "0123456789");

    ck_assert_int_eq(result, 0);
}
END_TEST

/* ===== Test Suite ========================================================= */

Suite * test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("strutils test suite");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_strutils_returns_name);

    tcase_add_test(tc_core, test_trim_handles_NULL_pointer);
    tcase_add_test(tc_core, test_trim_handles_empty_string);
    tcase_add_test(tc_core, test_trim_strips_leading_spaces);
    tcase_add_test(tc_core, test_trim_strips_trailing_spaces);
    tcase_add_test(tc_core, test_trim_strips_leading_and_trailing_spaces);
    tcase_add_test(tc_core, test_trim_does_not_alter_normal_string);

    tcase_add_test(tc_core, test_lowercase_handles_NULL_pointer);
    tcase_add_test(tc_core, test_lowercase_handles_empty_string);
    tcase_add_test(tc_core, test_lowercase_converts_all_letters_to_lowercase);

    tcase_add_test(tc_core, test_uppercase_handles_NULL_pointer);
    tcase_add_test(tc_core, test_uppercase_handles_empty_string);
    tcase_add_test(tc_core, test_uppercase_converts_all_letters_to_uppercase);

    tcase_add_test(tc_core, test_strConsistsOfCharSet_returns_true_for_consisting_of_char_set_1);
    tcase_add_test(tc_core, test_strConsistsOfCharSet_returns_true_for_consisting_of_char_set_2);
    tcase_add_test(tc_core, test_strConsistsOfCharSet_returns_false_for_NULL_string);
    tcase_add_test(tc_core, test_strConsistsOfCharSet_returns_false_for_empty_string);
    tcase_add_test(tc_core, test_strConsistsOfCharSet_returns_false_for_NULL_char_set);
    tcase_add_test(tc_core, test_strConsistsOfCharSet_returns_false_for_empty_char_set);
    tcase_add_test(tc_core, test_strConsistsOfCharSet_returns_false_for_not_consisting_of_char_set_1);
    tcase_add_test(tc_core, test_strConsistsOfCharSet_returns_false_for_not_consisting_of_char_set_2);

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
