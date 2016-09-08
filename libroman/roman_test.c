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
    unsigned    integer_value;
    int         success;

    integer_value = ROMAN_MAX_NUMBER;

    success = number2roman(integer_value, NULL);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_number2roman_fails_for_invalid_value)
{
    unsigned    integer_value;
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_value = ROMAN_MAX_NUMBER + 1;
    roman_value[0] = '\0';

    success = number2roman(integer_value, roman_value);

    ck_assert(success == 0);
    ck_assert_str_eq(roman_value, "");
}
END_TEST

START_TEST (test_number2roman_converts_maximum_roman_value)
{
    unsigned    integer_value;
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_value = ROMAN_MAX_NUMBER;
    roman_value[0] = '\0';

    success = number2roman(integer_value, roman_value);

    ck_assert(success);
    ck_assert_str_eq(roman_value, "MMMCMXCIX");
}
END_TEST

START_TEST (test_number2roman_converts_longest_roman_value)
{
    unsigned    integer_value;
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_value = 3888;
    roman_value[0] = '\0';

    success = number2roman(integer_value, roman_value);

    ck_assert(success);
    ck_assert_str_eq(roman_value, "MMMDCCCLXXXVIII");
}
END_TEST

START_TEST (test_number2roman_converts_0)
{
    unsigned    integer_value;
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_value = 0;
    roman_value[0] = '\0';

    success = number2roman(integer_value, roman_value);

    ck_assert(success);
    ck_assert_str_eq(roman_value, "");
}
END_TEST

START_TEST (test_number2roman_converts_1954)
{
    unsigned    integer_value;
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_value = 1954;
    roman_value[0] = '\0';

    success = number2roman(integer_value, roman_value);

    ck_assert(success);
    ck_assert_str_eq(roman_value, "MCMLIV");
}
END_TEST

START_TEST (test_number2roman_converts_1990)
{
    unsigned    integer_value;
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_value = 1990;
    roman_value[0] = '\0';

    success = number2roman(integer_value, roman_value);

    ck_assert(success);
    ck_assert_str_eq(roman_value, "MCMXC");
}
END_TEST

START_TEST (test_number2roman_converts_2014)
{
    unsigned    integer_value;
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    integer_value = 2014;
    roman_value[0] = '\0';

    success = number2roman(integer_value, roman_value);

    ck_assert(success);
    ck_assert_str_eq(roman_value, "MMXIV");
}
END_TEST

/* ===== roman2number() ===================================================== */

