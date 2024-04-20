// 色数（@MSc7orme）さんの問題の解答
// https://x.com/dc1394/status/1780926077751513170
#include <boost/math/constants/constants.hpp>      // for boost::math::constants::pi
#include <boost/multi_array.hpp>                   // for boost::extents, boost::multi_array
#include <boost/multiprecision/cpp_dec_float.hpp>  // for boost::multiprecision::cpp_dec_float, boost::multiprecision::number
#include <cassert>                                 // for assert
#include <cstdint>                                 // for std::int64_t
#include <functional>                              // for std::function
#include <iomanip>                                 // for std::setprecision, std::setiosflags
#include <iostream>                                // for std::cout, std::endl
#include <utility>                                 // for std::make_pair, std::move, std::pair

namespace {
static auto constexpr N = 15;

namespace mp                   = boost::multiprecision;
using cpp_dec_float_1000_64exp = mp::number<mp::cpp_dec_float<1000, std::int64_t>>;

std::pair<cpp_dec_float_1000_64exp, cpp_dec_float_1000_64exp> get_answer();
cpp_dec_float_1000_64exp
romberg_integrate(cpp_dec_float_1000_64exp const & a, cpp_dec_float_1000_64exp const & b,
                  std::function<cpp_dec_float_1000_64exp(cpp_dec_float_1000_64exp const &)> const & func);
}  // namespace

int main()
{
    auto const [answer, check] = get_answer();
    std::cout << std::setprecision(100) << std::setiosflags(std::ios::fixed);
    std::cout << "Romberg integrate = " << answer << "\nAnalytical        = " << check << std::endl;

    return 0;
}

namespace {
std::pair<cpp_dec_float_1000_64exp, cpp_dec_float_1000_64exp> get_answer()
{
    auto const func = [](auto const & x) { return cpp_dec_float_1000_64exp(1) / (cpp_dec_float_1000_64exp(1) + x * x * x); };

    auto answer = romberg_integrate(cpp_dec_float_1000_64exp(0), cpp_dec_float_1000_64exp(1), func);
    auto check  = mp::log(cpp_dec_float_1000_64exp(2)) / cpp_dec_float_1000_64exp(3) +
                 mp::sqrt(cpp_dec_float_1000_64exp(3)) * boost::math::constants::pi<cpp_dec_float_1000_64exp>() /
                     cpp_dec_float_1000_64exp(9);

    return std::make_pair(std::move(answer), std::move(check));
}

cpp_dec_float_1000_64exp
romberg_integrate(cpp_dec_float_1000_64exp const & a, cpp_dec_float_1000_64exp const & b,
                  std::function<cpp_dec_float_1000_64exp(cpp_dec_float_1000_64exp const &)> const & func)
{
    assert(a < b);
    boost::multi_array<cpp_dec_float_1000_64exp, 2> t(boost::extents[N][N]);

    // 台形則で積分
    auto n = 2;
    for (auto i = 0; i < N; i++) {
        auto const h = (b - a) / static_cast<cpp_dec_float_1000_64exp>(n);
        auto       s = cpp_dec_float_1000_64exp(0);
        auto       x = a;

        for (auto j = 0; j < n - 1; j++) {
            x += h;
            s += func(x);
        }

        // 結果を保存
        t[i][0] = h * ((func(a) + func(b)) / cpp_dec_float_1000_64exp(2) + s);

        n *= 2;
    }

    // Richardsonの補外法
    n = 4;
    for (auto j = 1; j < N; j++) {
        for (auto i = j; i < N; i++) {
            t[i][j] = t[i][j - 1] + (t[i][j - 1] - t[i - 1][j - 1]) / (n - 1);
        }
        n *= 4;
    }

    return t[N - 1][N - 1];
}
}  // namespace