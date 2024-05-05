// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1771710220089106943
#include <iomanip>   // for std::setiosflags, std::setprecision
#include <iostream>  // for std::cout, std::cerr
#include <random>    // for std::random_device, std::mt19937, std::uniform_int_distribution

namespace {
static auto constexpr N = 10000000;

double get_answer();
}  // namespace

int main()
{
    std::cout << std::setprecision(1) << std::setiosflags(std::ios::fixed);
    std::cout << "answer = " << get_answer() << "(%)" << std::endl;

    return 0;
}

namespace {
double get_answer()
{
    std::random_device                          seed_gen;
    std::mt19937                                engine(seed_gen());
    std::uniform_int_distribution<std::int32_t> dist(1, 6);

    auto cnt = 0;

    for (auto i = 0; i < N; i++) {
        if (dist(engine) * dist(engine) * dist(engine) >= 100) {
            cnt++;
        }
    }

    return static_cast<double>(cnt) / static_cast<double>(N) * 100.0;
}
}  // namespace