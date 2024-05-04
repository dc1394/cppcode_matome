#include <boost/rational.hpp>  // for boost::rational
#include <cstdint>             // for std::int32_t
#include <iostream>            // for std::cout, std::endl
#include <numeric>             // for std::gcd
#include <vector>              // for std::vector

namespace {
using myfraction = boost::rational<std::int32_t>;
using myvector   = std::vector<myfraction>;

static auto const MAX = myfraction(3, 8);
static auto const MIN = myfraction(3, 11);

myvector get_answer();
}  // namespace

int main()
{
    auto const answer = get_answer();

    for (auto const & item : answer) {
        std::cout << item << ", ";
    }
    std::cout << "\nanswer = " << answer.size() << std::endl;
}

namespace {
myvector get_answer()
{
    myvector answer;

    for (auto i = 1;; i++) {
        if (std::gcd(8, i) != 1) {
            continue;
        }

        auto fraction = myfraction(8, i);

        if (fraction <= MIN) {
            break;
        }

        if (fraction > MIN && fraction < MAX) {
            answer.push_back(fraction);
        }
    }

    return answer;
}
}  // namespace
