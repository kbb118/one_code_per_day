#include <vector>
#include <algorithm>
#include <queue>

#include <cstdio>
#include <climits>

typedef long long int LL;
#define rep(I, INIT, N) for(LL (I)=(INIT); (I)<(N); (I)++)
#define rep0(I, N) rep(I, 0, N)

template<class T>bool chmax(T &a, const T &b){return a<b ? (a=b,1):0;}
template<class T>bool chmin(T &a, const T &b){return a>b ? (a=b,1):0;}

typedef LL Vid;  // 頂点番号
typedef LL Cost; // 重み
struct Edge {
    Vid  to; // 辺の終点の頂点番号
    Cost c;  // 辺の重み
    Edge(Vid t, Cost c): to(t), c(c) {}
};
typedef std::vector<std::vector<Edge>> Graph;

const Cost Inf = LLONG_MAX;

std::vector<std::vector<Cost>> warshall_floyd(Graph &g) {

    // dp table 初期化
    std::vector<std::vector<Cost>> dp;
    rep0(i, g.size())
    {
        dp.push_back(std::vector<Cost>());
        // i,j 間に辺がなければ Inf
        dp[i].assign(g.size(), Inf);
        // あればその重み
        for(auto e: g[i])
            dp[i][e.to] = e.c;
        // i==jは0
        dp[i][i] = 0;
    }

    rep0(k, g.size())
        rep0(i, g.size())
            rep0(j, g.size())
                if(dp[i][k] != Inf && dp[k][j] != Inf)
                    chmin(dp[i][j], dp[i][k]+dp[k][j]);
    return dp;
}

Graph build_graph (LL n_vertices) {
    Graph g(n_vertices);
    rep0(i, n_vertices)
    {
        Vid from;
        LL  n_edges;
        scanf("%lld %lld", &from, &n_edges);

        rep0(j, n_edges)
        {
            Vid  to;
            Cost c;
            scanf("%lld %lld", &to, &c);

            g[from].push_back(Edge(to, c));
        }
    }
    return g;
}

int main(void) {
    LL n_vertices;
    scanf("%lld", &n_vertices);

    auto g = build_graph(n_vertices);

    auto answer = warshall_floyd(g);

    // output
    for (LL i = 0; i < answer.size(); ++i) {
        printf("%lld %lld\n", i, answer.at(0).at(i));
    }
    return 0;
}
