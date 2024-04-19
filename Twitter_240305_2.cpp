// れおまる（@reomaru_1103）さん作の問題の解答
// https://x.com/dc1394/status/1764870461824110659
// 参考: https://kamino.hatenablog.com/entry/cpp-permutation-combination
#include <cstdint>     // for std::int32_t
#include <functional>  // for std::function
#include <iostream>    // for std::cout, std::endl
#include <optional>    // for std::make_optional, std::optional
#include <string>      // for std::string
#include <vector>      // for std::vector

namespace {
static auto constexpr K = 3;
static auto constexpr N = 10000;
static auto constexpr M = 125;
static auto constexpr L = 269;

bool ansloop(std::vector<std::int32_t> const & conb, std::int32_t k);
// nCkの組み合わせに対して処理を実行する
void foreach_comb(std::int32_t n, std::int32_t k, std::function<void(std::vector<std::int32_t> &)> const & f);
std::optional<std::vector<std::int32_t>> get_answer();
std::vector<std::vector<std::int32_t>>   getconb(std::int32_t k);
void recursive_comb(std::vector<std::int32_t> & indexes, std::int32_t s, std::int32_t rest,
                    std::function<void(std::vector<std::int32_t> &)> const & f);
}  // namespace

int main()
{
    if (auto const answer = get_answer()) {
        std::cout << "answer = " << (*answer)[0] << ", " << (*answer)[1] << ", " << (*answer)[2] << std::endl;
    }

    return 0;
}

namespace {
bool ansloop(std::vector<std::int32_t> const & conb, std::int32_t k)
{
    auto cnt = 1;
    for (auto i = 1; i < N; i++) {
        auto const                          str = std::to_string(i);
        std::vector<std::string::size_type> vec(k, 0);
        for (auto n = 0U; n < conb.size(); n++) {
            vec[n] = str.find(std::to_string(conb[n]));
        }

        bool flag = false;
        for (auto const item : vec) {
            flag = flag || (item != std::string::npos);
        }

        if (flag) {
            continue;
        }

        if (cnt == M && i == L) {
            return true;
        }

        cnt++;

        if (cnt > M) {
            return false;
        }
    }

    return false;
}

// nCkの組み合わせに対して処理を実行する
void foreach_comb(std::int32_t n, std::int32_t k, std::function<void(std::vector<std::int32_t> &)> const & f)
{
    std::vector<std::int32_t> indexes(k, 0);
    recursive_comb(indexes, n - 1, k, f);
}

std::optional<std::vector<std::int32_t>> get_answer()
{
    for (auto const & conb : getconb(K)) {
        if (ansloop(conb, K)) {
            return std::make_optional(conb);
        }
    }

    return std::nullopt;
}

std::vector<std::vector<std::int32_t>> getconb(std::int32_t k)
{
    std::vector<std::vector<std::int32_t>> conb;
    foreach_comb(10, k, [&conb](std::vector<std::int32_t> & indexes) { conb.push_back(indexes); });

    return conb;
}

void recursive_comb(std::vector<std::int32_t> & indexes, std::int32_t s, std::int32_t rest,
                    std::function<void(std::vector<std::int32_t> &)> const & f)
{
    if (rest == 0) {
        f(indexes);
    } else {
        if (s < 0)
            return;

        recursive_comb(indexes, s - 1, rest, f);
        indexes[rest - 1] = s;
        recursive_comb(indexes, s - 1, rest - 1, f);
    }
}
}  // namespace
