#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    int a;
    int b;

    std::cin >> a >> b;

    std::string s = (a*b%2==0) ? "Even" : "Odd";
    std::cout << s;

    return 0;
}