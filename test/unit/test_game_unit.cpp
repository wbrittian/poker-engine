/*test_engine_unit.cpp*/

//
// poker-engine unit tests for engine objects
//
// William Brittian
// 2025
//

#include <gtest/gtest.h>

#include "../fixtures.cpp"

TEST_F(EngineTest, Basic) {
    EXPECT_EQ(2, 2);
}

TEST_F(EngineTest, Initialize) {
    engine1.initializeEngine(player1, 5, 1000);

    EXPECT_EQ(engine1.getNumPlayers(), 6);
}

// TODO: refactor when new function finished
//
// TEST_F(EngineTest, Betting) {
//   engine2.settlePlayerPot(300, player1);
//   engine2.settlePlayerPot(-100, player1);

//   EXPECT_EQ(engine2.getPot(), 200);
//   EXPECT_EQ(player1->getCash(), 800);

//   engine2.settlePlayerBet(300, player1);
//   engine2.settlePlayerBet(-100, player1);

//   EXPECT_EQ(engine2.getBet(), 200);
//   EXPECT_EQ(player1->getCash(), 600);

//   engine2.settleBetPot(100);
//   engine2.settleBetPot(-50);

//   EXPECT_EQ(engine2.getBet(), 150);
//   EXPECT_EQ(engine2.getPot(), 250);
// }

TEST_F(EngineTest, getPreviousPlayer) {
    std::shared_ptr<Player> bot = engine2.getPreviousPlayer(player1);

    EXPECT_EQ(bot->getName(), "Bot 3");
}

TEST_F(EngineTest, dealToPlayer) {
    engine2.dealToPlayer(player1);

    EXPECT_EQ(size(player1->getCards()), 2);
}

TEST_F(EngineTest, rotateOrder) {
    std::shared_ptr<Player> nextPlayer = player1->getNextPlayer();
    engine2.rotateOrder();

    EXPECT_EQ(engine2.getHead(), nextPlayer);
}

TEST_F(EngineTest, addPlayer_1) {
    std::shared_ptr<Player> nextPlayer = player1->getNextPlayer();
    engine2.addPlayer(player2, player1);

    EXPECT_EQ(player1->getNextPlayer(), player2);
    EXPECT_EQ(player2->getNextPlayer(), nextPlayer);
    EXPECT_EQ(engine2.getNumPlayers(), 5);
}

TEST_F(EngineTest, addPlayer_2) {
    std::shared_ptr<Player> nextPlayer = player1->getNextPlayer();
    std::shared_ptr<Player> nextNextPlayer = nextPlayer->getNextPlayer();
    engine2.addPlayer(player2, nextPlayer);

    EXPECT_EQ(nextPlayer->getNextPlayer(), player2);
    EXPECT_EQ(player2->getNextPlayer(), nextNextPlayer);
    EXPECT_EQ(engine2.getNumPlayers(), 5);
}

TEST_F(EngineTest, removePlayer_1) {
    std::shared_ptr<Player> nextPlayer = player1->getNextPlayer();
    engine2.removePlayer(player1);

    EXPECT_EQ(engine2.getHead(), nextPlayer);
    EXPECT_EQ(engine2.getNumPlayers(), 3);
}

TEST_F(EngineTest, removePlayer_2) {
    std::shared_ptr<Player> nextPlayer = player1->getNextPlayer();
    std::shared_ptr<Player> nextNextPlayer = nextPlayer->getNextPlayer();
    engine2.removePlayer(nextPlayer);

    EXPECT_EQ(player1->getNextPlayer(), nextNextPlayer);
    EXPECT_EQ(engine2.getNumPlayers(), 3);
}

// TEST_F(EngineTest, getCurrentLeader) {
//     engine2.settlePlayerPot(200, player1->getNextPlayer());
//     engine2.settlePlayerPot(-200, player1);

//     EXPECT_EQ(engine2.getCurrentLeader(), player1);
// }
