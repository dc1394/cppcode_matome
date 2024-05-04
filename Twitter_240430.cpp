// ますたべ（@ErZhong41864）さん作の問題の解答
// https://twitter.com/dc1394/status/1785177326747271495
#include <algorithm>  // for std::min
#include <cmath>      // for std::sqrt
#include <cstdint>    // for std::int32_t
#include <fstream>    // for std::ofstream
#include <iomanip>    // for std::setprecision, std::setiosflags
#include <iostream>   // for std::cout, std::endl
#include <random>     // for std::mt19937, std::normal_distribution, std::random_device, std::uniform_real_distribution
#include <utility>    // for std::make_pair, std::pair
#include <vector>     // for std::vector

namespace {
static auto constexpr N = 1000000;
using mypair            = std::pair<double, double>;
using myvector          = std::vector<mypair>;

static auto const X0 = std::make_pair(1.0 / std::sqrt(2.0), 1.0 / std::sqrt(2.0));

class MyRand final
{
    std::uniform_real_distribution<> dist_;
    std::mt19937                     engine_;

public:
    MyRand();
    double rand()
    {
        return dist_(engine_);
    }

    double rand(std::normal_distribution<> & dist)
    {
        return dist(engine_);
    }
};

double distribution(mypair const & pair);
void   get_answer();
// メトロポリス・ヘイスティングス法によるサンプリング
myvector metropolis_hastings(mypair const & x0, std::int32_t n_steps);
mypair   p_transition(MyRand & mr, mypair const & pair);
}  // namespace

int main()
{
    get_answer();
    return 0;
}

namespace {
MyRand::MyRand() : dist_(0.0, 1.0)
{
    std::random_device seed_gen;
    engine_ = std::mt19937(seed_gen());
}

double distribution(mypair const & pair)
{
    auto const [x, y] = pair;
    return (std::fabs(x) + std::fabs(y) >= 1.0 && x * x + y * y <= 1.0) ? 1.0 : 0.0;
}

void get_answer()
{
    // サンプリング
    auto const samples = metropolis_hastings(X0, N);

    std::ofstream ofs("result.txt");

    // 結果の出力
    ofs << std::setprecision(14) << std::setiosflags(std::ios::fixed);
    for (auto const & elem : samples) {
        auto const x = elem.first + elem.second;
        auto const y = elem.first * elem.second;

        ofs << x << ' ' << y << std::endl;
    }
}

myvector metropolis_hastings(mypair const & x0, std::int32_t n_steps)
{
    MyRand   mr;
    myvector samples = {x0};

    for (auto i = 1; i < n_steps; i++) {
        auto const p = samples[i - 1];

        auto const p_next = p_transition(mr, p);
        auto const alpha  = std::min(1.0, distribution(p_next) / distribution(p));
        auto const u      = mr.rand();
        if (u < alpha) {
            samples.push_back(p_next);
        } else {
            samples.push_back(p);
        }
    }

    return samples;
}

mypair p_transition(MyRand & mr, mypair const & pair)
{
    auto const [x, y] = pair;
    std::normal_distribution<> dist(x, 1.0);
    std::normal_distribution<> dist2(y, 1.0);

    return std::make_pair(mr.rand(dist), mr.rand(dist2));
}
}  // namespace