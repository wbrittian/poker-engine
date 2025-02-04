/*fixtures.cpp*/

//
// fixtures for poker-engine tests
//
// William Brittian
// 2025
//

#include <gtest/gtest.h>

#include "../src/player.h"
#include "../src/game.h"
#include "../src/deck.h"

class PlayerTest : public testing::Test {
protected:

    void SetUp() override {
        player1 = Player("Bob", 1000);
    }

    Player player1;
};

class GameTest : public testing::Test {
protected:

    void SetUp() override {
        player1 = new Player("Bob", 1000);

        game2.initializeGame(player1, 3, 1000);
    }

    void TearDown() override {
        game1.finishGame();
        game2.finishGame();

        delete player1;
        delete player2;
    }

    Game game1;
    Game game2;
    Player* player1;
    Player* player2;

};

class DeckTest : public testing::Test {
protected:
    Deck deck1;
};