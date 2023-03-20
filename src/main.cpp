#include <iostream>
#include <string>
#include <expected>
#include "../include/tryx.hpp"

std::expected<std::string, int> get_a()
{
    return "1"; // can replace with std::unexpected(1) to try error propagation
}

std::expected<std::string, int> get_b()
{
    return "2"; // can replace with std::unexpected(2) to try error propagation
}

std::expected<std::string, int> get_c()
{
    return "3"; // can replace with std::unexpected(3) to try error propagation
}

std::expected<std::string, int> get_d()
{
    return "4"; // can replace with std::unexpected(4) to try error propagation
}

std::expected<std::string, int> get_concatenation()
{
    // TRYX variation 1
    std::string a = TRYX(get_a());

    // TRYX variation 2
    std::string b;
    b = TRYX(get_b());

    // TRYX variation 3
    std::expected<std::string, int> expected_c = get_c();
    std::string c = TRYX(expected_c);

    // TRYX variation 4
    std::expected<std::string, int> expected_d = get_d();
    std::string d;
    d = TRYX(expected_d);

    return a + b + c + d;
}

int main()
{
    std::expected<std::string, int> expected_concatenation = get_concatenation();
    if (expected_concatenation.has_value())
    {
        std::cout << expected_concatenation.value();
    }
    else
    {
        std::cout << "error " + std::to_string(expected_concatenation.error());
    }
    return 0;
}