// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1767784104937099393
#include <cstdint>  // for std::int32_t
#include <iostream> // for std::cout, std::endl
#include <string>   // for std::string, std::stoi, std::to_string

namespace {
std::int32_t get_answer();
}

int main()
{
    std::cout << "answer = " << get_answer() << std::endl;
}

namespace {
std::int32_t get_answer()
{
    auto cnt = 0;

    auto const lambda = [](auto const & str, auto i) { return std::stoi(str[i] + std::string("\0")); };

    for (auto i = 100; i <= 999; i++) {
        auto const str = std::to_string(i);
        auto const M = lambda(str, 0) * lambda(str, 1) * lambda(str, 2);
        
        if (M % 10 == 5) {
            cnt++;
        }
    }

    return cnt;
}
}  // namespace
