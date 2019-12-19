#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    cin >> n;
    int r[n];
    rep(i,n) cin >> r[i];

    int minv=r[0];    
    int maxv=INT_MIN;
    rep1(i,n){
        maxv = max(maxv, r[i]-minv);
        minv = min(minv, r[i]);
    }
    cout << maxv;
    cout << endl;
    return 0;
}
