// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1784546093256310861
#include <cassert>   // for assert
#include <cstdint>   // for std::int32_t, std::uint64_t
#include <iostream>  // for std::cout, std::endl
#include <limits>    // for std::numeric_limits
#include <vector>    // for std::vector

namespace {
static auto constexpr N = 100000;
bool                      is_square(std::uint64_t x);
std::vector<std::int32_t> get_answer();
}  // namespace

int main()
{
    std::cout << "answer = " << get_answer()[2] << std::endl;
}

namespace {
bool is_square(std::uint64_t x)
{
    assert(sizeof(unsigned long long) == sizeof(std::uint64_t));

    auto const xtz = __builtin_ctz(x);
    if (x == 0) {
        return true;
    } else if (xtz & 1) {
        return false;
    }
    x >>= xtz;

    auto y = 1ULL;
    for (int i = 0; i < 5; i++) {
        y = ((3ULL - y * y * x) * y) >> 1;
    }

    auto xrt = x * y;
    if (xrt & (1ULL << 32)) {
        xrt = std::numeric_limits<uint64_t>::max() - xrt + 1;
    }

    xrt &= (1ULL << 32) - 1;

    return xrt * xrt == x;
}

std::vector<std::int32_t> get_answer()
{
    std::vector<std::int32_t> v;

    for (auto n = 12; n <= N; n += 12) {
        if (is_square(static_cast<std::uint64_t>(n + 36))) {
            v.push_back(n);
        }
    }

    return v;
}
}  // namespace