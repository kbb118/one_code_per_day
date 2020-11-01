#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

typedef unsigned long long int ull;
typedef long long int ll;

// Adjacency Matrix
ll G[100][100];

// S 内に頂点iが含まれていたら d[i]=1
ll s[100];

// S 内の頂点のみを通って頂点iに行くときの最短コスト
ll d[100];

int main() {

    // init
    rep(i,100)
    {
        rep(j,100)
            G[i][j]=LLONG_MAX;
        s[i]=0;
        d[i]=LLONG_MAX;
    }

    ll n;
    cin >> n;
    rep(i, n)
    {
        ll u, k;
        cin >> u >> k;
        rep(j,k)
        {
            ll c,v;
            cin >> v >> c;
            G[u][v] = c;
        }
    }

    // 問題より、始点は 0 なので
    ll start=0;
    d[start]=0;

    while(1)
    {
        // V-S な頂点のうちコスト最小な頂点を求める
        ll min_cost=LLONG_MAX;
        ll min_i=LLONG_MAX;
        rep(i, n)
        {
            if(s[i])
                continue;

            if(min_cost > d[i])
            {
                min_cost = d[i];
                min_i = i;
            }
        }
        // S==V となったら終わり
        if(min_cost==LLONG_MAX)
            break;

        // S に追加
        s[min_i]=1;

        // d 更新
        rep(v, n)
        {
            if(G[min_i][v] == LLONG_MAX)
                continue;
            d[v] = min(d[v], d[min_i]+G[min_i][v]);
        }
    }

    rep(i, n)
        cout << i << " " << d[i] << endl;

    return 0;
}
