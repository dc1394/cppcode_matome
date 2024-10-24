// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1784829542097711281
#include <algorithm>  // for std::next_permutation, std::sort, std::unique
#include <cstdint>    // for std::int32_t
#include <iostream>   // for std::cout, std::endl
#include <numeric>    // for std::iota
#include <string>     // for std::stoi, std::string
#include <vector>     // for std::vector

namespace {
static auto constexpr N = 6;
static auto constexpr M = 3;
std::vector<std::int32_t> get_answer();
}  // namespace

int main()
{
    auto const answer = get_answer();

    for (auto const & elem : answer) {
        std::cout << elem << ' ';
    }

    std::cout << "\nanswer = " << answer.size() << std::endl;
}

namespace {
std::vector<std::int32_t> get_answer()
{
    std::vector<std::string> cards{"0", "1", "2", "3", "4", "5"};

    std::vector<std::int32_t> vtmp(N);
    std::iota(vtmp.begin(), vtmp.end(), 0);

    std::vector<std::int32_t> v;
    do {
        auto str = std::string("");

        for (auto i = 0; i < M; i++) {
            str += cards[vtmp[i]];
        }

        auto const n = std::stoi(str);
        if (str[0] != '0' && n % 5 == 0) {
            v.push_back(n);
        }
    } while (std::next_permutation(vtmp.begin(), vtmp.end()));

    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());

    return v;
}
}  // namespace