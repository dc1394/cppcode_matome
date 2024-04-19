// れおまる（@reomaru_1103）さん作の問題の解答
// https://twitter.com/dc1394/status/1764844324624466075
#include <cstdint>   // for std::int32_t
#include <iostream>  // for std::cout, std::endl
#include <optional>  // for std::optional
#include <string>    // for std::string, std::to_string

namespace {
static auto constexpr N = 10000;
static auto constexpr M = 999;

std::optional<std::int32_t> get_answer();
}  // namespace

int main()
{
    if (auto const answer = get_answer()) {
        std::cout << "answer = " << *answer << std::endl;
    }

    return 0;
}

namespace {
std::optional<std::int32_t> get_answer()
{
    auto cnt = 1;
    for (auto i = 1; i < N; i++) {
        auto const str  = std::to_string(i);
        auto const chk  = str.find("4");
        auto const chk2 = str.find("9");

        if (chk != std::string::npos || chk2 != std::string::npos) {
            continue;
        }

        if (cnt == M) {
            return std::make_optional(i);
        }

        cnt++;
    }

    return std::nullopt;
}
}  // namespace