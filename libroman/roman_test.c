#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>

#include "roman.h"

#define STANDARD_LINE_LENGTH    80

/* ===== roman_name() ======================================================= */

START_TEST (test_roman_returns_name)
{
    char *name;

    name = roman_name();
    ck_assert_str_eq(name, "roman");
}
END_TEST

/* ===== number2roman() ===================================================== */

START_TEST (test_number2roman_fails_for_NULL_string_pointer)
{
    unsigned    integer_year;
    int         success;

    integer_year = ROMAN_MAX_NUMBER;

    success = number2roman(integer_year, NULL);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_number2roman_fails_for_invalid_year)
{
    unsigned    integer_year;
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_year = ROMAN_MAX_NUMBER + 1;
    roman_year[0] = '\0';

    success = number2roman(integer_year, roman_year);

    ck_assert(success == 0);
    ck_assert_str_eq(roman_year, "");
}
END_TEST

START_TEST (test_number2roman_converts_maximum_roman_year)
{
    unsigned    integer_year;
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_year = ROMAN_MAX_NUMBER;
    roman_year[0] = '\0';

    success = number2roman(integer_year, roman_year);

    ck_assert(success);
    ck_assert_str_eq(roman_year, "MMMCMXCIX");
}
END_TEST

START_TEST (test_number2roman_converts_longest_roman_year)
{
    unsigned    integer_year;
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_year = 3888;
    roman_year[0] = '\0';

    success = number2roman(integer_year, roman_year);

    ck_assert(success);
    ck_assert_str_eq(roman_year, "MMMDCCCLXXXVIII");
}
END_TEST

START_TEST (test_number2roman_converts_0)
{
    unsigned    integer_year;
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_year = 0;
    roman_year[0] = '\0';

    success = number2roman(integer_year, roman_year);

    ck_assert(success);
    ck_assert_str_eq(roman_year, "");
}
END_TEST

START_TEST (test_number2roman_converts_1954)
{
    unsigned    integer_year;
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_year = 1954;
    roman_year[0] = '\0';

    success = number2roman(integer_year, roman_year);

    ck_assert(success);
    ck_assert_str_eq(roman_year, "MCMLIV");
}
END_TEST

START_TEST (test_number2roman_converts_1990)
{
    unsigned    integer_year;
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_year = 1990;
    roman_year[0] = '\0';

    success = number2roman(integer_year, roman_year);

    ck_assert(success);
    ck_assert_str_eq(roman_year, "MCMXC");
}
END_TEST

START_TEST (test_number2roman_converts_2014)
{
    unsigned    integer_year;
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_year = 2014;
    roman_year[0] = '\0';

    success = number2roman(integer_year, roman_year);

    ck_assert(success);
    ck_assert_str_eq(roman_year, "MMXIV");
}
END_TEST

/* ===== roman2number() ===================================================== */

