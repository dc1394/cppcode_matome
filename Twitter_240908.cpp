#include <boost/multiprecision/cpp_dec_float.hpp>  // for boost::multiprecision::cpp_dec_float, boost::multiprecision::number
#include <cmath>                                   // for std::log
#include <cstdint>                                 // for std::int64_t
#include <iomanip>                                 // for std::setprecision
#include <iostream>                                // for std::iostream
#include <numeric>                                 // for std::accumulate
#include <vector>                                  // for std::vector

namespace {
namespace mp                  = boost::multiprecision;
using cpp_dec_float_100_64exp = mp::number<mp::cpp_dec_float<100, std::int64_t>>;
static auto constexpr MAX     = 100000000LL;

std::vector<std::int64_t> seek_primes();
cpp_dec_float_100_64exp   lhs(std::int64_t n);
cpp_dec_float_100_64exp   rhs(std::int64_t n, std::vector<std::int64_t> const & primes);
}  // namespace

int main()
{
    auto const primes(seek_primes());

    std::cout << std::setprecision(10) << std::fixed;
    for (auto n = 1; n <= 1000000; n *= 10) {
        auto const lhstmp = lhs(n);
        auto const rhstmp = rhs(n, primes);
        std::cout << "n = " << n << ", lhs = " << lhstmp << ", rhs = " << rhstmp << ", rhs / lhs = " << rhstmp / lhstmp << std::endl;
    }

    return 0;
}

namespace {
std::vector<std::int64_t> seek_primes()
{
    auto const max  = MAX + 1;
    auto const pmax = static_cast<std::int64_t>(static_cast<double>(max) / std::log(static_cast<double>(max)) * 1.2);

    std::vector<char>         sieve(max / 2 + 16);
    std::vector<std::int64_t> prime(pmax);

    auto * const p = reinterpret_cast<std::int64_t *>(sieve.data());
    for (auto i = 0; i <= max / 16; i += 3) {
        p[i + 0] = 0x0001010001010001;  //0x01010001;
        p[i + 1] = 0x0101000101000101;  //0x00010100;
        p[i + 2] = 0x0100010100010100;  //0x01000101;
    }
    sieve[1] = 1;

    for (auto i = 5LL; i * i < max; i += 2LL) {
        if (sieve[i / 2]) {
            auto j   = i * i / 2;
            sieve[j] = 0;
            j += i * (i % 3 - 1);
            for (; j < max / 2 - i * 2; j += i) {
                sieve[j] = 0;
                j += i * 2;
                sieve[j] = 0;
            }
            if (j < max / 2) {
                sieve[j] = 0;
            }
        }
    }

    prime[0]  = 2;
    auto pnum = 1LL;

    for (auto i = 1LL; i < max / 2; i++) {
        prime[pnum] = i * 2 + 1;
        pnum += sieve[i];
    }

    return prime;
}

cpp_dec_float_100_64exp lhs(std::int64_t n)
{
    cpp_dec_float_100_64exp sum(0);
    for (auto i = 1LL; i <= n; i++) {
        sum += cpp_dec_float_100_64exp(1) / cpp_dec_float_100_64exp(i);
    }

    return sum;
}

cpp_dec_float_100_64exp rhs(std::int64_t n, std::vector<std::int64_t> const & primes)
{
    return std::accumulate(
        primes.begin(), primes.begin() + n, cpp_dec_float_100_64exp(1), [n](auto const & product, auto prime) {
            auto const tmp = cpp_dec_float_100_64exp(1) / prime;
            return product * ((cpp_dec_float_100_64exp(1) - mp::pow(tmp, n + 1)) / (cpp_dec_float_100_64exp(1) - tmp));
        });
}
}  // namespace