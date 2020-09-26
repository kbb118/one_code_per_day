#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

int op(int a, int b) { return max(a,b); }
int e() { return 0;}

int dp[300005];
int main() {
    int n, k;
    cin>>n>>k;
    vector<int> vec;

    for(int i=0; i<n; i++)
    {
        int x;
        cin >> x;
        vec.push_back(x);
    }

    segtree<int, op, e> dp(300005);
    for(int i=0; i<n; i++)
    {
        int x=vec[i];
        int l=x-k, r=x+k+1;
        l=max(0,l); r=min(r,300005);
        int now = dp.prod(l,r)+1;
        dp.set(x, now);
    }
    cout << dp.prod(0, 300005);

    return 0;
}
