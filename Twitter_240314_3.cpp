// たけちゃん先生（@takechan1414213）さん作の問題の解答
// https://x.com/dc1394/status/1769937727309697230
#include <boost/multiprecision/cpp_dec_float.hpp>  // for boost::multiprecision
#include <cstdint>                                 // for std::int32_t
#include <iomanip>                                 // for std::setiosflags, std::setprecision
#include <iostream>                                // for std::cout, std::endl

namespace {
static auto const N             = 100;
namespace mp                    = boost::multiprecision;
using cpp_dec_float_10000_64exp = mp::number<mp::cpp_dec_float<10000, std::int64_t>>;

cpp_dec_float_10000_64exp get_answer();
}  // namespace

int main()
{
    std::cout << std::setprecision(100) << std::setiosflags(std::ios::fixed);
    std::cout << "answer = " << get_answer() << std::endl;
}

namespace {
cpp_dec_float_10000_64exp get_answer()
{
    auto an = mp::sqrt(static_cast<cpp_dec_float_10000_64exp>(5));
    for (auto i = 2; i <= N; i++) {
        an = 1.0 / (an - mp::floor(an));
    }

    return an;
}

}  // namespace