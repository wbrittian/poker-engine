/*fixtures.cpp*/

//
// fixtures for poker-engine tests
//
// William Brittian
// 2025
//

#include <gtest/gtest.h>

#include "../src/core/game.hpp"
#include "../src/core/player.hpp"
#include "../src/deck/deck.hpp"

class PlayerTest : public testing::Test {
  protected:
    void SetUp() override { player1 = Player("Bob", 1000); }

    Player player1;
};

class GameTest : public testing::Test {
  protected:
    void SetUp() override {
        player1 = std::make_shared<Player>("Bob", 1000);
        player2 = std::make_shared<Player>("Jim", 1000);

        game2.initializeGame(player1, 3, 1000);
    }

    void TearDown() override { game2.finishGame(); }

    Game game1;
    Game game2;
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
};

class DeckTest : public testing::Test {
  protected:
    Deck deck1;
};