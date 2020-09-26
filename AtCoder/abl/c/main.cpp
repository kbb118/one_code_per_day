#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

int main() {
    int n,m;
    cin >> n >> m;
 
    dsu d(n);
    for (int i=0; i<m; i++)
    {
        int a,b;
        cin >> a >> b;
        d.merge(a-1,b-1);
    }
    cout << d.groups().size()-1 << endl;


    return 0;
}
