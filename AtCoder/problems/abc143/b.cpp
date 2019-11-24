#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    cin >> n;
    int d[n];
    rep(i,n) cin >> d[i];

    int sum=0;
    rep(i,n-1){
        for(int k=i+1;k<n;k++)
            sum += d[i]*d[k];
    }

    cout<<sum;

    return 0;
}
