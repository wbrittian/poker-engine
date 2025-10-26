/*fixtures.cpp*/

//
// fixtures for poker-engine tests
//
// William Brittian
// 2025
//

#include <gtest/gtest.h>

#include "../src/core/engine.hpp"

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