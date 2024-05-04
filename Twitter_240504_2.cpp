// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://twitter.com/dc1394/status/1786659275449962978
#include <cassert>   // for assert
#include <chrono>    // for std::chrono
#include <cstdint>   // for std::uint32_t
#include <iostream>  // for std::cout, std::endl
#include <string>    // for std::string
#include <vector>    // for std::vector

namespace {
static auto constexpr CHECKYEAR = 100U;
static auto constexpr STARTYEAR = 2000U;

std::string get_answer();
}  // namespace

int main()
{
    auto const answer = get_answer();
    std::cout << "answer = " << answer << std::endl;

    return 0;
}

namespace {
std::string get_answer()
{
    namespace ch = std::chrono;

    std::vector<std::int32_t> v;
    for (auto i = 0U; i <= CHECKYEAR; i++) {
        ch::year_month_day_last ymdlast(ch::year(STARTYEAR + i), ch::last / ch::month(2));
        if (static_cast<std::uint32_t>(ymdlast.day()) == 29) {
            auto const ymd = ch::year_month_day(ch::year(STARTYEAR + i), ch::month(1), ch::day(1));
            auto const ymw = ch::year_month_weekday(ch::sys_days(ymd));
            if (ymw.weekday() == ch::Tuesday) {
                v.push_back(STARTYEAR + i);
            }
        }
    }

    std::string answer;
    for (auto const item : v) {
        for (auto i = 1U; i <= CHECKYEAR; i++) {
            auto const ymd = ch::year_month_day(ch::year(item + i), ch::month(1), ch::day(1));
            auto const ymw = ch::year_month_weekday(ch::sys_days(ymd));
            if (ymw.weekday() == ch::Tuesday) {
                assert(i == 5);
                answer = std::to_string(i) + "年後";
                std::cout << item << "年の" << i << "年後" << std::endl;
                break;
            }
        }
    }

    return answer;
}
}  // namespace