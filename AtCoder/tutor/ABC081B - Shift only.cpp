#include <iostream>
#include <string>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    int n;
    int a[200];
    int min = 999999999;
    std::cin >> n;
    std::cin.ignore();
    std::string s;
    for (size_t i = 0; i < n; i++)
    {
        int cnt = 0;
        if (i == n-1)
            std::getline(std::cin, s, '\n');
        else
            std::getline(std::cin, s, ' ');

        a[i] = atoi(s.c_str());
        while (a[i]!=0 && a[i]%2==0)
        {
            a[i]/=2;
            cnt++;
        }

        if (cnt < min)
            min = cnt;
    }
    
    std::cout << min;

    return 0;
}