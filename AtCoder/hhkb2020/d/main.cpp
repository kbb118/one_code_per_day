#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

typedef unsigned long long int ull;
#define P 1000000007
int main() {
    int t;
    cin >> t;

    rep(i,t)
    {
        ull n,a,b;
        cin >> n>>a>>b;

        ull x = (n-a+1)*(n-a+1)%P;
        x *= (n-b+1)*(n-b+1)%P;
        ull y = ((n-a+1)*(n-a+1)%P)*((a+b-1)*(a+b-1)%P)%P;
        
        // 引きすぎた分足し戻す

        cout << ((x<y) ? P + (x-y) : x-y ) << endl;
    }

    return 0;
}
