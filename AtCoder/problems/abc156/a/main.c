#include <stdio.h>

int main(int argc, char** argv)
{
    int n,r;
    scanf("%d", &n);
    scanf("%d", &r);

    if ( n < 10 )
        r += 100*(10-n);

    printf("%d\n", r);

    return 0;
}
