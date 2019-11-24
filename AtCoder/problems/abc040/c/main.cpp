#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int a[1000001];
int memo[1000001];
// n 番目の柱に至るまでの最小コスト
int to(int n)
{
    if (memo[n]!=-1)
        return memo[n];

    memo[n] = min(to(n-1) + abs(a[n]-a[n-1]),
                to(n-2) + abs(a[n]-a[n-2]));
    return memo[n];
}

int main() {
    int n;
    cin >> n;
    rep1(i,n+1) cin>>a[i];
    rep1(i,n+1) memo[i]=-1;
    memo[1]=0;memo[2]=abs(a[2]-a[1]);
    cout << to(n);
    return 0;
}
