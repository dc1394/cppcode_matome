// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://twitter.com/dc1394/status/1765281778175197672
#include <algorithm>  // for std::erase, std::find, std::sort, std::unique
#include <array>      // for std::array
#include <cstdint>    // for std::int32_t
#include <iostream>   // for std::cout, std::cerr
#include <random>     // for std::random_device, std::mt19937, std::uniform_int_distribution
#include <vector>     // for std::vector

namespace {
static auto constexpr N = 10000;
static auto constexpr M = 3;

std::vector<std::int32_t> get_answer();
void                      my_remove(std::vector<std::int32_t> & vec, std::int32_t n);
}  // namespace

int main()
{
    auto const answer = get_answer();
    for (auto const item : answer) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;

    std::cout << "answer = " << answer.size() << std::endl;

    return 0;
}

namespace {
std::vector<std::int32_t> get_answer()
{
    std::random_device seed_gen;
    std::mt19937       engine(seed_gen());

    std::uniform_int_distribution<std::int32_t> dist(0, 5);

    std::vector<std::int32_t> v;
    for (auto i = 0; i < N; i++) {
        std::vector<std::int32_t> vec = {1, 2, 2, 3, 3, 3};

        auto num = 0;
        auto a   = 1;
        for (auto j = 0; j < M; j++) {
            std::int32_t n;
            do {
                n = dist(engine);
            } while (n >= vec.size());

            auto const temp = vec[n];
            num += a * temp;
            my_remove(vec, temp);
            a *= 10;
        }

        v.push_back(num);
    }

    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());

    return v;
}

void my_remove(std::vector<std::int32_t> & vec, std::int32_t n)
{
    auto const itr = std::find(vec.begin(), vec.end(), n);
    vec.erase(itr, itr + 1);
}
}  // namespace
