// 天和（@ImMKzAygftk3dDH）さん作の問題の解答
// 参考：https://x.com/ImMKzAygftk3dDH/status/1760826160366436590
#include <algorithm>                               // for std::sort
#include <boost/multiprecision/cpp_dec_float.hpp>  // for boost::multiprecision::cpp_dec_float, boost::multiprecision::number
#include <boost/multiprecision/cpp_int.hpp>        // for boost::multiprecision::cpp_int
#include <cassert>                                 // for assert
#include <iostream>                                // for std::cout, std::endl
#include <sstream>                                 // for std::ostringstream
#include <string>                                  // for std::string
#include <vector>                                  // for std::vector

namespace {
namespace mp                   = boost::multiprecision;
using cpp_dec_float_1000_64exp = mp::number<mp::cpp_dec_float<1000, std::int64_t>>;

static auto constexpr N   = 2024;
static auto constexpr L   = 10000;
static auto constexpr M   = 2000;
static auto constexpr MAX = L + M;
static auto constexpr TH  = 1.0E-7;

std::string get_answer();
bool        is_integer_modf(cpp_dec_float_1000_64exp const & x);
}  // namespace

int main()
{
    std::cout << get_answer() << std::endl;
    return 0;
}

namespace {
std::string get_answer()
{
    std::vector<mp::cpp_int> v;
    v.reserve(MAX);

    for (auto i = 1; i <= L; i++) {
        v.push_back(mp::pow(mp::cpp_int(3), i));
    }
    for (auto i = 1; i <= M; i++) {
        v.push_back(mp::pow(mp::cpp_int(7), i));
    }

    std::sort(v.begin(), v.end());

    auto const a    = v[N - 1].convert_to<cpp_dec_float_1000_64exp>();
    auto const temp = mp::log10(a) / mp::log10(static_cast<cpp_dec_float_1000_64exp>(3));

    std::ostringstream oss;
    if (is_integer_modf(temp)) {
        oss << "answer = 3 ^ " << temp << " = " << v[N - 1] << std::endl;
    } else {
        auto const temp2 = mp::log10(a) / mp::log10(static_cast<cpp_dec_float_1000_64exp>(7));
        assert(is_integer_modf(temp2));
        oss << "answer = 7 ^ " << temp2 << " = " << v[N - 1] << std::endl;
    }

    return oss.str();
}

bool is_integer_modf(cpp_dec_float_1000_64exp const & x)
{
    return mp::fabs(x - mp::round(x)) < static_cast<cpp_dec_float_1000_64exp>(TH);
}
}  // namespace