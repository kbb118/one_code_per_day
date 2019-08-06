#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    std::string s;
    std::cin >> s;

    int cnt = 0;

    for (size_t i = 0; i < 3; i++)
    {
        if (s[i] == '1')
            cnt++;
    }
    
    std::cout << cnt;

    return 0;
}