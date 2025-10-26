/*fixtures.cpp*/

//
// fixtures for poker-engine tests
//
// William Brittian
// 2025
//

#include <gtest/gtest.h>

#include "../src/core/engine.hpp"
#include "../src/core/player.hpp"
#include "../src/deck/deck.hpp"
#include "../src/deck/card.hpp"
#include "../src/deck/hand.hpp"

class PlayerTest : public testing::Test {
  protected:
    void SetUp() override { player1 = Player("Bob", 1000); }

    Player player1;
};

class EngineTest : public testing::Test {
  protected:
    void SetUp() override {
        player1 = std::make_shared<Player>("Bob", 1000);
        player2 = std::make_shared<Player>("Jim", 1000);

        engine2.initializeEngine(player1, 3, 1000);
    }

    void TearDown() override { engine2.finishEngine(); }

    Engine engine1;
    Engine engine2;
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
};

class DeckTest : public testing::Test {
  protected:
    Deck deck1;
};

class HandTest : public testing::Test {
  protected:
    struct Hand hand;

    void SetUp() override {
        hand.Cards.clear();
        hand.HandHigh.clear();
        hand.OtherHigh.clear();
        hand.Type = HIGH_CARD;
    }

    Card makeCard(Rank rank, Suit suit) {
        Card c;
        c.Rank = rank;
        c.Suit = suit;
        return c;
    } 
};