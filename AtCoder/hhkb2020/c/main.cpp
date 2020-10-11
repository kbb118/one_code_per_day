#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int p[200005];
int ex[200005];
int main() {
    int n;
    cin>>n;
    rep(i,n) cin>>p[i];
    int last_idx=0;
    rep(i,n)
    {
        ex[p[i]]=1;
        for(int j=last_idx; j<200005; j++)
        {
            if(!ex[j])
            {
                cout<<j<<endl;
                last_idx=j;
                break;
            }
        }
    }

    return 0;
}
