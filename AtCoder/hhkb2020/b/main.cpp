#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

string s[105];
int main() {
    int h,w;
    cin >> h >> w;
    int prev=1; // 散らかってないなら 0;
    int now=1;
    int ans=0;
    rep(i,h)
    {
        cin >> s[i];
    }
    rep(i,h)
    {
        rep1(j,w)
        {
            if(s[i][j-1]=='.'&&s[i][j]=='.')
                ans++;
        }
    }
    rep(j,w)
    {
        rep1(i,h)
        {
            if(s[i-1][j]=='.'&&s[i][j]=='.')
                ans++;
        }
    }
    cout << ans << endl;



    return 0;
}