START_TEST (test_roman2number_fails_for_NULL_string_pointer)
{
    unsigned    integer_value;
    int         success;

    integer_value = 0;

    success = roman2number(NULL, &integer_value);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_roman2number_fails_for_NULL_integer_pointer)
{
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    roman_value[0] = '\0';

    success = roman2number(roman_value, NULL);

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

START_TEST (test_roman2number_fails_for_invalid_roman_value_1)
{
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_value;
    int         success;

    strncpy(roman_value, "MMMMCMXCIX", ROMAN_MAX_STRING_LENGTH);  /* Too big */
    roman_value[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_value = 0;

    success = roman2number(roman_value, &integer_value);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_roman2number_fails_for_invalid_roman_value_2)
{
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_value;
    int         success;

    strncpy(roman_value, "MCMXMCMIX", ROMAN_MAX_STRING_LENGTH);  /* Bad sequence */
    roman_value[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_value = 0;

    success = roman2number(roman_value, &integer_value);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_roman2number_fails_for_invalid_roman_value_3)
{
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_value;
    int         success;

    strncpy(roman_value, "MCMXCL", ROMAN_MAX_STRING_LENGTH);  /* Bad sequence */
    roman_value[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_value = 0;

    success = roman2number(roman_value, &integer_value);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_roman2number_fails_for_invalid_roman_value_4)
{
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_value;
    int         success;

    strncpy(roman_value, "XIVX", ROMAN_MAX_STRING_LENGTH);  /* Bad sequence */
    roman_value[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_value = 0;

    success = roman2number(roman_value, &integer_value);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_roman2number_converts_maximum_roman_value)
{
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_value;
    int         success;

    strncpy(roman_value, "MMMCMXCIX", ROMAN_MAX_STRING_LENGTH);
    roman_value[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_value = 0;

    success = roman2number(roman_value, &integer_value);

    ck_assert(success);
    ck_assert_uint_eq(integer_value, ROMAN_MAX_NUMBER);
}
END_TEST

START_TEST (test_roman2number_converts_longest_roman_value)
{
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_value;
    int         success;

    strncpy(roman_value, "MMMDCCCLXXXVIII", ROMAN_MAX_STRING_LENGTH);
    roman_value[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_value = 0;

    success = roman2number(roman_value, &integer_value);

    ck_assert(success);
    ck_assert_uint_eq(integer_value, 3888);
}
END_TEST

START_TEST (test_roman2number_converts_0)
{
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_value;
    int         success;

    strncpy(roman_value, "", ROMAN_MAX_STRING_LENGTH);
    roman_value[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_value = 0;

    success = roman2number(roman_value, &integer_value);

    ck_assert(success);
    ck_assert_uint_eq(integer_value, 0);
}
END_TEST

START_TEST (test_roman2number_converts_1954)
{
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_value;
    int         success;

    strncpy(roman_value, "MCMLIV", ROMAN_MAX_STRING_LENGTH);
    roman_value[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_value = 0;

    success = roman2number(roman_value, &integer_value);

    ck_assert(success);
    ck_assert_uint_eq(integer_value, 1954);
}
END_TEST

START_TEST (test_roman2number_converts_1990)
{
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_value;
    int         success;

    strncpy(roman_value, "MCMXC", ROMAN_MAX_STRING_LENGTH);
    roman_value[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_value = 0;

    success = roman2number(roman_value, &integer_value);

    ck_assert(success);
    ck_assert_uint_eq(integer_value, 1990);
}
END_TEST

START_TEST (test_roman2number_converts_2014)
{
    char        roman_value[ROMAN_MAX_STRING_LENGTH + 1];
    unsigned    integer_value;
    int         success;

    strncpy(roman_value, "MMXIV", ROMAN_MAX_STRING_LENGTH);
    roman_value[ROMAN_MAX_STRING_LENGTH] = '\0';
    integer_value = 0;

    success = roman2number(roman_value, &integer_value);

    ck_assert(success);
    ck_assert_uint_eq(integer_value, 2014);
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

START_TEST (test_romanAdd_adds_valid_roman_values)
{
    char        roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_value1, "MCMLIV", ROMAN_MAX_STRING_LENGTH);  /* 1954 */
    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_value2, "CXLIV", ROMAN_MAX_STRING_LENGTH);  /* 144 */
    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_value3[0] = '\0';

    success = romanAdd(roman_value1, roman_value2, roman_value3);

    ck_assert(success);
    ck_assert_str_eq(roman_value3, "MMXCVIII");  /* 2098 */
}
END_TEST

START_TEST (test_romanAdd_adds_kata_example_1)
{
    char        roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_value1, "XIV", ROMAN_MAX_STRING_LENGTH);  /* 14 */
    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_value2, "LX", ROMAN_MAX_STRING_LENGTH);  /* 60 */
    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_value3[0] = '\0';

    success = romanAdd(roman_value1, roman_value2, roman_value3);

    ck_assert(success);
    ck_assert_str_eq(roman_value3, "LXXIV");  /* 74 */
}
END_TEST

START_TEST (test_romanAdd_adds_kata_example_2)
{
    char        roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_value1, "XX", ROMAN_MAX_STRING_LENGTH);  /* 20 */
    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_value2, "II", ROMAN_MAX_STRING_LENGTH);  /* 2 */
    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_value3[0] = '\0';

    success = romanAdd(roman_value1, roman_value2, roman_value3);

    ck_assert(success);
    ck_assert_str_eq(roman_value3, "XXII");  /* 22 */
}
END_TEST

START_TEST (test_romanAdd_fails_when_sum_will_be_invalid)
{
    char        roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_value1, "MMMCMXCIX", ROMAN_MAX_STRING_LENGTH);  /* 3999 */
    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_value2, "I", ROMAN_MAX_STRING_LENGTH);  /* 1 */
    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_value3[0] = '\0';

    success = romanAdd(roman_value1, roman_value2, roman_value3);

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
    char        roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_value1, "MCMLIV", ROMAN_MAX_STRING_LENGTH);  /* 1954 */
    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_value2, "MCMLIV", ROMAN_MAX_STRING_LENGTH);  /* 1954 */
    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_value3[0] = '\0';

    success = romanSub(roman_value1, roman_value2, roman_value3);

    ck_assert(success);
    ck_assert_str_eq(roman_value3, "");
}
END_TEST

START_TEST (test_romanSub_subtracts_when_roman_values_are_positively_ordered)
{
    char        roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_value1, "MCMLIV", ROMAN_MAX_STRING_LENGTH);  /* 1954 */
    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_value2, "CXLIV", ROMAN_MAX_STRING_LENGTH);  /* 144 */
    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_value3[0] = '\0';

    success = romanSub(roman_value1, roman_value2, roman_value3);

    ck_assert(success);
    ck_assert_str_eq(roman_value3, "MDCCCX");  /* 1810 */
}
END_TEST

