#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_11_A&lang=ja
//

static const int N = 100;

int main() {
    int M[N][N];
    int n, u, k, v;

    cin >> n;

    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < n; j++ )
            M[i][j] = 0;
    }

    for ( int i = 0; i < n; i++ )
    {
        cin >> u >> k;
        u--; // 1 origin to 0 origin
        for ( int j = 0; j < k; j++ )
        {
            cin >> v;
            v--; // 1 origin to 0 origin
            M[u][v] = 1;
        }
    }

    for ( int i = 0; i < n; i++ )
    {
        for ( int j = 0; j < n; j++ )
            cout << M[i][j];
        cout << endl;
    }

    return 0;
}
