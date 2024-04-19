#include <cstdint>  // for std::int32_t
#include <iostream> // for std::cout, std::endl
#include <string>   // for std::to_string

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
    std::int32_t cnt = 0;

    for (auto i = 1000; i <= 1919; i++) {
        auto const str = std::to_string(i);
        if (str[0] == '1' && str[2] == '1' && i % 11 == 0) {
            cnt++;
        }
    }

    return cnt;
}
}  // namespace