START_TEST (test_romanSub_fails_when_roman_values_are_negatively_ordered)
{
    char        roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_value1, "CXLIV", ROMAN_MAX_STRING_LENGTH);  /* 144 */
    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_value2, "MCMLIV", ROMAN_MAX_STRING_LENGTH);  /* 1954 */
    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_value3[0] = '\0';

    success = romanSub(roman_value1, roman_value2, roman_value3);

    ck_assert(success == 0);
}
END_TEST

START_TEST (test_romanSub_subtracts_kata_example_1)
{
    char        roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_value1, "LXXIV", ROMAN_MAX_STRING_LENGTH);  /* 74 */
    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_value2, "XIV", ROMAN_MAX_STRING_LENGTH);  /* 14 */
    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_value3[0] = '\0';

    success = romanSub(roman_value1, roman_value2, roman_value3);

    ck_assert(success);
    ck_assert_str_eq(roman_value3, "LX");  /* 60 */
}
END_TEST

START_TEST (test_romanSub_subtracts_kata_example_2)
{
    char        roman_value1[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value2[ROMAN_MAX_STRING_LENGTH + 1];
    char        roman_value3[ROMAN_MAX_STRING_LENGTH + 1];
    int         success;

    strncpy(roman_value1, "XXII", ROMAN_MAX_STRING_LENGTH);  /* 22 */
    roman_value1[ROMAN_MAX_STRING_LENGTH] = '\0';

    strncpy(roman_value2, "II", ROMAN_MAX_STRING_LENGTH);  /* 2 */
    roman_value2[ROMAN_MAX_STRING_LENGTH] = '\0';

    roman_value3[0] = '\0';

    success = romanSub(roman_value1, roman_value2, roman_value3);

    ck_assert(success);
    ck_assert_str_eq(roman_value3, "XX");  /* 20 */
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
    tcase_add_test(tc_core, test_number2roman_fails_for_invalid_value);
    tcase_add_test(tc_core, test_number2roman_converts_maximum_roman_value);
    tcase_add_test(tc_core, test_number2roman_converts_longest_roman_value);
    tcase_add_test(tc_core, test_number2roman_converts_0);
    tcase_add_test(tc_core, test_number2roman_converts_1954);
    tcase_add_test(tc_core, test_number2roman_converts_1990);
    tcase_add_test(tc_core, test_number2roman_converts_2014);

    tcase_add_test(tc_core, test_roman2number_fails_for_NULL_string_pointer);
    tcase_add_test(tc_core, test_roman2number_fails_for_NULL_integer_pointer);
    tcase_add_test(tc_core, test_roman2number_fails_for_NULL_pointers);
    tcase_add_test(tc_core, test_roman2number_fails_for_invalid_roman_value_1);
    tcase_add_test(tc_core, test_roman2number_fails_for_invalid_roman_value_2);
    tcase_add_test(tc_core, test_roman2number_fails_for_invalid_roman_value_3);
    tcase_add_test(tc_core, test_roman2number_fails_for_invalid_roman_value_4);
    tcase_add_test(tc_core, test_roman2number_converts_maximum_roman_value);
    tcase_add_test(tc_core, test_roman2number_converts_longest_roman_value);
    tcase_add_test(tc_core, test_roman2number_converts_0);
    tcase_add_test(tc_core, test_roman2number_converts_1954);
    tcase_add_test(tc_core, test_roman2number_converts_1990);
    tcase_add_test(tc_core, test_roman2number_converts_2014);

    tcase_add_test(tc_core, test_romanAdd_fails_for_NULL_pointers);
    tcase_add_test(tc_core, test_romanAdd_adds_valid_roman_values);
    tcase_add_test(tc_core, test_romanAdd_adds_kata_example_1);
    tcase_add_test(tc_core, test_romanAdd_adds_kata_example_2);
    tcase_add_test(tc_core, test_romanAdd_fails_when_sum_will_be_invalid);

    tcase_add_test(tc_core, test_romanSub_fails_for_NULL_pointers);
    tcase_add_test(tc_core, test_romanSub_subtracts_to_empty_string_for_equal_values);
    tcase_add_test(tc_core, test_romanSub_subtracts_when_roman_values_are_positively_ordered);
    tcase_add_test(tc_core, test_romanSub_fails_when_roman_values_are_negatively_ordered);
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
