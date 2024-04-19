// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1766373109836431393
#include <cstdint>  // for std::int32_t
#include <iostream> // for std::cout, std::endl

namespace {
static auto constexpr N = 64;

std::int32_t get_answer();
}  // namespace

int main()
{
    std::cout << "answer = " << get_answer() << std::endl;

    return 0;
}

namespace {
std::int32_t get_answer()
{
    auto cnt = 0;

    for (auto a = 1; a <= N; a *= 2) {
        for (auto b = 1; a * b <= N; b *= 2) {
            for (auto c = 1; a * b * c <= N; c *= 2) {
                if (a * b * c == N) {
                    cnt++;
                }
            }
        }
    }

    return cnt;
}
}  // namespace