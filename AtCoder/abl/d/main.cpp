#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

int main() {
    int n, k;
    cin>>n>>k;
    vector<int> vec;
    fenwick_tree<int> fw(n-1);

    for(int i=0; i<n; i++)
    {
        int x;
        cin >> x;
        vec.push_back(x);
        if ( i>=1 )
            fw.add(i-1, vec.at(i)-vec.at(i-1));
    }

    int ans = 0;
    int end = 0;

    int i=0;
    int j=0;
    while ( j<n-1 )
    {
        if( fabs(fw.sum(i,j)) <= k )
        {
            ans++;
            j++;
            i=j;
        }
        else
            j++;
    }
    cout << ans << endl;

    return 0;
}
