#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    string s;
    cin >> s;
    // i=0 が一文字目であることに注意
    rep(i, s.size())
    {
        if (i%2==0){
            if (s[i] == 'L')
            {
                cout << "No";
                return 0;
            }
        }
        else{
            if (s[i] == 'R')
            {
                cout << "No";
                return 0;
            }
        }
    }
    
    cout << "Yes";

    return 0;
}
