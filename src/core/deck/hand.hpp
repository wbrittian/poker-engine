/*hand.h*/

//
// enum for hand types
//
// William Brittian
// 2025
//

#pragma once

#include <map>
#include <vector>

#include "deck.hpp"

enum HandType {
    HIGH_CARD = 0, // high card
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
};

struct Hand {
    int PlayerId;
    std::vector<Card> Cards;
    enum HandType Type;
    std::vector<int> HandHigh;
    std::vector<int> OtherHigh;

    void evaluateHand(const std::vector<Card>& community);
};