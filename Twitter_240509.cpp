#include <boost/multiprecision/cpp_dec_float.hpp>  // for boost::multiprecision::cpp_dec_float, boost::multiprecision::number
#include <boost/multiprecision/cpp_int.hpp>        // for boost::multiprecision::cpp_int
#include <boost/rational.hpp>                      // for boost::rational
#include <cstdint>                                 // for std::int64_t
#include <iostream>                                // for std::cout, std::endl
//#include <omp.h>                                   // for #pragma omp parallel
#include <cassert>
#include <format>
#include <iomanip>
#include <string>  // for std::string

namespace {
static auto constexpr N = 5 + 1;

namespace mp                   = boost::multiprecision;
using cpp_dec_float_3000_64exp = mp::number<mp::cpp_dec_float<3000, std::int64_t>>;
using myfraction               = boost::rational<mp::cpp_int>;

mp::cpp_int              factorial(mp::cpp_int const & n);
cpp_dec_float_3000_64exp get_answer();
mp::cpp_int              mypow(mp::cpp_int const & n, mp::cpp_int const & m);
}  // namespace

int main()
{
    auto const answer = get_answer();

    // for (auto const & item : answer) {
    //     std::cout << item << ", ";
    // }
    // std::cout << "\nanswer = " << answer.size() << std::endl;
}

namespace {
cpp_dec_float_3000_64exp get_answer()
{
    auto answer = myfraction(0, 1);

    std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);

    for (auto i = 0; i < N; i++) {
        auto const a  = myfraction(factorial(2 * i), factorial(i));
        auto const a3 = a * a * a;
        auto const b  = myfraction(42 * i + 5, mypow(2, 12 * i + 4));

        answer += a3 * b;
        std::cout << boost::rational_cast<cpp_dec_float_3000_64exp>(1 / answer) << std::endl;
    }


    std::cout << 1 / answer;

    return 0;
}

mp::cpp_int factorial(mp::cpp_int const & n)
{
    assert(n >= 0);

    if (n == 0) {
        return mp::cpp_int(1);
    }

    mp::cpp_int a = 1;

    for (mp::cpp_int i = 1; i <= n; i++) {
        a *= i;
    }

    return a;
}

mp::cpp_int mypow(mp::cpp_int const & n, mp::cpp_int const & m)
{
    assert(m >= 0);

    if (m == 0) {
        return mp::cpp_int(1);
    }

    mp::cpp_int a = 1;
    for (mp::cpp_int i = 0; i < m; i++) {
        a *= n;
    }

    return a;
}
}  // namespace
