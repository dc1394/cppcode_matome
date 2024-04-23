// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://twitter.com/dc1394/status/1781515188493238709
#include <boost/math/constants/constants.hpp>      // for boost::math::constants::pi
#include <cmath>     // for std::fabs, std::round, std::sqrt
#include <cstdint>   // for std::int32_t
#include <iostream>  // for std::cout, std::endl
#include <optional>  // for std::make_optional, std::optional
#include <random>    // for std::mt19937, std::random_device, std::uniform_real_distribution
#include <utility>   // for std::make_pair, std::pair

namespace {
static auto const A         = std::sqrt(360.0);
static auto const B         = std::sqrt(60.0);
static auto constexpr N     = 1000000;
static auto constexpr DELTA = 1.0E-5;
static auto constexpr EPS   = 1.0E-15;

bool                                                 check(double x);
std::int32_t                                         my_doubletoint(double x);
std::optional<std::pair<std::int32_t, std::int32_t>> get_answer();
}  // namespace

int main()
{
    if (auto const answer = get_answer()) {
        auto const [p, q] = *answer;
        std::cout << "p = " << p << ", q = " << q << std::endl;
    }
}

namespace {
bool check(double x)
{
    return std::fabs(std::round(x) - x) < DELTA;
}

std::int32_t my_doubletoint(double x)
{
    auto const tmp  = std::round(x);
    auto       tmp2 = static_cast<std::int32_t>(tmp);
    if (std::fabs(tmp - static_cast<double>(tmp2) - 1.0) < EPS) {
        tmp2++;
    } else if (std::fabs(tmp - static_cast<double>(tmp2) + 1.0) < EPS) {
        tmp2--;
    }

    return tmp2;
}

std::optional<std::pair<std::int32_t, std::int32_t>> get_answer()
{
    #ifdef TEST
        std::random_device seed_gen;
        std::mt19937 engine(seed_gen());
    #else
        std::mt19937 engine(42);
    #endif

    std::uniform_real_distribution<double> dist(0.0, boost::math::constants::pi<double>() * 0.5);

    for (auto i = 0; i < N; i++) {
        auto const theta = dist(engine);
        auto const a = A * std::cos(theta);
        auto const b = B * std::sin(theta);

        if (check(a) && check(b)) {
            return std::make_optional(std::make_pair(my_doubletoint(a), my_doubletoint(b)));
        }
    }

    return std::nullopt;
}
}  // namespace