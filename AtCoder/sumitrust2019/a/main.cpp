#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int m1,d1,m2,d2;
    cin >> m1 >> d1;
    cin >> m2 >> d2;
    if (m1+1 == m2)
        cout << '1';
    else if ( m1==12 && m2==1)
        cout << '1';
    else
        cout << '0';

    return 0;
}
