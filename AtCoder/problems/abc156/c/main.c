#include <stdio.h>

int X[100];
int main(int argc, char** argv)
{
    int n;
    int sum=0;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%d", &X[i]);
        sum+=X[i];
    }

    /*
     * 0                                   x
     * |-----------------------------------|
     *
     * for i in [0..n)
     *   for p in [0..n)
     *     costs[p] = (x[i] - p)*(x[i] - p);
     *
     *  sigma{0..n-1}{p^2 -2px[i] + x[i]^2}
     *  = np^2 -2p(sigma x[i]) + sigma x[i]^2
     *  = n(p - sigma x[i]/n)^2 - sigma x[i] * sigma x[i]/n + sigma x[i]^2
     *
     * p = sigma x[i]/n のとき最小値。
     *
     * p で微分して 0 になる点が最小値をとる点なので
     * 2np -2(sigma x[i]) = 0
     * p = (sigma x[i])/n としても同じことか。
     */

    int ans=0;
    int p=(double)sum/n + 0.5;
    for(int i=0; i<n; i++)
        ans += (X[i]-p)*(X[i]-p);
    printf("%d\n", ans);

    return 0;
}
