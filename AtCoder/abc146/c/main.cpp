#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

typedef long long ll;

ll a,b,x;
ll cost(ll n){
    return a*n + b*(ll)(log10(n)+1);
}

int main() {
    cin >> a >> b >> x;
    // 1 が買えないケース
    if (x < a + b){
        cout << 0;
        return 0;}
    // 10^9 が買えるケース
    if (x >= a*1e9 + b*10){
        cout << 1000*1000*1000;
        return 0;}

    // 二分探索スタート
    ll max = 1e9/2;
    ll pitch = max/2;
    while(1){
        if (x >= cost(max)){
            max += pitch;
            if (pitch==1 && x < cost(max)){
                max--;
                break;
            }
        }else{
            max -= pitch;
        }
        pitch /= 2;
        if (pitch == 0)
            pitch=1;
    }
        
    cout << max;
    return 0;
}
