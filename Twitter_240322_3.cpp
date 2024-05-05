#include <boost/multiprecision/cpp_int.hpp> // for boost::multiprecision
#include <cstdint>                          // for std::int32_t
#include <iostream>                         // for std::cout, std::endl
#include <string>                           // for std::string

namespace {
namespace mp = boost::multiprecision;

static auto constexpr N = 1999;

std::int32_t get_answer();
}

int main()
{
    std::cout << "answer = " << get_answer() << std::endl;
    return 0;
}

namespace {
std::int32_t get_answer()
{
    mp::cpp_int num = 1;
    for (auto i = 0; i < N; i++) {
        num *= N;
    }

    auto const result = mp::to_string(num);

    return std::stoi(result[result.length() - 2] + std::string("\0"));
}
}