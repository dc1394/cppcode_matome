// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1765207967778197830
#include <algorithm>  // for std::find_if
#include <array>      // for std::array
#include <cstdint>    // for std::int32_t
#include <iomanip>    // for std::setprecision, std::setiosflags
#include <iostream>   // for std::cout, std::cerr
#include <random>     // for std::random_device, std::mt19937, std::uniform_int_distribution

namespace {
static auto constexpr N = 10000000;
static auto constexpr T = 3;

double get_answer();
double montecarlo();
}  // namespace

int main()
{
    std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
    std::cout << "answer = " << get_answer() << "(%)" << std::endl;

    return 0;
}

namespace {
double get_answer()
{
    return montecarlo();
}

double montecarlo()
{
    std::random_device seed_gen;
    std::mt19937       engine(seed_gen());

    std::uniform_int_distribution<std::int32_t> dist(1, 6);

    auto cnt = 0;

    for (auto i = 0; i < N; i++) {
        std::array<std::int32_t, T> array = {};

        std::int32_t j;
        for (j = 0; j < T; j++) {
            auto const n   = dist(engine);
            auto const itr = std::find_if(array.begin(), array.end(), [n](int element) { return element >= n; });
            if (itr != array.end()) {
                break;
            }

            array[j] = n;
        }

        if (j != T) {
            continue;
        }

        cnt++;
    }

    return static_cast<double>(cnt) / static_cast<double>(N) * 100.0;
}
}  // namespace