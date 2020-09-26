#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {

    string s,t, u;
    int a,b;
    cin >> s >> t;
    cin >> a >> b;

    cin >> u;

    if ( u==s )
        a--;
    else
        b--;

    cout << a << " " << b;

    return 0;
}
