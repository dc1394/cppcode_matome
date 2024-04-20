// 清水　団 Dan Shimizu（@dannchu）さんの問題の解答
// https://x.com/dc1394/status/1768232613997924376
// 参考→ https://nonbiri-tereka.hatenablog.com/entry/2014/07/01/123518
#include <cstdint>   // for std::int32_t
#include <iostream>  // for std::cout, std::endl
#include <optional>  // for std::optional
#include <vector>    // for std::vector

namespace {
static auto const M = 10000;
static auto const N = 2024;
static auto const L = 13;

class MemorizeFibonacci final
{
private:
    std::vector<std::optional<std::int32_t>> memo;

public:
    MemorizeFibonacci();
    std::int32_t calc(std::int32_t x);
};
}  // namespace

int main()
{
    std::cout << "answer = " << MemorizeFibonacci().calc(N) << std::endl;
}

namespace {
MemorizeFibonacci::MemorizeFibonacci() : memo(M, std::nullopt)
{
    memo[0] = 0;
    memo[1] = 1;
}

std::int32_t MemorizeFibonacci::calc(std::int32_t x)
{
    if (!memo[x].has_value()) {
        memo[x] = std::make_optional((calc(x - 1) + calc(x - 2)) % L);
    }

    return *(memo[x]);
}
}  // namespace