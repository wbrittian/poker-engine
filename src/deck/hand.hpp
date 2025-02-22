/*hands.h*/

//
// enum for hand types
//
// William Brittian
// 2025
//

#pragma once

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
    std::vector<Card> PlayerCards;
    std::vector<Card> CommunityCards;
    enum HandTypes Type;
    Card HighCard;
};