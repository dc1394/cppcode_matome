#include <cstdint>   // for std::int32_t
#include <iostream>  // for std::cout, std::endl
#include <random>    // for std::mt19937, std::random_device, std::uniform_int_distribution

namespace CoinProblem {

// 定数の定義
auto constexpr TOTAL_COINS        = 17;
auto constexpr TARGET_AMOUNT_YEN  = 750;
auto constexpr NUM_COIN_TYPES     = 6;
auto constexpr MIN_COINS_PER_TYPE = 1;
auto constexpr MAX_COINS_PER_TYPE = TOTAL_COINS - (MIN_COINS_PER_TYPE * (NUM_COIN_TYPES - 1));  // 12

// ランダムジェネレーターのクラス
class RandomGenerator final
{
    std::uniform_int_distribution<> distribution_;
    std::mt19937                    engine_;

public:
    RandomGenerator() : distribution_(MIN_COINS_PER_TYPE, MAX_COINS_PER_TYPE), engine_(std::random_device{}())
    {
    }

    std::int32_t generate()
    {
        return distribution_(engine_);
    }
};

// 5円硬貨の枚数を求める関数の宣言
std::int32_t findFiveYenCoinCount();

}  // namespace CoinProblem

int main()
{
    std::cout << "5円硬貨の枚数: " << CoinProblem::findFiveYenCoinCount() << std::endl;
}

namespace CoinProblem {

// 5円硬貨の枚数を求める関数の定義
std::int32_t findFiveYenCoinCount()
{
    RandomGenerator rng;
    std::int32_t    totalAmount;
    std::int32_t    num5Yen;

    do {
        // 各硬貨の枚数をランダムに生成
        auto const num500Yen = rng.generate();
        auto const num100Yen = rng.generate();
        auto const num50Yen  = rng.generate();
        auto const num10Yen  = rng.generate();
        num5Yen              = rng.generate();
        auto const num1Yen   = rng.generate();

        // 総枚数が17枚であることを確認
        if (num500Yen + num100Yen + num50Yen + num10Yen + num5Yen + num1Yen != TOTAL_COINS) {
            continue;
        }

        // 合計金額を計算
        totalAmount =
            (num500Yen * 500) + (num100Yen * 100) + (num50Yen * 50) + (num10Yen * 10) + (num5Yen * 5) + (num1Yen * 1);
    } while (totalAmount != TARGET_AMOUNT_YEN);  // 合計金額が750円になるまで繰り返す

    return num5Yen;
}

}  // namespace CoinProblem
