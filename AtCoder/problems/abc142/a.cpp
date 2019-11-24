#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    cin >> n;

    if (n%2==0)
        cout << (double)n/2/n;
    else
        cout << (double)(n/2+1)/n;
    return 0;
}
