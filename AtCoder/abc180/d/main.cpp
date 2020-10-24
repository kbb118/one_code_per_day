#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

typedef unsigned long long int ull;
typedef long long int ll;


ull A;
ull B;
ull X;
ull Y;

int main() {
    cin >> X>>Y>>A>>B;

    ll st = X;
    ll ans=0;

    // b 超えるまで a 倍

    while (1)
    {
        if ( B < A )
            break;

        if ( st*A < A || st*A < st )
            break;

        if ( st*A - st > B )
            break;

        if ( st*A >= Y )
            break;

        st *= A;
        ans++;
    }

    // b ばっかり
    // X + n*B <= Y

    ull b_n = (Y-(st))/B;
    if ( (Y-st)%B==0 )
        b_n--;

    cout << ans + b_n << endl;
    return 0;



    return 0;
}
