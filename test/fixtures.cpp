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
        player1 = Player("Bob", 500);
    }

    Player player1;
};

class GameTest : public testing::Test {
protected:

    void SetUp() override {
        player1 = new Player("Bob", 500);

        game1.initializeGame(player1, 3, 500);
    }

    void TearDown() override {
        delete player1;
    }

    Game game1;
    Player* player1;

};

class DeckTest : public testing::Test {

};