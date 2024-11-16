// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1768950601889779927
#define SAVE_RESULT 1

#include <algorithm>  // for std::max_element, std::sort
#include <cassert>    // for assert
#include <cstdint>    // for std::int32_t
#ifdef SAVE_RESULT
#include <fstream>
#endif
#include <iomanip>   // for std::setiosflags, std::setprecision
#include <iostream>  // for std::cout, std::endl
#include <iterator>  // for std::distance
#include <optional>  // for std::make_optional, std::optional
#include <random>    // for std::mt19937, std::random_device, std::uniform_int_distribution
#include <tuple>     // for std::make_tuple, std::tuple
#include <vector>    // for std::vector

namespace {
using mytuple = std::tuple<double, double, std::int32_t>;

static auto constexpr N    = 10000000;
static auto constexpr REST = 8;

class MyRand final
{
    std::uniform_int_distribution<> dist_;
    std::mt19937                    engine_;

public:
    MyRand();
    double rand()
    {
        return dist_(engine_);
    }
};

mytuple                   getresult(std::vector<std::int32_t> const & vec, std::optional<std::ofstream> & pofs);
std::vector<std::int32_t> montecarlo(MyRand & mr, std::int32_t numdice);
void                      result_display(mytuple const & tup);
}  // namespace

int main()
{
    MyRand mr;

    std::optional<std::ofstream> pofs;
    if (SAVE_RESULT) {
        pofs.emplace("result1.txt");
    }
    auto const res = montecarlo(mr, 2);
    auto const ans = getresult(res, pofs);

    std::cout << "サイコロ2個の場合:" << std::endl;
    result_display(ans);

    std::optional<std::ofstream> pofs2;
    if (SAVE_RESULT) {
        pofs2.emplace("result2.txt");
    }

    auto const res2 = montecarlo(mr, 3);
    auto const ans2 = getresult(res2, pofs2);

    std::cout << "サイコロ3個の場合:" << std::endl;
    result_display(ans2);
}

namespace {
MyRand::MyRand() : dist_(1, 6)
{
    #ifdef TEST
        std::mt19937 engine(42);
    #else
        std::random_device seed_gen;
        std::mt19937 engine(seed_gen());
    #endif
}

std::tuple<double, double, std::int32_t> getresult(std::vector<std::int32_t> const & vec,
                                                   std::optional<std::ofstream> &    pofs)
{
    assert(vec.size() == N);

    auto const mean = static_cast<double>(std::reduce(vec.begin(), vec.end())) / static_cast<double>(N);

    double median;
    auto   vectmp(vec);
    std::sort(vectmp.begin(), vectmp.end());
    if (N % 2 == 0) {
        median = static_cast<double>(vectmp[N / 2 - 1] + vectmp[N / 2]) * 0.5;
    } else {
        median = static_cast<double>(vectmp[N / 2]);
    }

    std::vector count(*std::max_element(vectmp.begin(), vectmp.end()) + 1, 0);

    for (auto const item : vectmp) {
        count[item]++;
    }

    if (pofs) {
        for (auto i = 1; i < count.size(); i++) {
            *pofs << i << " " << count[i] << std::endl;
        }
    }

    // 最大値の要素のインデックスを取り出す
    auto const mode = std::distance(count.begin(), std::max_element(count.begin(), count.end()));

    return std::make_tuple(mean, median, mode);
}

std::vector<std::int32_t> montecarlo(MyRand & mr, std::int32_t numdice)
{
    std::vector<std::int32_t> v;
    for (auto i = 0; i < N; i++) {
        auto pos = REST;
        for (auto j = 1;; j++) {
            auto sum = 0;

            for (auto k = 0; k < numdice; k++) {
                sum += mr.rand();
            }

            pos -= sum;
            if (pos == 0) {
                v.push_back(j);
                break;
            }
            else if (pos < 0) {
                pos = -pos;
            }
        }
    }

    return v;
}

void result_display(mytuple const & tup)
{
    auto const [mean, median, mode] = tup;

    std::cout << std::setprecision(3) << std::setiosflags(std::ios::fixed);
    std::cout << "平均値: " << mean << "ターン, 中央値: " << median << "ターン, 最頻値:" << mode << "ターン"
              << std::endl;
}
}  // namespace