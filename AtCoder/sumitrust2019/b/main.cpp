#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    cin >> n;

    int x = n/1.08;

    if ( (int)x*1.08 == n)
        cout << x;
    else if ( (int)((x+1)*1.08) == n)
        cout << x+1;
    else
        cout << ":(";

    return 0;
}
