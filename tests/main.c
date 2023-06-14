#include "munit/munit.h"
#include <stdlib.h>

void test(int a, int b) {
    munit_assert_int(a, ==, b);
}

MunitResult my_test(const MunitParameter params[], void *user_data) {
    // silence compiler warning
    (void) params;
    (void) user_data;

    munit_assert(0 != 1);
    
    munit_assert_false(0);

    const unsigned char val_uchar = 'b';
    munit_assert_uchar(val_uchar, ==, 'b');

    const char *stewardesses = "stewardesses";
    munit_assert_string_equal(stewardesses, "stewardesses");

    return MUNIT_OK;
}

static void *test_setup(const MunitParameter params[], void *user_data) {
    return strdup("Hello, world!");
}

static void test_teardown(void *fixture) {
    free(fixture);
}

static MunitResult test_with_setup(const MunitParameter params[], void *fixture) {
    char *str = (char*) fixture;
    munit_assert_string_equal(str, "Hello, world!");
    return MUNIT_OK;
}

static char *foo_params[] = { "one", "two", "three", NULL };
static char *bar_params[] = { "red", "green", "blue", NULL };
static MunitParameterEnum test_params[] = {
    { "foo", foo_params },
    { "bar", bar_params },
    { NULL, NULL }
};

static MunitResult param_test(const MunitParameter params[], void *user_data) {
    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    {
        "/example/compare", // Name
        my_test,            // Test Fn
        NULL,               // Startup
        NULL,               // Teardown
        MUNIT_TEST_OPTION_NONE, // Number of iterations
        NULL                // Parameters
    },
    { "/example/setup", test_with_setup, test_setup, test_teardown, 0, NULL },
    { "/example/params", param_test, NULL, NULL, 0, test_params },
    // Ending Marker
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
    "/tests",               // Name
    test_suite_tests,       // test array
    NULL,                   // Suite array
    1,                      // Iterations
    MUNIT_SUITE_OPTION_NONE // Options
};



int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
