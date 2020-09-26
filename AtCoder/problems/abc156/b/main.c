#include <stdio.h>
#include <math.h>

typedef long long int ll;

/*aのb進数時の桁数*/
ll digits(ll a, ll b){return a/b?1+digits(a/b,b):1;}

int main(int argc, char** argv)
{
    int n,k;

    scanf("%d", &n);
    scanf("%d", &k);

    // log_k(n)
    // log(n)/log(k)
    //printf("%d\n", (int)(log(n)/log(k))+1);
    printf("%lld\n", digits(n,k));

    return 0;
}
