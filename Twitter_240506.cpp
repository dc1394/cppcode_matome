// 清水　団 Dan Shimizu（@dannchu）さん作の問題の解答
// https://twitter.com/dc1394/status/1787407228628238840
// コンパイルに-std=c++20指定が必要
#include <algorithm>  // for std::next_permutation, std::sort, std::unique
#include <cassert>    // for assert
#include <cstdint>    // for std::int32_t
#include <iostream>   // for std::cout, std::endl
#include <numeric>    // for std::iota
#include <string>     // for std::u8string
#include <vector>     // for std::vector

namespace {
static auto constexpr N = 10;
static auto constexpr M = 4;
static auto constexpr L = 4;

std::vector<std::u8string> get_answer();
}  // namespace

int main()
{
    auto const answer = get_answer();
    for (auto const & elem : answer) {
        std::cout << reinterpret_cast<char const *>(elem.c_str()) << ' ';
    }

    std::cout << "\n全" << answer.size() << "通り" << std::endl;
}

namespace {
std::vector<std::u8string> get_answer()
{
    std::u8string str = u8"\U0001F535\U0001F535\U0001F535\U0001F535\U0001F534\U0001F534\U0001F534\U0001F7E2\U0001F7E2\U0001F7E0";
    
    assert(N * L == str.size());

    std::vector<std::int32_t> vtmp(N);
    std::iota(vtmp.begin(), vtmp.end(), 0);

    std::vector<std::u8string> v;

    do {
        std::u8string tmp(u8"");
        for (auto i = 0; i < M; i++) {
            tmp += str.substr(L * vtmp[i], L);
        }
        v.push_back(tmp);
    } while (std::next_permutation(vtmp.begin(), vtmp.end()));

    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());

    return v;
}
}  // namespace