#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

typedef unsigned long long int ull;
typedef long long int ll;


class ModularExponentiation
{
    int ans;                    // Answer
public:
    ll compME(ll, ll, ll);  // Compute Modular Exponentiation
};
/*
 * Compute Modular Exponentiation
 */
ll ModularExponentiation::compME(ll b, ll e, ll m)
{
    if (e == 0) return 1;

    ans = compME(b, e / 2, m);
    ans = (ans * ans) % m;
    if (e % 2 == 1) ans = (ans * b) % m;

    return ans;
}

#define MOD 998244353

ll m_sum(ll a,ll b)
{
    ll c = a + b;
    return (c > 0) ? c%MOD : c+MOD;
}

ull a[200005];
int main() {

    ll n, k;
    cin >> n >> k;
    rep(i, n) cin >> a[i];

    rep1(j, k+1)
    {
        ll ans=0;
        rep(i, n-1)
        {
            ll b = a[i] + a[i+1];

            // Instantiation
            ModularExponentiation objMain;

            // Compute Modular Exponentiation
            ll me = objMain.compME(b, j, 998244353);

            ans = m_sum(ans, me);
        }
        cout << ans << endl;
    }

    return 0;
}
