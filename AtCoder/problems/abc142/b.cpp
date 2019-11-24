#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n ,k;
    cin >> n >> k;
    int h;
    int ans=0;
    rep(i,n){
        cin >> h;
        if (h>=k)
            ans++;
    }
    cout<<ans;
    return 0;
}
