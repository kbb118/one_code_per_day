#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    vector<int> d;
    cin>>n;
    rep(i, n){ 
        int tmp;
        cin>>tmp;
        d.push_back(tmp);
    }
    
    sort(d.begin(), d.end());
    auto last = unique(d.begin(), d.end());
    d.erase(last, d.end());
    cout<<d.size();
    return 0;
}