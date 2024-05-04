// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1771064849876808112
#include <iomanip>   // for std::setiosflags, std::setprecision
#include <iostream>  // for std::cout, std::cerr
#include <random>    // for std::random_device, std::mt19937, std::uniform_int_distribution
#include <utility>   // for std::make_pair, std::pair

namespace {
static auto constexpr N = 1000000;
static auto constexpr M = 7;

std::pair<double, double> get_answer();

double montecarlo(bool b);
}  // namespace

int main()
{
    auto const [ans1, ans2] = get_answer();
    std::cout << std::setprecision(1) << std::setiosflags(std::ios::fixed);
    std::cout << "4勝したら終わりの場合で引き分けになる確率 = " << ans1 << "(%), 4勝しても続ける場合で引き分けになる確率 = " << ans2 << "(%)" << std::endl;

    return 0;
}

namespace {
std::pair<double, double> get_answer()
{
    return std::make_pair(montecarlo(true), montecarlo(false));
}

double montecarlo(bool b)
{
    std::random_device seed_gen;
    std::mt19937       engine(seed_gen());
    std::uniform_int_distribution<std::int32_t> dist(1, 100);

    auto cnt = 0;

    for (auto i = 0; i < N; i++) {
        auto cnt_a = 0;
        auto cnt_b = 0;
        auto cnt_d = 0;

        for (auto j = 1; j <= M; j++) {
            auto const rnd = dist(engine);
            if (rnd <= 45) {
                cnt_a++;
            } else if (rnd <= 90) {
                cnt_b++;
            }

            if (b) {
                if (j != M && (cnt_a >= 4 || cnt_b >= 4)) {
                    break;
                }
            }

            if (j == M && cnt_a == cnt_b) {
                cnt++;
                break;
            }
        }
    }

    return static_cast<double>(cnt) / static_cast<double>(N) * 100.0;
}
}  // namespace