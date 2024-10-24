#include <cmath>    // for std::log, std::sqrt
#include <cstdint>  // for std::int32_t
#include <iostream> // for std::cout, std::endl
#include <numeric>  // for std::accumulate
#include <vector>   // for std::vector

namespace twitter_240923_2 {
auto constexpr N = 120;
std::int32_t              get_answer();
std::vector<std::int32_t> get_divisors();
}  // namespace twitter_240923_2

int main()
{
    std::cout << "answer = " << twitter_240923_2::get_answer() << std::endl;
}

namespace twitter_240923_2 {
std::int32_t get_answer()
{
    auto const v = get_divisors();
    auto const prod =
        std::accumulate(v.begin(), v.end(), 1.0, [](auto acc, auto i) { return static_cast<double>(acc * i); });

    return static_cast<std::int32_t>(std::log(prod) / std::log(static_cast<double>(N)));
}

std::vector<std::int32_t> get_divisors()
{
    auto const                MAX = static_cast<std::int32_t>(std::sqrt(static_cast<double>(N)));
    std::vector<std::int32_t> v;

    for (auto i = 1; i <= MAX; i++) {
        if (N % i == 0) {
            v.push_back(i);
            v.push_back(N / i);
        }
    }

    return v;
}
}  // namespace twitter_240923_2
