#include <algorithm>  // for std::copy, std::fill_n, std::find_if
#include <array>      // for std::array
#include <cstdint>    // for std::int32_t
#include <iostream>   // for std::cout, std::endl
#include <string>     // for std::string
#include <vector>     // for std::vector

namespace {
static auto constexpr N = 5;
static auto constexpr M = 3;

bool                                    check(std::array<char, N> const & s);
std::vector<std::array<std::string, M>> get_answer();
std::array<char, N>                     treat(std::int32_t i);
}  // namespace

int main()
{
    auto const answer = get_answer();
    for (auto const & elem : answer) {
        std::cout << '(';
        for (auto i = 0; i < M - 1; i++) {
            std::cout << '{' << elem[i] << "},";
        }
        std::cout << '{' << elem[M - 1] << "}), ";
    }
    std::cout << '\n';

    std::cout << "全" << answer.size() << "通り" << std::endl;
}

namespace {
bool check(std::array<char, N> const & s)
{
    auto const result = std::find_if(s.begin(), s.end(), [](auto c) { return c >= (M + '0'); });
    return result == s.end();
}

std::vector<std::array<std::string, M>> get_answer()
{
    std::vector<std::array<char, N>> v;

    auto digit = 1;
    auto max   = 0;
    for (auto i = 0; i < N; i++) {
        max += digit * (M - 1);
        digit *= 10;
    }

    for (auto i = 0; i <= max; i++) {
        auto const s = treat(i);
        if (check(s)) {
            v.push_back(s);
        }
    }

    std::vector<std::array<std::string, M>> res;
    for (auto const & elem : v) {
        std::array<std::string, M> ary;
        std::fill_n(ary.begin(), M, std::string(""));

        for (auto i = 0; i < N; i++) {
            auto const c = elem[i] - '0';
            ary[c] += 'A' + i;
        }

        res.push_back(ary);
    }

    return res;
}

std::array<char, N> treat(std::int32_t i)
{
    auto str = std::to_string(i);
    while (str.length() != N) {
        str = "0" + str;
    }

    std::array<char, N> ary;
    std::copy(str.begin(), str.end(), ary.begin());

    return ary;
}
}  // namespace