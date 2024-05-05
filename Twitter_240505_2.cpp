// ブリザードマン（@HhG2cL9UOLRSz4I）さん作の問題の解答
// https://x.com/dc1394/status/1787079774688649694
#include <cstdint>   // for std::int32_t
#include <iostream>  // for std::cout, std::endl
#include <regex>     // for std::regex, std::regex_search
#include <string>    // for std::string

namespace {
static auto constexpr N = 2024;
std::vector<std::int32_t> get_answer();
}  // namespace

int main()
{
    auto const answer = get_answer();

    std::cout << "(1) answer = " << answer.size() << std::endl;
    std::cout << "(2) answer = " << answer[answer.size() - N] << std::endl;

    return 0;
}

namespace {
std::vector<std::int32_t> get_answer()
{
    std::vector<std::int32_t> v;
    std::regex const          re(R"((.)\1{1,3})");

    for (auto i = 1000; i <= 9999; i++) {
        auto const str = std::to_string(i);
        if (std::regex_search(str, re)) {
            v.push_back(i);
        }
    }

    return v;
}
}  // namespace