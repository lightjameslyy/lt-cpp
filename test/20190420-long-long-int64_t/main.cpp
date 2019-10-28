#include <cstdint>
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {

    int64_t n1 = INT64_MAX;
    std::string s1 = std::to_string(n1);

    long long n2 = INT64_MAX;
    std::string s2 = std::to_string(n2);

    std::cout << "n1 : " << s1 << ", n2: " << s2 << std::endl;
}
