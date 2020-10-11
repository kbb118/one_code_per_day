#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)
typedef long long int ll;

int main() {
    ll a,b,c,d;
    cin >> a>>b>>c>>d;
    ll ans=LLONG_MIN;
    if ( a*c > ans )
        ans = a*c;
    if ( a*d > ans )
        ans = a*d;
    if ( b*c > ans )
        ans = b*c;
    if ( b*d > ans )
        ans = b*d;
    cout << ans << endl;

    return 0;
}
