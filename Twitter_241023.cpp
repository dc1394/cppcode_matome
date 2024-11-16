// 清水　団 Dan Shimizu（@dannchu）さんのJuliaによる問題解答のC++版
// https://x.com/dc1394/status/1849005000887824707
// コンパイルに-std=c++20指定が必要
#include <algorithm>  // for std::next_permutation, std::sort, std::unique
#include <cstdint>    // for std::int32_t
#include <format>     // for std::format
#include <iostream>   // for std::cout, std::endl
#include <random>     // for std::mt19937, std::uniform_int_distribution
#include <vector>     // for std::vector

namespace {
using myvec                       = std::vector<std::int32_t>;
static const myvec    v           = {1, 1, 2, 3};
static constexpr auto N           = 10000000;
static constexpr auto VECTOR_SIZE = 4;
static constexpr auto SUBSET_SIZE = 2;
static constexpr auto BASE        = 10;

class MyRand final
{
    std::uniform_int_distribution<> dist_;
    std::mt19937                    engine_;

public:
    explicit MyRand(std::uniform_int_distribution<> const & dist) : dist_(dist)
    {
        #ifdef TEST
            engine_ = std::mt19937(42);
        #else
            std::random_device seed_gen;
            engine_ = std::mt19937(seed_gen());
        #endif
    }

    std::int32_t rand()
    {
        return dist_(engine_);
    }
};

std::int32_t get_answer();
double       get_answer2();
}  // namespace

int main()
{
    std::cout << std::format("(1) {}\n(2) {:.7f}\n", get_answer(), get_answer2());
    return 0;
}

namespace {
std::int32_t get_answer()
{
    std::vector<myvec> vec;
    vec.reserve(VECTOR_SIZE * (VECTOR_SIZE - 1) / 2);  // 予想される最大サイズで予約

    myvec temp = v;
    do {
        vec.push_back(myvec(temp.begin(), temp.begin() + SUBSET_SIZE));
    } while (std::next_permutation(temp.begin(), temp.end()));

    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    return static_cast<std::int32_t>(vec.size());
}

double get_answer2()
{
    std::uniform_int_distribution<> dist(0, VECTOR_SIZE - 1);
    MyRand                          mr(dist);
    auto                            cnt = 0;

    for (auto i = 0; i < N; ++i) {
        auto const n = BASE * v[mr.rand()] + v[mr.rand()];
        if (n % 2 == 0) {
            cnt++;
        }
    }
    return static_cast<double>(cnt) / static_cast<double>(N);
}
}  // namespace