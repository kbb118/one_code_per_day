#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    string s,t;
    cin>>s;
    cin>>t;

    if(s=="N")
    {
        cout << t << endl;
    }
    else
    {
        rep(i,s.size())
        {
            if(t[i]=='a')
                cout << 'A';
            if(t[i]=='b')
                cout << 'B';
            if(t[i]=='c')
                cout << 'C';
        }
        cout << endl;
    }

    return 0;
}
