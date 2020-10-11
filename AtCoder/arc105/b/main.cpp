#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

typedef long long int ll;

// 10^5 = 100000
// 10^1 = 10
//        100000
set<ll> a;
int main() {
    ll n;
    cin >> n;
    rep(i, n)
    {
        ll t;
        cin >> t;
        a.insert(t);
    }

    while(a.size()>1)
    {
        ll max = *(a.rbegin());
        ll min = *(a.begin());

        if ( max==min )
            break;
        a.insert(max-min);
        a.erase(max);
    }
    cout << *(a.begin()) << endl;

    return 0;
}
