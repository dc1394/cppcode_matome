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
static auto constexpr N = 5;
static auto constexpr M = 3;

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
    std::u8string const str = u8"父母兄姉妹";
    
    assert(N * M == str.size());
    
    std::vector<std::int32_t> vtmp(N);
    std::iota(vtmp.begin(), vtmp.end(), 0);

    std::vector<std::u8string> v;
    do {
        std::u8string tmp(u8"");
        for (auto i = 0; i < N; i++) {
            tmp += str.substr(M * vtmp[i], M);
        }

        if (tmp.find(u8"父母") != std::u8string::npos || tmp.find(u8"母父") != std::u8string::npos) {
            v.push_back(tmp);
        }
    } while (std::next_permutation(vtmp.begin(), vtmp.end()));

    return v;
}
}  // namespace