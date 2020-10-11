#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)


typedef unsigned long long int ull;

ull a[100005];

string winner(int n)
{
    ull res = 0;
    for (ull i = 1; i <= n; i++) {
        res ^= a[i];
    }

    if (res == 0)
        return "First";
    if (n%2 == 0)
        return "First";
    else
        return "Second";
}
int main() {
    int t;
    cin >> t;
    rep(i,t)
    {
        int n;
        cin >>n;
        rep1(j,n+1)
        {
            cin >> a[j];
        }
        cout << winner(n) << endl;
    }

    return 0;
}
