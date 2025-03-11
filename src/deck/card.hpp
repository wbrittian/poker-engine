/*card.h*/

//
// a card
//
// William Brittian
// 2025
//

#pragma once

#include <iostream>

#include "../utils/functions.hpp"

enum Suit {
    SPADES,
    HEARTS,
    CLUBS,
    DIAMONDS
};

struct Card {
    int Rank;
    Suit Suit;

    void printCard();
};