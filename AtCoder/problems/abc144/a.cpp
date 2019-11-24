#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int a,b;
    cin >> a >> b;
    if (a>9 || b>9)
        cout << -1;
    else
        cout << a*b;

    return 0;
}
