#include "munit/munit.h"

void test(int a, int b) {
    munit_assert_int(a, ==, b);
}

MunitResult my_test(const MunitParameter params[], void *user_data) {
    // silence compiler warning
    (void) params;
    (void) user_data;

    munit_assert(0 != 1);
    
    munit_assert_false(0);

    /* Calling Errors
    munit_error("FAIL");
    munit_errorf("Goodbye, cruel %s", "world");
    */

    const unsigned char val_uchar = 'b';
    munit_assert_uchar(val_uchar, ==, 'b');

    const char *stewardesses = "stewardesses";
    munit_assert_string_equal(stewardesses, "stewardesses");

    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    {
        (char*) "/example/compare",
        my_test,
        NULL,
        NULL,
        0,
        NULL
    }
};

static const MunitSuite test_suite = {
    (char*) "",
    test_suite_tests,
    NULL,
    0,
    MUNIT_SUITE_OPTION_NONE
};


#include <stdlib.h>

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
