#include <algorithm>                               // for std::remove
#include <boost/multiprecision/cpp_dec_float.hpp>  // for boost::multiprecision::cpp_dec_float, boost::multiprecision::number
#include <boost/multiprecision/cpp_int.hpp>        // for boost::multiprecision::cpp_int
#include <boost/rational.hpp>                      // for boost::rational
#include <cstdint>                                 // for std::int64_t
#include <iostream>                                // for std::cout, std::endl
#include <omp.h>                                   // for #pragma omp parallel
#include <string>                                  // for std::string
#include <vector>                                  // for std::vector

namespace {
static auto constexpr N = 10000;
static auto constexpr M = 400;

namespace mp                   = boost::multiprecision;
using cpp_dec_float_3000_64exp = mp::number<mp::cpp_dec_float<3000, std::int64_t>>;
using myfraction               = boost::rational<mp::cpp_int>;
using myvector                 = std::vector<myfraction>;

myvector get_answer();
}  // namespace

int main()
{
    auto const answer = get_answer();

    for (auto const & item : answer) {
        std::cout << item << ", ";
    }
    std::cout << "\nanswer = " << answer.size() << std::endl;
}

namespace {
myvector get_answer()
{
    myvector v(N, myfraction(0, 1));

#pragma omp parallel for shared(v)
    for (auto i = 1; i <= N; i++) {
        myfraction n(0, 1);
        for (auto j = 1; j <= i; j++) {
            n += myfraction(1, j);
        }
        auto const str = boost::rational_cast<cpp_dec_float_3000_64exp>(n).str();
        if (str.length() <= M) {
            v[i] = n;
        }
    }

    v.erase(std::remove(v.begin(), v.end(), myfraction(0, 1)), v.end());

    return v;
}
}  // namespace
