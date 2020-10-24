#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

typedef unsigned long long int ull;
typedef long long int ll;

int main() {
    ll n;
    cin >> n;

    ll man = 0;
    ll euc = 0;
    ll che = 0;
    rep(i, n)
    {
        ll x;
        cin >> x;
        if (x<0)
            x*=-1;

        man += x;
        euc += x*x;
        che = max(x,che);
    }
    cout << man << endl;
    cout << std::setprecision(15)  << sqrt(euc) << endl;
    cout << che << endl;

    return 0;
}
