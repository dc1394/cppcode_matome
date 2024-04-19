// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1766806508095029425
#include <algorithm>  // for std::sort, std::unique
#include <array>      // for std::array
#include <cstdint>    // for std::int32_t
#include <iostream>   // for std::cout, std::endl
#include <vector>     // for std::vector

namespace {
std::int32_t get_answer();
}

int main()
{
    auto const answer = get_answer();
    std::cout << "answer = " << answer << std::endl;
}

namespace {
std::int32_t get_answer()
{
    std::vector<std::array<std::int32_t, 3>> v;

    for (auto i = 5; i <= 1155; i += 2) {
        for (auto j = 5; i * j <= 1155; j += 2) {
            for (auto k = 5; i * j * k <= 1155; k += 2) {
                if (i * j * k == 1155) {
                    std::array<std::int32_t, 3> tmp{i, j, k};
                    v.push_back(tmp);
                }
            }
        }
    }

    for (auto && item : v) {
        std::sort(item.begin(), item.end());
    }
    std::sort(v.begin(), v.end());

    v.erase(std::unique(v.begin(), v.end()), v.end());

    for (auto const & item : v) {
        for (auto const & item2 : item) {
            std::cout << item2 << " ";
        }
        std::cout << std::endl;
    }

    return v.size();
}
}  // namespace