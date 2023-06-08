#include "munit/munit.h"

void test(int a, int b) {
    munit_assert_int(a, ==, b);
}

int main() {
    test(1,0);
    return 0;
}