// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1767810036581978492
#include <algorithm>  // for std::shuffle, std::transform
#include <cassert>    // for assert
#include <cstdint>    // for std::int32_t
#include <iomanip>    // for std::setiosflags, std::setprecision
#include <iostream>   // for std::cout, std::cerr
#include <random>     // for std::random_device, std::mt19937
#include <vector>     // for std::vector

namespace {
static auto constexpr N            = 10000000;
static std::vector<char> const vec = {'A', 'B', 'C', 'D'};

double get_answer();
}  // namespace

int main()
{
    std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
    std::cout << "answer = " << get_answer() << std::endl;
}

namespace {
double get_answer()
{
    std::random_device seed_gen;
    std::mt19937       engine(seed_gen());

    auto cnt = 0;

    for (auto i = 0; i < N; i++) {
        std::vector<char> v(vec);
        std::shuffle(v.begin(), v.end(), engine);

        auto const len = vec.size();
        assert(len == v.size());

        std::vector<bool> result;
        result.reserve(len);

        std::transform(vec.begin(), vec.end(), v.begin(), result.begin(), [](auto a, auto b) { return a == b; });

        auto j = 0;
        for (j = 0; j < len; j++) {
            if (result[j] == true) {
                break;
            }
        }

        if (j == len) {
            cnt++;
        }
    }

    return static_cast<double>(cnt) / static_cast<double>(N) * 100.0;
}
}  // namespace
