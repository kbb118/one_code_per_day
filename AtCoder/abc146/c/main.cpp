#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    long long a, b, x;
    cin >> a >> b >> x;
    //a*n + b*((n%10)+1)
    if (x < a + b)
    {
        cout << 0;
        return 0;
    }

    // これよりは小さいはず。
    long long max = x/a +1;

    long long xxx = 1000000000;
    if (x >= a*xxx + b*(long long)(log10(xxx)+1))
    {
        cout << xxx;
        return 0;
    }

    while(x < a*max + b*(long long)(log10(max)+1))
    {
        max/=10;    
    }
    while(x >= a*max + b*(long long)(log10(max)+1))
    {
        max+=100;    
    }
    while(x < a*max + b*(long long)(log10(max)+1))
    {
        max--;    
    }
    if (max<0)
        max=0;
        
    cout << max;

    return 0;
}
