#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {

    int n;
    cin>>n;
    int a[n];
    rep(i, n) cin>>a[i];
    sort(a, a+n);
    
    int score = 0;
    int start;
    if (n%2==1)
        score+=a[0];
    
    for (int i = n-1; i > 0; i-=2)
    {
        score += a[i] - a[i-1];
    }
    
    cout<<score;
    return 0;
}