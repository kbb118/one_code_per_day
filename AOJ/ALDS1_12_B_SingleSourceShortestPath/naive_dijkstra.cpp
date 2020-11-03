#include <vector>
#include <algorithm>

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

std::vector<Cost> dijkstra(Graph &g, Vid start) {
    std::vector<Cost> d;
    d.assign(g.size(), Inf);
    d.at(start) = 0;

    std::vector<bool> s; // s==G までループ
    s.assign(g.size(), false);
    LL s_size = 0;

    while (s_size != g.size()) {
        // G-S なvのうちコスト最小なvを探す
        //  (ここに O(n_vertices) かかる)
        Cost min    = Inf;
        Vid  min_v = LLONG_MAX;
        rep0(i, g.size())
        {
            if(s.at(i) == true)
                continue;
            else if(chmin(min, d.at(i)))
                min_v = i;
        }

        // Sに追加 & 緩和
        s.at(min_v) = 1;
        s_size++;
        for(auto v: g[min_v])
            chmin(d[v.to], d[min_v]+v.c);
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

    auto answer = dijkstra(g, 0);

    // output
    for (LL i = 0; i < answer.size(); ++i) {
        printf("%lld %lld\n", i, answer.at(i));
    }
    return 0;
}