START_TEST (test_roman2number_fails_for_NULL_string_pointer)
{
    unsigned    integer_year;
    int         success;

    integer_year = 0;

    success = roman2number(NULL, &integer_year);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_roman2number_fails_for_NULL_integer_pointer)
{
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    roman_year[0] = '\0';

    success = roman2number(roman_year, NULL);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_roman2number_fails_for_NULL_pointers)
{
    int         success;

    success = roman2number(NULL, NULL);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_roman2number_fails_for_invalid_roman_year_1)
{
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_year;
    int         success;

    strncpy(roman_year, "MMMMCMXCIX", ROMAN_MAX_STRING_LENGTH);  /* Too big */
    roman_year[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_year = 0;

    success = roman2number(roman_year, &integer_year);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_roman2number_fails_for_invalid_roman_year_2)
{
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_year;
    int         success;

    strncpy(roman_year, "MCMXMCMIX", ROMAN_MAX_STRING_LENGTH);  /* Bad sequence */
    roman_year[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_year = 0;

    success = roman2number(roman_year, &integer_year);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_roman2number_fails_for_invalid_roman_year_3)
{
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_year;
    int         success;

    strncpy(roman_year, "MCMXCL", ROMAN_MAX_STRING_LENGTH);  /* Bad sequence */
    roman_year[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_year = 0;

    success = roman2number(roman_year, &integer_year);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_roman2number_fails_for_invalid_roman_year_4)
{
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_year;
    int         success;

    strncpy(roman_year, "XIVX", ROMAN_MAX_STRING_LENGTH);  /* Bad sequence */
    roman_year[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_year = 0;

    success = roman2number(roman_year, &integer_year);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_roman2number_converts_maximum_roman_year)
{
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_year;
    int         success;

    strncpy(roman_year, "MMMCMXCIX", ROMAN_MAX_STRING_LENGTH);
    roman_year[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_year = 0;

    success = roman2number(roman_year, &integer_year);

    ck_assert(success);
    ck_assert_uint_eq(integer_year, ROMAN_MAX_NUMBER);
}
END_TEST

START_TEST (test_roman2number_converts_longest_roman_year)
{
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_year;
    int         success;

    strncpy(roman_year, "MMMDCCCLXXXVIII", ROMAN_MAX_STRING_LENGTH);
    roman_year[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_year = 0;

    success = roman2number(roman_year, &integer_year);

    ck_assert(success);
    ck_assert_uint_eq(integer_year, 3888);
}
END_TEST

START_TEST (test_roman2number_converts_0)
{
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_year;
    int         success;

    strncpy(roman_year, "", ROMAN_MAX_STRING_LENGTH);
    roman_year[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_year = 0;

    success = roman2number(roman_year, &integer_year);

    ck_assert(success);
    ck_assert_uint_eq(integer_year, 0);
}
END_TEST

START_TEST (test_roman2number_converts_1954)
{
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_year;
    int         success;

    strncpy(roman_year, "MCMLIV", ROMAN_MAX_STRING_LENGTH);
    roman_year[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_year = 0;

    success = roman2number(roman_year, &integer_year);

    ck_assert(success);
    ck_assert_uint_eq(integer_year, 1954);
}
END_TEST

START_TEST (test_roman2number_converts_1990)
{
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_year;
    int         success;

    strncpy(roman_year, "MCMXC", ROMAN_MAX_STRING_LENGTH);
    roman_year[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_year = 0;

    success = roman2number(roman_year, &integer_year);

    ck_assert(success);
    ck_assert_uint_eq(integer_year, 1990);
}
END_TEST

START_TEST (test_roman2number_converts_2014)
{
    char        roman_year[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_year;
    int         success;

    strncpy(roman_year, "MMXIV", ROMAN_MAX_STRING_LENGTH);
    roman_year[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_year = 0;

    success = roman2number(roman_year, &integer_year);

    ck_assert(success);
    ck_assert_uint_eq(integer_year, 2014);
}
END_TEST

/* ===== romanAdd() ========================================================= */

START_TEST (test_romanAdd_fails_for_NULL_pointers)
{
    int         success;

    success = romanAdd(NULL, NULL, NULL);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_romanAdd_adds_valid_roman_years)
{
    char        roman_year1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_year1, "MCMLIV", ROMAN_MAX_STRING_LENGTH);  /* 1954 */
    roman_year1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_year2, "CXLIV", ROMAN_MAX_STRING_LENGTH);  /* 144 */
    roman_year2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_year3[0] = '\0';

    success = romanAdd(roman_year1, roman_year2, roman_year3);

    ck_assert(success);
    ck_assert_str_eq(roman_year3, "MMXCVIII");  /* 2098 */
}
END_TEST

START_TEST (test_romanAdd_adds_kata_example_1)
{
    char        roman_year1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_year1, "XIV", ROMAN_MAX_STRING_LENGTH);  /* 14 */
    roman_year1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_year2, "LX", ROMAN_MAX_STRING_LENGTH);  /* 60 */
    roman_year2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_year3[0] = '\0';

    success = romanAdd(roman_year1, roman_year2, roman_year3);

    ck_assert(success);
    ck_assert_str_eq(roman_year3, "LXXIV");  /* 74 */
}
END_TEST

START_TEST (test_romanAdd_adds_kata_example_2)
{
    char        roman_year1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_year1, "XX", ROMAN_MAX_STRING_LENGTH);  /* 20 */
    roman_year1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_year2, "II", ROMAN_MAX_STRING_LENGTH);  /* 2 */
    roman_year2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_year3[0] = '\0';

    success = romanAdd(roman_year1, roman_year2, roman_year3);

    ck_assert(success);
    ck_assert_str_eq(roman_year3, "XXII");  /* 22 */
}
END_TEST

START_TEST (test_romanAdd_fails_when_sum_will_be_invalid)
{
    char        roman_year1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_year1, "MMMCMXCIX", ROMAN_MAX_STRING_LENGTH);  /* 3999 */
    roman_year1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_year2, "I", ROMAN_MAX_STRING_LENGTH);  /* 1 */
    roman_year2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_year3[0] = '\0';

    success = romanAdd(roman_year1, roman_year2, roman_year3);

    ck_assert(success == 0);
}
END_TEST

/* ===== romanSub() ========================================================= */

START_TEST (test_romanSub_fails_for_NULL_pointers)
{
    int         success;

    success = romanSub(NULL, NULL, NULL);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_romanSub_subtracts_to_empty_string_for_equal_values)
{
    char        roman_year1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_year1, "MCMLIV", ROMAN_MAX_STRING_LENGTH);  /* 1954 */
    roman_year1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_year2, "MCMLIV", ROMAN_MAX_STRING_LENGTH);  /* 1954 */
    roman_year2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_year3[0] = '\0';

    success = romanSub(roman_year1, roman_year2, roman_year3);

    ck_assert(success);
    ck_assert_str_eq(roman_year3, "");
}
END_TEST

START_TEST (test_romanSub_subtracts_when_roman_years_are_positively_ordered)
{
    char        roman_year1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_year1, "MCMLIV", ROMAN_MAX_STRING_LENGTH);  /* 1954 */
    roman_year1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_year2, "CXLIV", ROMAN_MAX_STRING_LENGTH);  /* 144 */
    roman_year2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_year3[0] = '\0';

    success = romanSub(roman_year1, roman_year2, roman_year3);

    ck_assert(success);
    ck_assert_str_eq(roman_year3, "MDCCCX");  /* 1810 */
}
END_TEST

