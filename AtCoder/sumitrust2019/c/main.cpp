#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int x;
    cin >> x;

    if ( x < 100 )
    {
        cout << '0';
        return 0;
    }

    // m = num1 + num2 + ... num;
    int num = x/100;
    int m = x%100;

    rep(i, num){
        if ( m>=5)
            m-=5;
        else if (m>=4)
            m-=4;
        else if (m>=3)
            m-=3;
        else if (m>=2)
            m-=2;
        else if (m>=1)
            m-=1;
    }
    
    if (m==0)
        cout << '1';
    else
        cout << '0';

    return 0;
}
