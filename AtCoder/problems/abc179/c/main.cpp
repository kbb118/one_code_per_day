#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    cin >> n;

    //a*b <=n-1 を満たすa,bの個数を数える
    int ans=0;
    rep1(a,n)
    {
        ans+=(n-1)/a;
    }
    cout << ans << endl;

    return 0;
}
