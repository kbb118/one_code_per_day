#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

typedef unsigned long long int ull;
typedef long long int ll;

#define M 1000000007
int main() {
    int n;
    cin >> n;
    if (n==1)
        cout << 0 << endl;
    else if (n==2)
        cout << 2 << endl;
    else
    {
        ll ans=1;
        ll one_lack=1;
        ll two_lack=1;
        rep(i, n)
        {
            ans = (ans * 10)%M;
            one_lack = (one_lack * 9)%M;
            two_lack = (two_lack*8)%M;
        }
        ans = ans - one_lack - one_lack;
        if ( ans < 0 )
            ans += M;
        ans += two_lack;
        ans %=M;
        cout << ((ans > 0) ? ans : (ans+M)) << endl;
    }

    return 0;
}
