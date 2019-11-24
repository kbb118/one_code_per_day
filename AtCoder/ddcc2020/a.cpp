#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int x;
    int y;

    int m = 0;

    cin >> x >> y;

    if (x == 1)
        m += 300000;
    else if (x == 2)
        m += 200000;
    else if (x == 3)
        m += 100000;

    if (y == 1)
        m += 300000;
    else if (y == 2)
        m += 200000;
    else if (y == 3)
        m += 100000;

    if (x == 1 && y == 1)
    {
        m += 400000;
    }

    cout << m;

    return 0;
}
