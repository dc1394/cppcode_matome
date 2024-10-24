// 鈴木伸介@数学アカデミー（@suzzukes）さん作の問題の解答
// https://x.com/dc1394/status/1830087440360697951
// コンパイルに-std=c++20指定が必要
#include <array>      // for std::array
#include <cstdint>    // for std::int32_t, std::int64_t
#include <format>     // for std::format
#include <iostream>   // for std::cout, std::endl
#include <random>     // for std::mt19937, std::random_device, std::uniform_int_distribution
#include <stdexcept>  // for std::invalid_argument
#include <string>     // for std::string
#include <utility>    // for std::make_pair, std::pair
#include <vector>     // for std::vector

namespace card_game {

// Constants
static auto constexpr NUM_SIMULATIONS = 1000000;
static auto constexpr NUM_SUITS       = 4;
static auto constexpr NUM_RANKS       = 13;

// Enums for suits and ranks
enum class Suit
{
    Spades,
    Clubs,
    Diamonds,
    Hearts
};

enum class Rank
{
    Ace = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

// Card structure
struct Card
{
    Suit suit;
    Rank rank;
};

// Function declarations
std::vector<Card>           create_deck();
std::array<std::int64_t, 4> simulate_game(std::vector<Card> const & deck);
std::string                 suit_to_string(Suit suit);
std::string                 rank_to_string(Rank rank);
}  // namespace card_game

// Main function
int main()
{
    auto deck    = card_game::create_deck();
    auto results = card_game::simulate_game(deck);

    std::cout << std::format("A: {}点, B: {}点, C: {}点, D: {}点\n", results[0], results[1], results[2], results[3]);
    return 0;
}

namespace card_game {
// Create a full deck of cards
std::vector<Card> create_deck()
{
    std::vector<Card> deck;
    deck.reserve(NUM_SUITS * NUM_RANKS);

    for (auto s = 0; s < NUM_SUITS; ++s) {
        for (auto r = 1; r <= NUM_RANKS; ++r) {
            deck.push_back({static_cast<Suit>(s), static_cast<Rank>(r)});
        }
    }

    return deck;
}

// Simulate the game and return results
std::array<std::int64_t, 4> simulate_game(std::vector<Card> const & deck)
{
    std::array<std::int64_t, 4>     results{};
    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> dis(0, deck.size() - 1);

    for (auto i = 0; i < NUM_SIMULATIONS; ++i) {
        auto const & card = deck[dis(gen)];

        if (card.suit == Suit::Diamonds) {
            results[0] += 100;
        } else if (card.rank == Rank::Jack || card.rank == Rank::Queen || card.rank == Rank::King) {
            results[1] += 150;
        } else if (card.rank == Rank::Ace) {
            results[2] += 300;
        } else if (card.suit == Suit::Hearts && card.rank == Rank::Seven) {
            results[3] += 1500;
        }
    }

    return results;
}

// Convert Suit enum to string
std::string suit_to_string(Suit suit)
{
    switch (suit) {
    case Suit::Spades:
        return "Spades";
    case Suit::Clubs:
        return "Clubs";
    case Suit::Diamonds:
        return "Diamonds";
    case Suit::Hearts:
        return "Hearts";
    default:
        throw std::invalid_argument("Invalid suit");
    }
}

// Convert Rank enum to string
std::string rank_to_string(Rank rank)
{
    switch (rank) {
    case Rank::Ace:
        return "A";
    case Rank::Jack:
        return "J";
    case Rank::Queen:
        return "Q";
    case Rank::King:
        return "K";
    default:
        return std::to_string(static_cast<std::int32_t>(rank));
    }
}

}  // namespace card_game