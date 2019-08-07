#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {

    int n,a,b;
    int out=0;
    cin>>n>>a>>b;
    
    
    rep1(i, n+1)
    {
        string s=to_string(i);
        int sum=0;
        rep(j, s.length())
        {
            sum+=s[j]-'0';
        }
        if (sum >= a && sum <= b)
            out+=i;
    }
    
    cout<<out;
    return 0;
}