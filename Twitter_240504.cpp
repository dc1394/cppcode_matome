// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://twitter.com/dc1394/status/1786658106098991335
#include <cstdint>    // for std::int32_t
#include <iostream>   // for std::cout, std::endl

namespace {
std::int32_t get_answer();
}  // namespace

int main()
{
    auto const answer = get_answer();
    std::cout << "answer = " << answer << std::endl;

    return 0;
}

namespace {
std::int32_t get_answer()
{
    auto cnt = 0;
    for (auto i = 1010; i <= 1919; i++) {
        if ((i / 10) % 10 == 1 && i % 11 == 0) {
            std::cout << i << std::endl;
            cnt++;
        }
    }

    return cnt;
}
}  // namespace