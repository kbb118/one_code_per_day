#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    string s;
    cin >> s;
    int n = s.size();
    if ( s[n-1]=='s' )
        cout << s << "es" << endl;
    else
        cout << s << "s" << endl;

    return 0;
}
