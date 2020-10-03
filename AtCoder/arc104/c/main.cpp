#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int Fill[205];
int main() {
    int n;
    int on[205];
    int off[205];
    cin >> n;
    rep(i,n)
    {
        cin >> on[i] >> off[i];
        if ( off[i]!=-1 && on[i]!=-1 &&
             (off[i] <= on[i] || n < off[i]-on[i]) )
        {
            cout << "No" << endl;
            return 0;
        }
        if (off[i]!=-1)
            Fill[off[i]]=1;
        if (on[i]!=-1)
            Fill[on[i]]=1;
    }

    rep(i,n)
    {
        rep(j,n)
        {
            if (j==i)
                continue;
            if ( off[i]!=-1 && on[i]!=-1 &&
                 off[j]!=-1 && on[j]!=-1 &&
                ( on[i]==off[j] || on[j]==off[i] ||
                  on[i]==on[j] || off[j]==off[i] ) )
            {
                cout << "No" << endl;
                return 0;
            }
            if ( off[i]!=-1 && on[i]!=-1 &&
                 off[j]!=-1 && on[j]!=-1 &&
                ( on[i]<on[j] && off[j]<off[i] ) )
            {
                cout << "No" << endl;
                return 0;
            }
        }
    }

    // 空きが無い場合がある
    rep(i,n)
    {
        if (on[i] == -1)
        {
            int j=1;
            for(j=1; j<=2*n+1; j++)
            {
                if (!Fill[j])
                    break;
            }
            if (j==2*n+1)
                goto NON;
            on[i]=j;
            Fill[j]=1;
        }
        if (off[i] == -1)
        {
            int j=1;
            for(j=on[i]+1; j<=2*n+1; j++)
            {
                if (!Fill[j])
                    break;
            }
            if (j==2*n+1)
                goto NON;
            off[i]=j;
            Fill[j]=1;
        }
        if (off[i] <= on[i] || n < off[i]-on[i])
            goto NON;
    }

    cout << "Yes" << endl;
    return 0;
NON:
    cout << "No" << endl;
    return 0;
}
