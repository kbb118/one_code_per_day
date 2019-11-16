#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

uint64_t fact(uint64_t n){
    uint64_t ret=1;
    for(uint64_t i=2; i<n+1;i++){
        ret *= i;
        if (ret > 1000*1000*1000){
            ret %= 1000*1000*1000 + 7;
        }
    }
    return ret;
}

int main() {
    int x;
    int y;
    int a; 
    int b; 
    int kotae;
    cin >> x >> y ;

    if ((2*x-y)%3!=0 || (2*y-x)%3!=0){
        kotae = 0;
    } else {
        a = (2*y-x)/3;
        b = (2*x-y)/3;


        kotae = fact(a+b)/(fact(a)*fact(b));
        for (int i=a+b; i<b; i--){
        
        }
    }

    cout << kotae;
    return 0;
}
