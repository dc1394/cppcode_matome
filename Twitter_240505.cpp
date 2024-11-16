// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1786968767937032254
// コンパイルに-std=c++20指定が必要
#include <algorithm>  // for std::shuffle
#include <array>      // for std::array
#include <cstdint>    // for std::int32_t
#include <format>     // for std::format
#include <iostream>   // for std::cout, std::endl
#include <random>     // for std::mt19937, std::random_device, std::uniform_real_distribution

namespace {
static auto constexpr N = 10000000;
class MyRand final
{
    std::mt19937 engine_;

public:
    MyRand();
    std::mt19937 & get_engine()
    {
        return engine_;
    }
    double rand(std::uniform_int_distribution<> & dist)
    {
        return dist(engine_);
    }
};

double get_answer();
}  // namespace

int main()
{
    std::cout << std::format("{:.3}(%)", get_answer() * 100.0) << std::endl;
    return 0;
}

namespace {
MyRand::MyRand()
{
    #ifdef TEST
        engine_ = std::mt19937(42);
    #else
        std::random_device seed_gen;
        engine_ = std::mt19937(seed_gen());
    #endif
}

double get_answer()
{
    std::array<bool, 4> boxA{false, false, false, true};
    std::array<bool, 5> boxB{false, false, false, false, true};

    MyRand                          mr;
    std::uniform_int_distribution<> dist(0, 1);

    auto cnt     = 0;
    auto cnt_all = 0;

    for (auto i = 0; i < N; i++) {
        if (mr.rand(dist)) {
            std::shuffle(boxA.begin(), boxA.end(), mr.get_engine());
            if (boxA[0]) {
                cnt_all++;
            }
        } else {
            std::shuffle(boxB.begin(), boxB.end(), mr.get_engine());
            if (boxB[0]) {
                cnt++;
                cnt_all++;
            }
        }
    }

    return static_cast<double>(cnt) / static_cast<double>(cnt_all);
}
}  // namespace