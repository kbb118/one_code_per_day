#include "example_lib.h"
#include <stdio.h>

int
main (int argc,
      char** argv)
{
        Test* test = test_new(2, "test");
        int a = mul_100(test);
        printf("%s = %d",test_name(test), a);
        return 0;
}
