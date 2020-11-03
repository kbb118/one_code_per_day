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

std::vector<Cost> bellman_ford(Graph &g, Vid start) {
    std::vector<Cost> d;
    d.assign(g.size(), Inf);
    d.at(start) = 0;

    // |V| 回 各 E について緩和を行う
    // |V| 回目に更新が行われた場合は負閉路が存在する
    rep0(i, g.size())
    {
        bool updated = false;
        rep0(v, g.size())
        {
            // Inf から緩和する意味がないどころか有害
            if(d[v] == Inf)
                continue;

            // 緩和
            for(auto e: g[v])
            {
                if(chmin(d[e.to], d[v]+e.c))
                    updated = true;
            }
        }
        if(updated == false)
            break;
        else if(i == g.size()-1)
            return std::vector<Cost>(0);
    }
    return d;
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

    auto answer = bellman_ford(g, 0);

    // output
    for (LL i = 0; i < answer.size(); ++i) {
        printf("%lld %lld\n", i, answer.at(i));
    }
    return 0;
}
