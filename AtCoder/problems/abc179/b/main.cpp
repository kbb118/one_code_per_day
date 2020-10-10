#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int A[105];
int B[105];
int main() {
    int n;
    cin >> n;
    rep(i,n) cin >> A[i] >> B[i];
    for(int i=2; i<n; i++)
    {
        if( A[i-2]==B[i-2] &&
            A[i-1]==B[i-1] &&
            A[i]==B[i] )
        {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;
    return 0;
}
