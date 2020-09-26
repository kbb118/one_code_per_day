#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

double sigma(int n)
{
    return (n+1)*n/2.0;
}

int p[200000];
int main() {
    int n, k;
    cin >> n >> k;

    int max = -1;
    int sum = 0;
    rep(i, n)
    {
        cin >> p[i];

        sum += p[i]+1;
        if ( i >= k )
            sum -= p[i-k]+1;

        if ( sum > max )
            max = sum;
    }

    cout << setprecision(15) << max/2.0;

    return 0;
}
