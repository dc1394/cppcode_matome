// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1784829542097711281
#include <array>       // for std::array
#include <cstdint>     // for std::int32_t
#include <functional>  // for std::function
#include <iostream>    // for std::cout, std::endl
#include <vector>      // for std::vector

namespace {
static auto constexpr N = 5;
static auto constexpr M = 3;

using myarray = std::array<double, M>;

// nCkの組み合わせに対して処理を実行する
void foreach_comb(std::int32_t n, std::int32_t k, std::function<void(std::vector<std::int32_t> &)> const & f);
std::vector<myarray>                   get_answer();
std::vector<std::vector<std::int32_t>> get_combination(std::int32_t n, std::int32_t k);
void recursive_comb(std::vector<std::int32_t> & indexes, std::int32_t s, std::int32_t rest,
                    std::function<void(std::vector<std::int32_t> &)> const & f);
}  // namespace

int main()
{
    auto const answer = get_answer();

    for (auto const & elem : answer) {
        std::cout << '(';
        for (auto i = 0; i < M - 1; i++) {
            std::cout << elem[i] << "cm, ";
        }
        std::cout << elem[M - 1] << "cm), ";
    }

    std::cout << "\nanswer = " << answer.size() << std::endl;
}

namespace {
// nCkの組み合わせに対して処理を実行する
void foreach_comb(std::int32_t n, std::int32_t k, std::function<void(std::vector<std::int32_t> &)> const & f)
{
    std::vector<std::int32_t> indexes(k, 0);
    recursive_comb(indexes, n - 1, k, f);
}

std::vector<myarray> get_answer()
{
    std::vector<double> data{2.0, 3.0, 4.0, 5.0, 6.0};

    std::vector<myarray> answer;
    auto const           conb = get_combination(N, M);
    for (auto const & elem : conb) {
        if (data[elem[0]] + data[elem[1]] > data[elem[2]]) {
            answer.push_back(myarray{data[elem[0]], data[elem[1]], data[elem[2]]});
        }
    }

    return answer;
}

std::vector<std::vector<std::int32_t>> get_combination(std::int32_t n, std::int32_t k)
{
    std::vector<std::vector<std::int32_t>> conb;
    foreach_comb(n, k, [&conb](std::vector<std::int32_t> & indexes) { conb.push_back(indexes); });

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