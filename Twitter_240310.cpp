// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1766701678496248179
#include <cstdint>  // for std::int32_t
#include <iostream> // for std::cout, std::endl

namespace {
static auto constexpr N = 100;

std::int32_t get_answer();
}  // namespace

int main()
{
    std::cout << "answer = " << get_answer() << std::endl;
}

namespace {
std::int32_t get_answer()
{
    auto sum    = 0;
    auto numseq = 2;

    for (auto i = 1; i <= N; i++) {
        if (i % 3 == 1) {
            numseq--;
        } else {
            numseq++;
        }

        sum += numseq;
    }

    return sum;
}
}  // namespace