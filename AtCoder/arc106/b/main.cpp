#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

typedef unsigned long long int ull;
typedef long long int ll;

ll N[200005];
ll a[200005];
ll b[200005];

ll M[200005][2];

using Graph = vector<vector<int>>;


vector<bool> seen;

ll sum_a=0;
ll sum_b=0;
void comp_sum(const Graph &G, int v) {
    seen[v] = true;
    sum_a+=a[v];
    sum_b+=b[v];
    for (auto next_v : G[v]) { 
        if (seen[next_v]) continue;
        comp_sum(G, next_v); // 再帰的に探索
    }
}

int main() {

    int n, m;
    cin >> n >> m;
    rep(i,n){ cin >> a[i+1]; sum_a+=a[i+1];}
    rep(i,n){ cin >> b[i+1]; sum_b+=b[i+1];}

    if ( sum_a != sum_b )
    {
        cout << "No" << endl;
        return 0;
    }

    rep(i,n)
    {
        if( a[i+1]==b[i+1] )
            continue;
        goto NEXT;
    }
    cout << "Yes" << endl;
    return 0;

NEXT:
    Graph G(n+1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    // 全頂点が訪問済みになるまで探索
    int count = 0;
    seen.assign(n+1, false);
    for (int v = 1; v < n+1; ++v) {
        if (seen[v]) continue; // v が探索済みだったらスルー

        sum_a=0;
        sum_b=0;
        comp_sum(G, v);
        if ( sum_a != sum_b )
        {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}
