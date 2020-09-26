#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

/*
 *
 * A---B
 *   C---D
 *
 *
 *  A---B
 *C---D
 *
 */
int main() {
    unsigned long long int a,b,c,d;
    cin >> a >> b >> c >> d;
    if ( a <= c && c <= b )
        cout << "Yes" << endl;
    else if ( c <= a && a <= d)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}
