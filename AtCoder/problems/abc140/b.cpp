#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    cin >> n;
    int a[n+1], b[n+1], c[n];
    rep1(i,n+1) cin >> a[i];
    rep1(i,n+1) cin >> b[i];
    rep1(i,n) cin >> c[i];

    int prev = -100;
    int ans=0;
    for(int i=1;i<n+1;i++)
    {
        if (i!=1)
            prev = a[i-1];
        ans += b[a[i]];
        if (a[i] == prev+1)
            ans += c[prev];
    }

    cout << ans;

    return 0;
}
