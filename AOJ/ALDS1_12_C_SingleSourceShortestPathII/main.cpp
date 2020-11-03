#include <bits/stdc++.h>
#include <queue>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

typedef unsigned long long int ull;
typedef long long int ll;

#define N 10000

struct Edge {
    ll to;
    ll cost;
    Edge(ll to, ll cost) : to(to), cost(cost) {}
};
using Graph = vector<vector<Edge>>;

#define INF LLONG_MAX

// Adjacency List
Graph G(N);

// 最短経路木内の頂点のみを通って頂点iに行くときの最短コスト
ll d[N];

int main() {

    // init
    ll n; cin >> n;
    rep(i, n) {
        d[i]=INF;
        ll u, k; cin >> u >> k;
        rep(j,k) {
            ll c,v; cin >> v >> c;
            G[u].push_back(Edge(v,c));
        }
    }

    // 問題より、始点は 0 なので
    ll start=0;
    d[start]=0;

    using Pair = pair<ll,ll>;
    priority_queue<Pair,
                   vector<Pair>,
                   greater<Pair>> que;
    que.push(Pair(d[start], start));

    while(!que.empty())
    {
        // V-S な頂点のうちコスト最小な頂点を求める
        auto p = que.top();
        que.pop();
        ll min_cost = p.first;
        ll min_i = p.second;

        // que 内のゴミ
        if (min_cost > d[min_i])
            continue;

        // d 更新
        for( auto v: G[min_i] )
        {
            if(d[v.to] > d[min_i]+v.cost)
            {
                d[v.to] = min(d[v.to], d[min_i] + v.cost);
                que.push(Pair(d[v.to], v.to));
            }
        }
    }

    rep(i, n)
        cout << i << " " << d[i] << endl;

    return 0;
}
