// 色数（@MSc7orme）さんの問題の解答
// https://x.com/dc1394/status/1781609070904160552
#include <boost/math/constants/constants.hpp>  // for boost::math::constants::pi
#include <boost/math/tools/roots.hpp>          // for boost::math::tools::bisect
#include <boost/multiprecision/cpp_dec_float.hpp>  // for boost::multiprecision::cpp_dec_float, boost::multiprecision::number
#include <cassert>                                 // for assert
#include <cstdint>                                 // for std::int64_t
#include <functional>                              // for std::function
#include <iomanip>                                 // for std::setprecision, std::setiosflags
#include <iostream>                                // for std::cout, std::endl
#include <omp.h>                                   // for pragma omp parallel for
#include <utility>                                 // for std::make_pair, std::move, std::pair
#include <valarray>                                // for std::valarray
#include <vector>                                  // for std::vector

namespace {
namespace mp                  = boost::multiprecision;
using cpp_dec_float_170_64exp = mp::number<mp::cpp_dec_float<170, std::int64_t>>;

class Gauss_Legendre_integ final
{
    static cpp_dec_float_170_64exp const EPS;

    std::int32_t                         n_;
    std::vector<cpp_dec_float_170_64exp> w_;
    std::vector<cpp_dec_float_170_64exp> x_;

    void init_gauleg();

public:
    explicit Gauss_Legendre_integ(std::int32_t n) : n_(n), w_(n_), x_(n_)
    {
        init_gauleg();
    };
    cpp_dec_float_170_64exp integrate(cpp_dec_float_170_64exp const & x1, cpp_dec_float_170_64exp const & x2) const;
};

cpp_dec_float_170_64exp const Gauss_Legendre_integ::EPS = cpp_dec_float_170_64exp(1.0E-100);

static auto constexpr N = 1000;
static auto const DELTA = cpp_dec_float_170_64exp(1.0E-30);
static auto const PI    = boost::math::constants::pi<cpp_dec_float_170_64exp>();

cpp_dec_float_170_64exp                                     func(cpp_dec_float_170_64exp const & x);
std::pair<cpp_dec_float_170_64exp, cpp_dec_float_170_64exp> get_answer();
}  // namespace

int main()
{
    auto const [answer, check] = get_answer();

    std::cout << std::setprecision(100) << std::setiosflags(std::ios::fixed);
    std::cout << "Gauss-Legendre integrate = " << answer << "\nAnalytical               = " << check << std::endl;

    return 0;
}

namespace {
void Gauss_Legendre_integ::init_gauleg()
{
    auto const m = (n_ + 1) / 2;

#pragma omp parallel for shared(x_, w_)
    for (auto i = 0; i < m; i++) {
        auto                    z = mp::cos(PI * (cpp_dec_float_170_64exp(i + 1) - cpp_dec_float_170_64exp(0.25)) /
                                            (cpp_dec_float_170_64exp(n_) + cpp_dec_float_170_64exp(0.5)));
        cpp_dec_float_170_64exp z1, pp;

        do {
            auto p1 = cpp_dec_float_170_64exp(1);
            auto p2 = cpp_dec_float_170_64exp(0);

            for (auto j = 1; j <= n_; j++) {
                auto const p3 = p2;
                p2            = p1;
                p1            = ((cpp_dec_float_170_64exp(2 * j) - cpp_dec_float_170_64exp(1)) * z * p2 -
                      cpp_dec_float_170_64exp(j - 1) * p3) /
                     cpp_dec_float_170_64exp(j);
            }

            pp = cpp_dec_float_170_64exp(n_) * (z * p1 - p2) / (z * z - cpp_dec_float_170_64exp(1));
            z1 = z;
            z  = z1 - p1 / pp;
        } while (mp::fabs(z - z1) > EPS);

        x_[i]          = -z;
        x_[n_ - i - 1] = z;
        w_[i]          = cpp_dec_float_170_64exp(2) / ((cpp_dec_float_170_64exp(1) - z * z) * pp * pp);
        w_[n_ - i - 1] = w_[i];
    }
}

cpp_dec_float_170_64exp Gauss_Legendre_integ::integrate(cpp_dec_float_170_64exp const & x1,
                                                        cpp_dec_float_170_64exp const & x2) const
{
    assert(x1 < x2);

    auto const xm = cpp_dec_float_170_64exp(0.5) * (x1 + x2);
    auto const xr = cpp_dec_float_170_64exp(0.5) * (x2 - x1);

    std::valarray<cpp_dec_float_170_64exp> sum(n_);
#pragma omp parallel for
    for (auto i = 0; i < n_; i++) {
        sum[i] = w_[i] * func(xm + xr * x_[i]);
    }

    return sum.sum() * xr;
}

cpp_dec_float_170_64exp func(cpp_dec_float_170_64exp const & x)
{
    auto const a = cpp_dec_float_170_64exp(0.5) * PI * mp::sinh(x);
    auto const t = mp::tanh(a);

    return mp::log(cpp_dec_float_170_64exp(1) - t) * mp::log(t) * cpp_dec_float_170_64exp(0.5) * PI * mp::cosh(x) /
           (mp::cosh(a) * mp::cosh(a));
}

std::pair<cpp_dec_float_170_64exp, cpp_dec_float_170_64exp> get_answer()
{
    Gauss_Legendre_integ integ(N);
    auto const           constant = cpp_dec_float_170_64exp(2) - PI * PI / cpp_dec_float_170_64exp(6);

    auto const fun = [&integ, &constant](cpp_dec_float_170_64exp const & max) {
        auto const answer = integ.integrate(cpp_dec_float_170_64exp(DELTA), cpp_dec_float_170_64exp(max));
        return answer - constant;
    };

    boost::uintmax_t max_iter = 1000;
    auto const       res      = boost::math::tools::bisect(
        fun, cpp_dec_float_170_64exp(std::string("2.26274649749316953701833503496598089204466788")),
        cpp_dec_float_170_64exp(std::string("2.26274649749316953701833503496598089204466789")),
        boost::math::tools::eps_tolerance<cpp_dec_float_170_64exp>(150), max_iter);

    auto const answer =
        integ.integrate(cpp_dec_float_170_64exp(DELTA), (res.first + res.second) * cpp_dec_float_170_64exp(0.5));

    return std::make_pair(std::move(answer), std::move(constant));
}
}  // namespace