START_TEST (test_romanSub_fails_when_roman_years_are_negatively_ordered)
{
    char        roman_year1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_year1, "CXLIV", ROMAN_MAX_STRING_LENGTH);  /* 144 */
    roman_year1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_year2, "MCMLIV", ROMAN_MAX_STRING_LENGTH);  /* 1954 */
    roman_year2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_year3[0] = '\0';

    success = romanSub(roman_year1, roman_year2, roman_year3);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_romanSub_subtracts_kata_example_1)
{
    char        roman_year1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_year1, "LXXIV", ROMAN_MAX_STRING_LENGTH);  /* 74 */
    roman_year1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_year2, "XIV", ROMAN_MAX_STRING_LENGTH);  /* 14 */
    roman_year2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_year3[0] = '\0';

    success = romanSub(roman_year1, roman_year2, roman_year3);

    ck_assert(success);
    ck_assert_str_eq(roman_year3, "LX");  /* 60 */
}
END_TEST

START_TEST (test_romanSub_subtracts_kata_example_2)
{
    char        roman_year1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_year3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_year1, "XXII", ROMAN_MAX_STRING_LENGTH);  /* 22 */
    roman_year1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_year2, "II", ROMAN_MAX_STRING_LENGTH);  /* 2 */
    roman_year2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_year3[0] = '\0';

    success = romanSub(roman_year1, roman_year2, roman_year3);

    ck_assert(success);
    ck_assert_str_eq(roman_year3, "XX");  /* 20 */
}
END_TEST

/* ===== Test Suite ========================================================= */

Suite * test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("roman test suite");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_roman_returns_name);

    tcase_add_test(tc_core, test_number2roman_fails_for_NULL_string_pointer);
    tcase_add_test(tc_core, test_number2roman_fails_for_invalid_year);
    tcase_add_test(tc_core, test_number2roman_converts_maximum_roman_year);
    tcase_add_test(tc_core, test_number2roman_converts_longest_roman_year);
    tcase_add_test(tc_core, test_number2roman_converts_0);
    tcase_add_test(tc_core, test_number2roman_converts_1954);
    tcase_add_test(tc_core, test_number2roman_converts_1990);
    tcase_add_test(tc_core, test_number2roman_converts_2014);

    tcase_add_test(tc_core, test_roman2number_fails_for_NULL_string_pointer);
    tcase_add_test(tc_core, test_roman2number_fails_for_NULL_integer_pointer);
    tcase_add_test(tc_core, test_roman2number_fails_for_NULL_pointers);
    tcase_add_test(tc_core, test_roman2number_fails_for_invalid_roman_year_1);
    tcase_add_test(tc_core, test_roman2number_fails_for_invalid_roman_year_2);
    tcase_add_test(tc_core, test_roman2number_fails_for_invalid_roman_year_3);
    tcase_add_test(tc_core, test_roman2number_fails_for_invalid_roman_year_4);
    tcase_add_test(tc_core, test_roman2number_converts_maximum_roman_year);
    tcase_add_test(tc_core, test_roman2number_converts_longest_roman_year);
    tcase_add_test(tc_core, test_roman2number_converts_0);
    tcase_add_test(tc_core, test_roman2number_converts_1954);
    tcase_add_test(tc_core, test_roman2number_converts_1990);
    tcase_add_test(tc_core, test_roman2number_converts_2014);

    tcase_add_test(tc_core, test_romanAdd_fails_for_NULL_pointers);
    tcase_add_test(tc_core, test_romanAdd_adds_valid_roman_years);
    tcase_add_test(tc_core, test_romanAdd_adds_kata_example_1);
    tcase_add_test(tc_core, test_romanAdd_adds_kata_example_2);
    tcase_add_test(tc_core, test_romanAdd_fails_when_sum_will_be_invalid);

    tcase_add_test(tc_core, test_romanSub_fails_for_NULL_pointers);
    tcase_add_test(tc_core, test_romanSub_subtracts_to_empty_string_for_equal_values);
    tcase_add_test(tc_core, test_romanSub_subtracts_when_roman_years_are_positively_ordered);
    tcase_add_test(tc_core, test_romanSub_fails_when_roman_years_are_negatively_ordered);
    tcase_add_test(tc_core, test_romanSub_subtracts_kata_example_1);
    tcase_add_test(tc_core, test_romanSub_subtracts_kata_example_2);

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
