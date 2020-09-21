#include <stdio.h>

int S[(int)1e5];
int T[(int)5e4];

/*
 *
 * 0            x                     n
 * |----------------|-----------------|
 * l                m                 r
 *
 *  x   < S[m] のとき、解が m より左にあるので右境界を m にする。
 * S[m] <  x   のとき、解が m より右にあるので左境界を m+1 にする。
 * x == S[m] のとき解が見つかった
 */
int search(int x, int n)
{
    // [left, right)
    int l, m, r;
    l=0; r=n; m=n/2;
    while (l<r)
    {
        m=(l+r)/2;
        if ( x < S[m] )
            r=m;
        else if ( x > S[m] )
            l=m+1;
        else
            return 1;
    }
    return 0;
}

int main(int argc, char** argv)
{
    // S, T はソート済み
    // T に含まれるものの中で S に含まれるものの個数
    int ans = 0;

    // get input
    int n, q;
    scanf("%d", &n);
    for (int i=0; i<n; i++)
        scanf("%d", &S[i]);
    scanf("%d", &q);
    for (int i=0; i<q; i++)
        scanf("%d ", &T[i]);

    // binary search each member of T in S.
    for (int i=0; i<q; i++)
        ans += search(T[i], n);

    printf("%d\n", ans);

    return 0;
}
