#include <stdio.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;
int main(int argc, char** argv)
{
    int n,q;
    cin >> n >> q;
    dsu d(n);
    for(int i=0; i<q; i++)
    {
        int t, u1, u2;
        cin >> t >> u1 >> u2;
        if(t==0)
            d.merge(u1,u2);
        else if( d.same(u1, u2) )
            cout << 1 << endl;
        else
            cout << 0 << endl;
    }

    return 0;
}
