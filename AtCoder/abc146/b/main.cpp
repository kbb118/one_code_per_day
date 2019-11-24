#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    int n;
    string s;
    cin >> n;
    cin >> s;

    char table[52];
    char c='A';
    for(int i=0;i<26;i++)
    {
        table[i]=c;
        c++;
    }
    c='A';
    for(int i=26;i<52;i++)
    {
        table[i]=c;
        c++;
    }

    rep(i,s.size())
    {
        s[i] = table[s[i] - 'A'+n];
    }
    cout << s;

    return 0;
}
