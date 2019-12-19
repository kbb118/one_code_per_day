#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int q(string x,int a,int b,int c)
{
    return 100*(x[a]-'0') + 10*(x[b]-'0') + (x[c]-'0');
}

int main() {
    int n;
    string str;
    cin >> n;
    cin >> str;

    int ans[1000];
    rep(i,1000) ans[i] = 0;

    int as[10];rep(i,10) as[i]=0;
    int bs[100];rep(i,100) bs[i]=0;
    for ( int a=0; a<n-2 ; a++)
    {
        if ( as[str[a]-'0'] == 1)
            continue;
        for ( int b=a+1; b<n-1 ; b++)
        {
            if ( bs[10*(str[a]-'0')+(str[b]-'0')] == 1)
                continue;

            int cs[10]; rep(i,10) cs[i] = 0;
            for ( int c=b+1; c<n ; c++)
            {
                rep(i,10){
                    if (cs[i]==0)
                        goto C;
                }
                break;
C:
                cs[str[b]-'0']=1;
                ans[q(str,a,b,c)] = 1;
            }
            bs[10*(str[a]-'0')+(str[b]-'0')] = 1;
        }
        as[str[a]-'0'] = 1;
    }

    int a=0;
    rep(i,1000){
        if (ans[i]==1)
            a++;
    }
    cout << a;
    return 0;
}
