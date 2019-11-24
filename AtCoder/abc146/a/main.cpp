#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    string s;
    cin >> s;
    int a;
    if (s=="SUN")
        a=7;
    if (s=="MON")
        a=6;
    if (s=="TUE")
        a=5;
    if (s=="WED")
        a=4;
    if (s=="THU")
        a=3;
    if (s=="FRI")
        a=2;
    if (s=="SAT")
        a=1;
        
    cout << a;

    return 0;
}
