#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    char s[5005];
    cin >> n;
    int A[5005];
    int T[5005];
    int C[5005];
    int G[5005];
    int a,t,c,g,ans;
    a=t=c=g=ans=0;
    rep(i, n){
        char s;
        cin >> s;
        A[i] = a;
        T[i] = t;
        C[i] = c;
        G[i] = g;
        if ( s == 'A' )
            ++a;
        if ( s == 'T' )
            ++t;
        if ( s == 'C' )
            ++c;
        if ( s == 'G' )
            ++g;
    }
    A[n] = a;
    T[n] = t;
    C[n] = c;
    G[n] = g;

    int w=2;
    while (w<=n)
    {
        for(int i=0; i<=n-w; i++)
        {
            if ( A[i+w]-A[i]==T[i+w]-T[i] &&
                 C[i+w]-C[i]==G[i+w]-G[i] )
                ans++;
        }
        w+=2;
    }

    cout << ans << endl;



    return 0;
}
