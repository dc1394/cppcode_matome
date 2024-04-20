// 大澤裕一（@HirokazuOHSAWA）さんの問題の解答
// https://twitter.com/dc1394/status/1768185923437761016
// 参考→ https://nonbiri-tereka.hatenablog.com/entry/2014/07/01/123518
#include <algorithm>  // for std::remove_if
#include <cstdint>    // for std::int32_t
#include <iostream>   // for std::cout, std::endl
#include <utility>    // for std::pair, std::make_pair
#include <vector>     // for std::vector

namespace {
static auto constexpr N = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1;

std::vector<std::pair<std::int32_t, std::int32_t>> calc_divisors(std::int32_t n);
std::vector<std::pair<std::int32_t, std::int32_t>> get_answer();
}  // namespace

int main()
{
    auto const answer = get_answer();
    std::cout << "(m, n) = ";
    for (auto const & item : answer) {
        std::cout << '(' << item.first << ", " << item.second << "), ";
    }
    std::cout << std::endl;

    std::cout << "全" << answer.size() << "通り" << std::endl;
}

namespace {
// N の約数をすべて求める関数
std::vector<std::pair<std::int32_t, std::int32_t>> calc_divisors(std::int32_t n)
{
    // 答えを表す集合
    std::vector<std::pair<std::int32_t, std::int32_t>> res;

    // 各整数 i が n の約数かどうかを調べる
    for (auto i = 1; i * i <= n; ++i) {
        // i が n の約数でない場合はスキップ
        if (n % i != 0) {
            continue;
        }

        // i は約数である
        res.push_back(std::make_pair(i, n / i));
    }

    return res;
}

std::vector<std::pair<std::int32_t, std::int32_t>> get_answer()
{
    auto res = calc_divisors(N);

    auto const itr = std::remove_if(res.begin(), res.end(),
                                    [](auto const & item) { return item.first % 2 != 0 || item.second % 2 != 0; });

    res.erase(itr, res.end());

    return res;
}
}  // namespace
