#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    cin >> n;

    vector<int> a;
    int input;
    rep(i,n)
    {
        cin >> input;
        a.push_back(input);
    }

    vector<uint64_t> acc(n);
    acc[0] = a[0];
    rep1(i,n)
        acc[i] = a[i] + acc[i-1];

    int i;
    for (i=0;i<n;i++)
    {
        if (acc[i]*2 >= acc[n-1])
            break;
    }

    int64_t shorten = acc[i]*2 - acc[n-1];
    // 全部 1 とかのケース
    if (shorten > acc[i] - (i+1))
        shorten = 99999999999;
    int64_t longthen;
    if (i == 0)
        // 一番目が全体の半分以上長いケース
        longthen = 999999999999;
    else
        longthen = acc[n-1] - acc[i-1]*2;


    cout << min(shorten, longthen);

    return 0;
}
