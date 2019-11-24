#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)

int main() {
    string s;
    cin >>s;
    if (s=="Sunny")
        cout << "Cloudy";
    else if (s=="Rainy")
        cout << "Sunny";
    else if (s=="Cloudy")
        cout << "Rainy";

    return 0;
}
