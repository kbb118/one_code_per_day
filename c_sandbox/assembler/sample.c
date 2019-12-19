#include <stdio.h>

int a, b;
main()
{
    a = 0;
    do {
        b += a + 1;
        a++;
    } while (a < 11);
}
