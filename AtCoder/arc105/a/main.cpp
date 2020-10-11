#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

typedef unsigned long long int ull;
int main() {

    ull a,b,c,d;
    cin >> a>>b>>c>>d;

    if( a == b+c+d ||
        b == a+c+d ||
        c == a+b+d ||
        d == a+b+c ||
        a+b == c+d ||
        a+c == b+d ||
        a+d == b+c )
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}
