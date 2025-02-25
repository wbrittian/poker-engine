/*test_game_unit.cpp*/

//
// poker-engine unit tests for game objects
//
// William Brittian
// 2025
//

#include <gtest/gtest.h>

#include "../fixtures.cpp"

TEST_F(GameTest, Basic) {
    EXPECT_EQ(2, 2);
}

TEST_F(GameTest, Initialize) {
    game1.initializeGame(player1, 5, 1000);

    EXPECT_EQ(game1.getNumPlayers(), 6);
}

// TODO: refactor when new function finished
//
// TEST_F(GameTest, Betting) {
//   game2.settlePlayerPot(300, player1);
//   game2.settlePlayerPot(-100, player1);

//   EXPECT_EQ(game2.getPot(), 200);
//   EXPECT_EQ(player1->getCash(), 800);

//   game2.settlePlayerBet(300, player1);
//   game2.settlePlayerBet(-100, player1);

//   EXPECT_EQ(game2.getBet(), 200);
//   EXPECT_EQ(player1->getCash(), 600);

//   game2.settleBetPot(100);
//   game2.settleBetPot(-50);

//   EXPECT_EQ(game2.getBet(), 150);
//   EXPECT_EQ(game2.getPot(), 250);
// }

TEST_F(GameTest, getPreviousPlayer) {
    std::shared_ptr<Player> bot = game2.getPreviousPlayer(player1);

    EXPECT_EQ(bot->getName(), "Bot 3");
}

TEST_F(GameTest, dealToPlayer) {
    game2.dealToPlayer(player1);

    EXPECT_EQ(size(player1->getCards()), 2);
}

TEST_F(GameTest, rotateOrder) {
    std::shared_ptr<Player> nextPlayer = player1->getNextPlayer();
    game2.rotateOrder();

    EXPECT_EQ(game2.getHead(), nextPlayer);
}

TEST_F(GameTest, addPlayer_1) {
    std::shared_ptr<Player> nextPlayer = player1->getNextPlayer();
    game2.addPlayer(player2, player1);

    EXPECT_EQ(player1->getNextPlayer(), player2);
    EXPECT_EQ(player2->getNextPlayer(), nextPlayer);
    EXPECT_EQ(game2.getNumPlayers(), 5);
}

TEST_F(GameTest, addPlayer_2) {
    std::shared_ptr<Player> nextPlayer = player1->getNextPlayer();
    std::shared_ptr<Player> nextNextPlayer = nextPlayer->getNextPlayer();
    game2.addPlayer(player2, nextPlayer);

    EXPECT_EQ(nextPlayer->getNextPlayer(), player2);
    EXPECT_EQ(player2->getNextPlayer(), nextNextPlayer);
    EXPECT_EQ(game2.getNumPlayers(), 5);
}

TEST_F(GameTest, removePlayer_1) {
    std::shared_ptr<Player> nextPlayer = player1->getNextPlayer();
    game2.removePlayer(player1);

    EXPECT_EQ(game2.getHead(), nextPlayer);
    EXPECT_EQ(game2.getNumPlayers(), 3);
}

TEST_F(GameTest, removePlayer_2) {
    std::shared_ptr<Player> nextPlayer = player1->getNextPlayer();
    std::shared_ptr<Player> nextNextPlayer = nextPlayer->getNextPlayer();
    game2.removePlayer(nextPlayer);

    EXPECT_EQ(player1->getNextPlayer(), nextNextPlayer);
    EXPECT_EQ(game2.getNumPlayers(), 3);
}

// TEST_F(GameTest, getCurrentLeader) {
//     game2.settlePlayerPot(200, player1->getNextPlayer());
//     game2.settlePlayerPot(-200, player1);

//     EXPECT_EQ(game2.getCurrentLeader(), player1);
// }
