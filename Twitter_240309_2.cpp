// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1766438029596762479
#include <cassert>  // for assert
#include <chrono>   // for std::chrono
#include <cstdint>  // for std::uint32_t
#include <iostream> // for std::cout, std::endl
#include <string>   // for std::string

namespace {
static auto constexpr STARTYEAR  = 1800U;
static auto constexpr STARTMONTH = 1U;

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
    std::string answer;    

    ch::year_month_day ymd(ch::year(STARTYEAR), ch::month(STARTMONTH), ch::day(1U));

    auto check = 0;
    for (auto i = 0U; i < (2024U - STARTYEAR) * 12U; i++) {
        ch::year_month_day_last ymdlast(ymd.year(), ch::last / ymd.month());

        auto const days_in_month = static_cast<std::uint32_t>(ymdlast.day());
        auto day_cnt = 0;
        for (auto i = 1U; i <= days_in_month; i++) {
            auto const ymdtmp = ch::year_month_day(ymd.year(), ymd.month(), ch::day(i));
            auto const ymw    = ch::year_month_weekday(ch::sys_days(ymdtmp));
            if (ymw.weekday() == ch::Tuesday) {
                day_cnt += i;
            }
        }

        if (day_cnt == 66 && days_in_month >= 30) {
            check++;
            auto const ymwtmp = ch::year_month_weekday(ch::sys_days(ch::year_month_day(ymd.year(), ymd.month(), ch::day(30U))));

            if (ymwtmp.weekday() == ch::Friday) {
                answer = "金曜日";                
            }
            else {
                assert(!"例外があった！");
            }
        }

        ymd += ch::months(1);
    }

    std::cout << "そのような月は" << STARTYEAR << "年" << STARTMONTH << "月から2024年1月まで" << check << "回あった" << std::endl; 

    return answer;
}
}  // namespace