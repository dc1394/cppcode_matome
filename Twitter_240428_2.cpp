// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1784540223755673932
#include <array>     // for std::array
#include <cstdint>   // for std::int32_t
#include <iostream>  // for std::cout, std::endl
#include <numeric>   // for std::iota
#include <optional>  // for std::make_optional, std::optional

namespace {
static auto constexpr N = 1000;
static auto constexpr M = 11;
static auto constexpr L = 19;
std::optional<std::int32_t> get_answer();
}  // namespace

int main()
{
    if (auto const answer = get_answer()) {
        std::cout << "answer = " << *answer << std::endl;
    }
}

namespace {
std::optional<std::int32_t> get_answer()
{
    for (auto i = 1; i < N; i++) {
        std::array<std::int32_t, M> arr;
        std::iota(arr.begin(), arr.end(), i);

        auto oddsum  = 0;
        auto evensum = 0;
        for (auto j = 0; j < M; j++) {
            if (j & 1) {
                oddsum += arr[j];
            } else {
                evensum += arr[j];
            }
        }

        if (evensum - oddsum == L) {
            return std::make_optional(i + M - 1);
        }
    }

    return std::nullopt;
}
}  // namespace