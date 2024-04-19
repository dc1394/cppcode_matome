// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1768071193910030464
#include <algorithm>  // for std::next_permutation
#include <cassert>    // for assert
#include <cstdint>    // for std::int32_t
#include <iostream>   // for std::cout, std::endl
#include <utility>    // for std::make_pair, std::pair
#include <vector>     // for std::vector

namespace {
static std::vector<char> const vec = {'A', 'B', 'C', 'D'};

std::pair<std::int32_t, std::int32_t> get_answer();
}  // namespace

int main()
{
    auto const ans = get_answer();
    std::cout << "answer = " << ans.first << "/" << ans.second << std::endl;
}

namespace {
std::pair<std::int32_t, std::int32_t> get_answer()
{
    std::vector<char> v(vec);

    auto n = 0;
    auto cnt = 0;
    do {
        n++;
        auto const len = vec.size();
        assert(len == v.size());

        auto i = 0;
        for (i = 0; i < len; i++) {
            if (vec[i] == v[i]) {
                break;
            }
        }

        if (i == len) {
            cnt++;
        }
    } while (std::next_permutation(v.begin(), v.end()));

    return std::make_pair(cnt, n);
}
}  // namespace