#include <stdlib.h>
#include <check.h>

#include "roman.h"

START_TEST (test_roman_returns_name)
{
    char *name;

    name = roman_name();
    ck_assert_str_eq(name, "roman");
}
END_TEST

Suite * test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("roman test suite");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_roman_returns_name);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
