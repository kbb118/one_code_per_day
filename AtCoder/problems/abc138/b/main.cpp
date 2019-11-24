#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    cin >> n;
    double sum=0;
    int a;
    rep(i,n){
        cin >> a;
        sum +=1.0/a;
    }
    cout << 1/sum;

    return 0;
}
