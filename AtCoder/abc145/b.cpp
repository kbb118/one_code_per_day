#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    string s;
    cin >> n;
    cin >> s;

    if ( n%2 != 0){
        cout << "No";
        return 0;
    }

    if (n==2 && s[0] != s[1]){
        cout << "No";
        return 0;
    }

        
    rep(i, n/2-1){
        if ( s[i] != s[i + n/2]){
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";

    return 0;
}
