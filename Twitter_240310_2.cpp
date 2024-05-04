// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1766712060350722556
#include <array>     // for std::array
#include <cstdint>   // for std::int32_t
#include <iomanip>   // for std::setiosflags, std::setprecision
#include <iostream>  // for std::cout, std::cerr
#include <random>    // for std::random_device, std::mt19937, std::uniform_int_distribution

namespace {
static auto constexpr N = 20000000;

double get_answer();
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
    #ifdef TEST
        std::mt19937 engine(42);
    #else
        std::random_device seed_gen;
        std::mt19937 engine(seed_gen());
    #endif

    std::uniform_int_distribution<std::int32_t> dist(1, 6);

    auto cnt = 0;
    for (auto i = 0; i < N; i++) {
        std::array<std::int32_t, 3> const ar = {dist(engine), dist(engine), dist(engine)};
        if ((ar[0] - ar[1]) * (ar[1] - ar[2]) * (ar[2] - ar[0]) == 0) {
            cnt++;
        }
    }

    return static_cast<double>(cnt) / static_cast<double>(N) * 100.0;
}
}  // namespace