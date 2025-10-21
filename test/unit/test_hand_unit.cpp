/*test_hand_unit.cpp*/

//
// poker-engine unit tests for hand evaluation
//
// William Brittian
// 2025
//

#include <gtest/gtest.h>

#include "../fixtures.cpp"

TEST_F(HandTest, FullHouse) {
    hand.Cards = {
        makeCard(THREE, SPADES),
        makeCard(THREE, DIAMONDS),
        makeCard(FOUR, DIAMONDS),
        makeCard(QUEEN, SPADES),
        makeCard(QUEEN, DIAMONDS),
        makeCard(QUEEN, CLUBS),
        makeCard(SEVEN, HEARTS)
    };

    hand.evaluateHand();

    EXPECT_EQ(hand.Type, FULL_HOUSE);
    EXPECT_EQ(hand.HandHigh, std::vector<int>{QUEEN});
    EXPECT_EQ(hand.OtherHigh, std::vector<int>{THREE});
}