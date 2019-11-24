#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    cin >> n;

    rep1(i,10)
    {
        if (n%i==0 && n/i < 10)
        {
            cout << "Yes";
            return 0;
        }
    
    }
    cout << "No";
    return 0;
}
