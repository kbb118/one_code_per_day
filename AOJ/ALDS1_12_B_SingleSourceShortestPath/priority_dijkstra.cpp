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

std::vector<Cost> dijkstra(Graph &g, Vid start) {
    std::vector<Cost> d;
    d.assign(g.size(), Inf);
    d.at(start) = 0;

    // 頂点番号と、そこへの最短経路の長さのペア
    typedef std::pair<Cost, Vid> Pair;
    std::priority_queue<Pair> que;
    que.push(Pair(0, start));

    // 最短経路木に v が含まれているか。
    std::vector<bool> s;
    s.assign(g.size(), false);
    LL s_size = 0;

    while (s_size != g.size()) {
        // G-S なvのうちコスト最小なvを得る
        Vid  min_v = que.top().second;
        que.pop();

        // Sに追加済みのゴミがqueに残るので飛ばす
        if (s.at(min_v) == true)
            continue;

        // v を S に追加
        s.at(min_v) = true;
        s_size++;

        // 緩和
        for(auto v: g[min_v])
        {
            if(chmin(d[v.to], d[min_v]+v.c))
            {
                // priority_que の仕様でデフォルト降順なのでマイナスつける
                que.push(Pair(-d[v.to], v.to));
            }
        }
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
