#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int a[200000];
int main() {

    int n;
    cin >> n;
    rep(i, n)
        cin >> a[i];

    std::qsort(a, n, sizeof(int),
            [](const void* a, const void* b){
                int x = *(int*)a;
                int y = *(int*)b;

                if (x<y) return -1;
                if (y<x) return 1;
                return 0;
            }
            );

    for ( int i=1; i<n; i++)
    {
        if (a[i-1] == a[i])
        {
            cout<< "NO";
            return 0;
        }

    }
    cout<< "YES";
    
    return 0;
}
