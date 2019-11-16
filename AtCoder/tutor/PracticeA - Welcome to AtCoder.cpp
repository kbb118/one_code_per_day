#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    int a;
    int b;
    int c;
    std::string s;

    std::cin >> a;
    std::cin >> b >> c;
    std::cin >> s;

    std::cout << a+b+c;
    // 末尾に改行入れること! というか問題の注意事項をよく読むこと。
    std::cout << " " + s + "\n";

    return 0;
}
