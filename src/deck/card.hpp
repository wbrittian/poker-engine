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

enum class Suit {
    SPADES,
    HEARTS,
    CLUBS,
    DIAMONDS
};

struct Card {
    int Rank;
    enum Suit Suit;

    void printCard();
};