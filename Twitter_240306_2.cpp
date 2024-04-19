// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// 参考：https://twitter.com/suzzukes/status/1760778992712294578
#include <cstdint>   // for std::int32_t
#include <iostream>  // for std::cout, std::endl
#include <optional>  // for std::make_optional, std::optional

namespace {
static auto constexpr N = 1000;
static auto constexpr M = 60;

std::optional<std::int32_t> get_answer();
}  // namespace

int main()
{
    if (auto const answer = get_answer()) {
        std::cout << "answer = " << *answer << std::endl;
    }

    return 0;
}

namespace {
std::optional<std::int32_t> get_answer()
{
    auto cnt = 0;
    for (auto i = 1; i <= N; i++) {
        if (i % 3 == 0 || i % 7 == 0) {
            cnt++;
        }

        if (cnt == M) {
            return std::make_optional(i);
        }
    }

    return std::nullopt;
}
}  // namespace