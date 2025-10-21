/*hands.h*/

//
// enum for hand types
//
// William Brittian
// 2025
//

#pragma once

#include <map>
#include <vector>

#include "card.hpp"

enum HandTypes {
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
    std::vector<Card> Cards;
    enum HandTypes Type;
    std::vector<int> HandHigh;
    std::vector<int> OtherHigh;

    void evaluateHand();
};